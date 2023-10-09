#include <Wire.h>

struct temps {
  byte annee[2];
  byte mois[2];
  byte date[2];
  byte jour[1]; // (0-6)
  byte heure[2];
  byte minute[2];
  byte seconde[2];
} recupTemps[] = {
  { {0, 0}, {0, 0}, {0, 0}, {0}, {0, 0}, {0, 0}, {0, 0} }
};

void recupSeconde() {
  byte seconde;
  byte sec_unite;
  byte sec_dizzaine;

  Wire.beginTransmission(RTC);
  Wire.write(REGISTRE_SEC);
  Wire.endTransmission(false);
  Wire.requestFrom(RTC, 1, true);
  seconde = Wire.read();

  sec_unite = seconde & 0b1111;
  sec_dizzaine = seconde >> 4;

  recupTemps[0].seconde[1] = sec_dizzaine;
  recupTemps[0].seconde[0] = sec_unite;
}

void recupMinute() {
  byte minute;
  byte min_unite;
  byte min_dizzaine;

  Wire.beginTransmission(RTC);
  Wire.write(REGISTRE_MIN);
  Wire.endTransmission(false);
  Wire.requestFrom(RTC, 1, true);
  minute = Wire.read();

  min_unite = minute & 0b1111;
  min_dizzaine = minute >> 4;

  recupTemps[0].minute[1] = min_dizzaine;
  recupTemps[0].minute[0] = min_unite;
}

void recupHeure() {
  byte heure;
  byte heure_unite;
  byte heure_dizzaine;

  Wire.beginTransmission(RTC);
  Wire.write(REGISTRE_HRS);
  Wire.endTransmission(false);
  Wire.requestFrom(RTC, 1, true);
  heure = Wire.read();

  heure_unite = heure & 0b1111;
  heure_dizzaine = (heure >> 4) & 0b11; // Recup des bit 4-5 puisque c'est configuré en format 0-24h

  recupTemps[0].heure[1] = heure_dizzaine;
  recupTemps[0].heure[0] = heure_unite;
}

void recupJour() { // Jours de la semaine (1-7)
  byte jour;

  Wire.beginTransmission(RTC);
  Wire.write(REGISTRE_JRS);
  Wire.endTransmission(false);
  Wire.requestFrom(RTC, 1, true);
  jour = Wire.read();

  recupTemps[0].jour[0] = jour;
}

void recupDate() { // Jour du mois (1-31)
  byte date;
  byte date_unite;
  byte date_dizzaine;

  Wire.beginTransmission(RTC);
  Wire.write(REGISTRE_DATE);
  Wire.endTransmission(false);
  Wire.requestFrom(RTC, 1, true);
  date = Wire.read();

  date_unite = date & 0b1111;
  date_dizzaine = (date >> 4) & 0b11;

  recupTemps[0].date[1] = date_dizzaine;
  recupTemps[0].date[0] = date_unite;
}

void recupMois() {
  byte mois;
  byte mois_unite;
  byte mois_dizzaine;

  Wire.beginTransmission(RTC);
  Wire.write(REGISTRE_MOIS);
  Wire.endTransmission(false);
  Wire.requestFrom(RTC, 1, true);
  mois = Wire.read();

  mois_dizzaine = (mois >> 4) & 0b1;
  mois_unite = mois & 0b1111;

  recupTemps[0].mois[1] = mois_dizzaine;
  recupTemps[0].mois[0] = mois_unite;
}

void recupAnnee() {
  byte annee;
  byte annee_unite;
  byte annee_dizzaine;

  Wire.beginTransmission(RTC);
  Wire.write(REGISTRE_AN);
  Wire.endTransmission(false);
  Wire.requestFrom(RTC, 1, true);
  annee = Wire.read();

  annee_dizzaine = annee >> 4;
  annee_unite = annee & 0b1111;

  recupTemps[0].annee[1] = annee_dizzaine;
  recupTemps[0].annee[0] = annee_unite;
}
