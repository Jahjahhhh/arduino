#include <LiquidCrystal.h>
#include "definitions21.h"
#include "recup.h"

void instructions() {
  String premiereLigne[] = { { "prev: joystk <- " }, { "quit: joystk DWN" },   { "Pour modifier   " }, { "Pour changer    " }, { "appuyer joystick"}, { "Pour sortir du  " }, { "maintenir S4 et " }, { "      FIN       " } };
  String deuxiemeLigne[] = { { "next: joystk -> " }, { "open: joystk  UP" },   { "l'heure: s2, s3." }, { "d'unite de temps" }, { "               " }, { "mode de reglage " }, { "presser joystick" }, { "quit: joystk DWN" } };
  size_t len = sizeof(premiereLigne) / sizeof(premiereLigne[0]); // classique pour trouver le nombre d'elements dans un array
  byte page = 0;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("VOICI LE MENU    ");
  lcd.setCursor(0, 1);
  lcd.print("D'INSTRUCTIONS:  ");
  delay(2000);

  unsigned int middle = analogRead(JOY_X_PIN); // la valeur au centre est differente d'un joystick à l'autre

  while (analogRead(JOY_Y_PIN) >= 400) { // y <= 400?, si vrai, sortir de la boucle
    lcd.setCursor(0, 0); lcd.print(premiereLigne[page]); lcd.print("   ");
    lcd.setCursor(0, 1); lcd.print(deuxiemeLigne[page]); lcd.print("   ");

    if (analogRead(JOY_X_PIN) > (middle+5) && page > 0) page--; // GAUCHE = 1023
    else if (analogRead(JOY_X_PIN) < (middle-5) && page < len - 1) page++; // DROITE = 0
    while (analogRead(JOY_X_PIN) != middle);
  }
  lcd.clear();
}

String jourEnLettres(byte jour) {
  String jour_en_lettres;
  if (jour > 7 || jour < 1) jour = 1;  // [1-7], remettre a 1(lundi) si on est pas dans le range
  switch (jour) {
    case 1: jour_en_lettres = "Lun"; break;
    case 2: jour_en_lettres = "Mar"; break;
    case 3: jour_en_lettres = "Mer"; break;
    case 4: jour_en_lettres = "Jeu"; break;
    case 5: jour_en_lettres = "Ven"; break;
    case 6: jour_en_lettres = "Sam"; break;
    case 7: jour_en_lettres = "Dim"; break;
    default: jour_en_lettres = "???";
  }
  return jour_en_lettres;
}

void afficherTempsFormat() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RTC");
  lcd.setCursor(8, 0);
  lcd.print("jj");
  lcd.print("/");
  lcd.print("mm");
  lcd.print("/");
  lcd.print("aa");
  lcd.setCursor(0, 1);
  lcd.print("jour");
  lcd.setCursor(8, 1);
  lcd.print("hh");
  lcd.print(":");
  lcd.print("mm");
  lcd.print(":");
  lcd.print("ss");
  delay(5000);
  lcd.clear();
}

void afficherTemps() {
  lcd.setCursor(8, 0);
  lcd.print(recupTemps[0].date[1]);
  lcd.print(recupTemps[0].date[0]);
  lcd.print("/");
  lcd.print(recupTemps[0].mois[1]);
  lcd.print(recupTemps[0].mois[0]);
  lcd.print("/");
  lcd.print(recupTemps[0].annee[1]);
  lcd.print(recupTemps[0].annee[0]);

  lcd.setCursor(0, 1);
  lcd.print(jourEnLettres(recupTemps[0].jour[0]));
  lcd.setCursor(8, 1);
  lcd.print(recupTemps[0].heure[1]);
  lcd.print(recupTemps[0].heure[0]);
  lcd.print(":");
  lcd.print(recupTemps[0].minute[1]);
  lcd.print(recupTemps[0].minute[0]);
  lcd.print(":");
  lcd.print(recupTemps[0].seconde[1]);
  lcd.print(recupTemps[0].seconde[0]);
}

void reglageTemps(byte unite_de_temps) {
  static byte sec = 0, min = 0, hrs = 0, jrs = 1, date = 1, mois = 1, an = 0;

  switch (unite_de_temps) {  // Les cases sont defini dans definitions21.h
    case SECONDES:
      if (!digitalRead(SW_S3_PIN)) sec++;
      else if (!digitalRead(SW_S2_PIN)) sec--;
      sec == 255 ? sec = 59 : sec %= 60;
      recupTemps[0].seconde[1] = sec / 10;
      recupTemps[0].seconde[0] = sec % 10;
      break;
    case MINUTES:
      if (!digitalRead(SW_S3_PIN)) min++;
      else if (!digitalRead(SW_S2_PIN)) min--;
      min == 255 ? min = 59 : min %= 60;
      recupTemps[0].minute[1] = min / 10;
      recupTemps[0].minute[0] = min % 10;
      break;
    case HEURES:
      if (!digitalRead(SW_S3_PIN)) hrs++;
      else if (!digitalRead(SW_S2_PIN)) hrs--;
      hrs == 255 ? hrs = 23 : hrs %= 24;
      recupTemps[0].heure[1] = hrs / 10;
      recupTemps[0].heure[0] = hrs % 10;
      break;
    case JOURS:
      if (!digitalRead(SW_S3_PIN)) jrs++;
      else if (!digitalRead(SW_S2_PIN)) jrs--;
      jrs %= 8;
      recupTemps[0].jour[0] = jrs;
      break;
    case DATE:
      if (!digitalRead(SW_S3_PIN)) date++;
      else if (!digitalRead(SW_S2_PIN)) date--;
      date == 255 ? date = 31 : date %= 32;
      recupTemps[0].date[1] = date / 10;
      recupTemps[0].date[0] = date % 10;
      break;
    case MOIS:
      if (!digitalRead(SW_S3_PIN)) mois++;
      else if (!digitalRead(SW_S2_PIN)) mois--;
      mois == 255 ? mois = 12 : mois %= 13;
      recupTemps[0].mois[1] = mois / 10;
      recupTemps[0].mois[0] = mois % 10;
      break;
    case ANNEES:
      if (!digitalRead(SW_S3_PIN)) an++;
      else if (!digitalRead(SW_S2_PIN)) an--;
      an == 255 ? an = 99 : an %= 100;
      recupTemps[0].annee[1] = an / 10;
      recupTemps[0].annee[0] = an % 10;
      break;
  }
}

