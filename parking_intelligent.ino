#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>

/**
 * SYS-EMBRQ: SMART PARKING 
 */

LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo entreeServo;
#define PIN_SERVO 13 

#define LED_VERT  26 
#define LED_ROUGE 27 
#define LED_A     25 // Occupation Zone A
#define LED_B     33 // Occupation Zone B

#define PIN_TRIG  3  

struct Ultra { 
  int echo; 
  const char* nom; 
};

//ECHO de ultras
Ultra capteurs[4] = {
  {15, "Entree"}, 
  {2,  "ZoneA "}, 
  {4,  "ZoneB "}, 
  {5,  "Sortie"} 
};

const int CAPACITE         = 6;   
const int SEUIL_VOITURE    = 15;   // Distance de détection dune voiture 
const int SEUIL_ZONE_LIBRE = 30;   // Distance pour considerer une place libre 
const unsigned long DEBOUNCE_MS  = 2500; // Temps datt entre deux détections b millisec
const unsigned long LCD_INTERVAL = 500;  // Intervalle de mise à jour de lecran b millisec

// ================= VARIABLES DE GESTION =================
int voitures = 0;
unsigned long derniere_entree = 0;
unsigned long derniere_sortie = 0;
unsigned long dernierLCD      = 0;

/**
 * Fonction pour lire la distance d'un capteur spécifique
 * @param echoPin Le pin ECHO du capteur à lire
 * @return La distance mesurée en centimètres
 */
long lireDistance(int echoPin) {
  // Génération de l'impulsion TRIG (commune à tous)
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(4);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  // Mesure du temps de retour de l'écho sur le pin spécifique
  // Timeout de 30ms pour ne pas bloquer le programme si rien n'est détecté
  long duree = pulseIn(echoPin, HIGH, 30000);
  
  if (duree == 0) return 999; // Pas d'obstacle détecté
  return duree * 0.034 / 2;   // Conversion temps -> distance (vitesse du son)
}

/**
 * Fonction pour ouvrir la barrière de manière fluide
 * 
 */
void ouvrirBarriere() {
  Serial.println("Action : Ouverture Barrière...");
  for (int pos = 0; pos <= 90; pos += 2) { // Mouvement progressif
    entreeServo.write(pos);
    delay(15);
  }
}

/**
 * Fonction pour fermer la barrière de manière fluide
 */
void fermerBarriere() {
  Serial.println("Action : Fermeture Barrière...");
  for (int pos = 90; pos >= 0; pos -= 2) {
    entreeServo.write(pos);
    delay(15);
  }
}

/**
 * Mise à jour intelligente de l'affichage LCD
 */
void mettreAJourLCD(int places, long dA, long dB) {
  lcd.setCursor(0, 0);
  lcd.print("SMART PARKING   ");

  lcd.setCursor(0, 1);
  if (places <= 0) {
    lcd.print("Free:0 PARK FULL");
  } else {
    String dir = "";
    bool zoneA_libre = (dA > SEUIL_ZONE_LIBRE);
    bool zoneB_libre = (dB > SEUIL_ZONE_LIBRE);

    if (zoneA_libre && zoneB_libre) dir = "GO A or B ";
    else if (zoneA_libre)           dir = "GO LEFT A ";
    else if (zoneB_libre)           dir = "GO RIGHT B";
    else                            dir = "WAIT      ";

    // Construction de la ligne avec formatage propre
    String ligne = "Free:" + String(places) + " " + dir;
    while (ligne.length() < 16) ligne += " "; // Compléter avec des espaces
    lcd.print(ligne);
  }
}

// ================= INITIALISATION =================
void setup() {
  // Note : On utilise Serial pour le debug (TX0), mais RX0 est pris par le TRIG
  Serial.begin(115200);

  // Configuration du TRIG commun
  pinMode(PIN_TRIG, OUTPUT);
  digitalWrite(PIN_TRIG, LOW);

  // Configuration des pins ECHO
  for (int i = 0; i < 4; i++) {
    pinMode(capteurs[i].echo, INPUT);
  }

  // Configuration des LEDs
  pinMode(LED_VERT,  OUTPUT);
  pinMode(LED_ROUGE, OUTPUT);
  pinMode(LED_A,     OUTPUT);
  pinMode(LED_B,     OUTPUT);

  // Configuration du Servo
  ESP32PWM::allocateTimer(0);
  entreeServo.setPeriodHertz(50);
  entreeServo.attach(PIN_SERVO, 500, 2400);
  entreeServo.write(0); // Position fermée par défaut

  // Initialisation de l'écran LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SYSTEM STARTING");
  delay(2000);
  lcd.clear();

  Serial.println("=== SYSTEME PRET ===");
}

// ================= BOUCLE PRINCIPALE =================
void loop() {
  unsigned long maintenant = millis();
  long d[4];

  // 1. Lecture séquentielle des capteurs
  for (int i = 0; i < 4; i++) {
    d[i] = lireDistance(capteurs[i].echo);
    delay(40); // Délai pour éviter les interférences entre échos
  }

  // 2. Logique d'ENTRÉE (Incrémente le compteur)
  // Utilisation d'un "Debounce" pour éviter les doubles comptages
  if (d[0] < SEUIL_VOITURE && (maintenant - derniere_entree > DEBOUNCE_MS)) {
    if (voitures < CAPACITE) {
      voitures++;
      derniere_entree = maintenant;
      Serial.print("Entree detectee ! Voitures : "); Serial.println(voitures);
      ouvrirBarriere();
      delay(2000); // Temps pour laisser passer la voiture
      fermerBarriere();
    } else {
      Serial.println("Parking Plein ! Entree refusee.");
    }
  }

  // 3. Logique de SORTIE (Décrémente le compteur)
  if (d[3] < SEUIL_VOITURE && (maintenant - derniere_sortie > DEBOUNCE_MS)) {
    if (voitures > 0) {
      voitures--;
      derniere_sortie = maintenant;
      Serial.print("Sortie detectee ! Voitures : "); Serial.println(voitures);
    }
  }

  // le compteur reste entre 0 et capacitz
  voitures = constrain(voitures, 0, CAPACITE);
  int places_libres = CAPACITE - voitures;

  // 4. Gestion des LEDs de Zone
  digitalWrite(LED_A, (d[1] < SEUIL_VOITURE) ? HIGH : LOW);
  digitalWrite(LED_B, (d[2] < SEUIL_VOITURE) ? HIGH : LOW);

  // 5. Gestion des LEDs d'état général
  if (places_libres > 0) {
    digitalWrite(LED_VERT, HIGH);
    digitalWrite(LED_ROUGE, LOW);
  } else {
    digitalWrite(LED_VERT, LOW);
    digitalWrite(LED_ROUGE, HIGH);
  }

  // 6. Mise à jour de l'affichage LCD 
  if (maintenant - dernierLCD >= LCD_INTERVAL) {
    dernierLCD = maintenant;
    mettreAJourLCD(places_libres, d[1], d[2]);
  }

  delay(10); 
}