void envoyerTemps() {
  byte sec, min, hrs, date, mois, an;
  sec = (recupTemps[0].seconde[1] << 4) | (recupTemps[0].seconde[0]);
  min = (recupTemps[0].minute[1] << 4) | (recupTemps[0].minute[0]);
  hrs = ((recupTemps[0].heure[1] & 0b11) << 4) | (recupTemps[0].heure[0]);
  date = ((recupTemps[0].date[1] & 0b11) << 4) | (recupTemps[0].date[0]);
  mois = ((recupTemps[0].mois[1] & 0b1) << 4) | (recupTemps[0].mois[0]);
  an = (recupTemps[0].annee[1] << 4) | (recupTemps[0].annee[0]);

  Wire.beginTransmission(RTC);
  Wire.write(REGISTRE_SEC);
  Wire.write(sec);
  Wire.endTransmission();

  Wire.beginTransmission(RTC);
  Wire.write(REGISTRE_MIN);
  Wire.write(min);
  Wire.endTransmission();

  Wire.beginTransmission(RTC);
  Wire.write(REGISTRE_HRS);
  Wire.write(hrs);
  Wire.endTransmission();

  Wire.beginTransmission(RTC);
  Wire.write(REGISTRE_JRS);
  Wire.write(recupTemps[0].jour[0]);
  Wire.endTransmission();

  Wire.beginTransmission(RTC);
  Wire.write(REGISTRE_DATE);
  Wire.write(date);
  Wire.endTransmission();

  Wire.beginTransmission(RTC);
  Wire.write(REGISTRE_MOIS);
  Wire.write(mois);
  Wire.endTransmission();

  Wire.beginTransmission(RTC);
  Wire.write(REGISTRE_AN);
  Wire.write(an);
  Wire.endTransmission();
}

void reglerRTC() {
  byte unite_de_temps = 1;
  String affichage_unite_de_temps[7] = { "SEC   ", "MIN   ", "HRS  ", "JRS   ", "DATE  ", "MOIS  ", "ANNEES" };



  do {
    if (unite_de_temps > 7) unite_de_temps = 1;
    do {
      if (analogRead(JOY_Y_PIN) >= 800) instructions();
      lcd.setCursor(0, 0);
      lcd.print(affichage_unite_de_temps[unite_de_temps - 1]);
      afficherTemps();
      reglageTemps(unite_de_temps);
      delay(100);  // Delai entre chaque incrementation/decrementation
    } while (digitalRead(JOY_SW_PIN));
    delay(250);
    unite_de_temps++;
  } while (digitalRead(SW_S4_PIN));

  envoyerTemps();
}

void menu() {
  bool changer, garder;

  do {
    lcd.setCursor(0, 0);
    lcd.print("S2: CHANGER");
    lcd.setCursor(0, 1);
    lcd.print("S3: GARDER");
    changer = digitalRead(SW_S2_PIN);
    garder = digitalRead(SW_S3_PIN);
    delay(150);
  } while (changer && garder);
  lcd.clear();

  if (changer == LOW) {
    lcd.setCursor(0, 0); lcd.print("JOY UP pour les");
    lcd.setCursor(0, 1); lcd.print("instructions");
    delay(2000); lcd.clear();
    reglerRTC();
  }
}

void horloge() {
  static bool premiereFois = true;

  while (digitalRead(SW_S4_PIN) == HIGH) {

    if (premiereFois == true) {
      recupSeconde();
      recupMinute();
      recupHeure();
      recupJour();
      recupDate();
      recupMois();
      recupAnnee();
      premiereFois = false;
    }

    recupSeconde();  // On veut chercher la nouvelle valeur des secondes a chaque loop (1000ms par iteration)

    if (recupTemps[0].seconde[1] == 0 && recupTemps[0].seconde[0] == 0) {
      recupMinute();
      if (recupTemps[0].minute[1] == 0 && recupTemps[0].minute[0] == 0) {
        recupHeure();
        if (recupTemps[0].heure[1] == 0 && recupTemps[0].heure[0] == 0) {
          recupJour();
          recupDate();
          if (recupTemps[0].date[1] == 0 && recupTemps[0].date[0] == 1) { // valeur minimale de la date (le jour 0 n'existe pas)
            recupMois();
            if (recupTemps[0].mois[1] == 0 && recupTemps[0].mois[0] == 1) { // valeur minimale du mois (le mois 0 n'existe pas)
              recupAnnee();
            }
          }
        }
      }
    }
    lcd.setCursor(0, 0);
    lcd.print("RTC    ");
    afficherTemps();
  }
}
