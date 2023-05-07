byte modification_heure, modification_minute, modification_seconde, modification_jour, modification_mois, modification_annee, modif_jour_en_lettres = 0;
bool modification_rtc = false;

struct temps {
  unsigned int annee[2];
  unsigned int mois[2];
  String jour_en_lettres[7];
  unsigned int jour[2];
  unsigned int heure[2];
  unsigned int minute[2];
  unsigned int secondes[2];
} recupererTemps[] = {
  { {0,0}, {0,0}, {"Lun", "Mar", "Mer", "Jeu", "Ven", "Sam", "Dim"}, {0, 0}, {0, 0}, {0, 0}, {0, 0} }
};

void trente_jours()
{
  if (modification_jour >= 31 && modification_jour != 255) modification_jour = 0;
  else if (modification_jour == 255) modification_jour = 30;
}

void trente_et_un_jours()
{
  if (modification_jour >= 32 && modification_jour != 255) modification_jour = 0;
  else if (modification_jour == 255) modification_jour = 31;
}

void fevrier()
{
  if(modification_annee % 4 == 0)
  {
    if(modification_annee % 100 == 0)
    {
      if(modification_annee % 400 == 0)
      {
        if (modification_jour >= 30 && modification_jour != 255) modification_jour = 0;
        else if (modification_jour == 255) modification_jour = 29;
      }
      else
      {
        if (modification_jour >= 29 && modification_jour != 255) modification_jour = 0;
        else if (modification_jour == 255) modification_jour = 28;
      }
    }
    else
    {
      if (modification_jour >= 30 && modification_jour != 255) modification_jour = 0;
      else if (modification_jour == 255) modification_jour = 29;
    }
  }
  else 
  {
    if (modification_jour >= 29 && modification_jour != 255) modification_jour = 0;
    else if (modification_jour == 255) modification_jour = 28;
  }
}

void jours_dans_mois()
{
  switch(modification_mois)
  {
    case 0: // mois 0 n'exsite pas, permet de loopback quand on a pas choisi le mois (affichage: jj/mm/aa, mois = mm)
      trente_et_un_jours();
      break;
    case 1:
      trente_et_un_jours();
      break;
    case 2:
      fevrier();
      break;
    case 3:
      trente_et_un_jours();
      break;
    case 4:
      trente_jours();
      break;
    case 5:
      trente_et_un_jours();
      break;
    case 6:
      trente_jours();
      break;
    case 7:
      trente_et_un_jours();
      break;
    case 8:
      trente_et_un_jours();
      break;
    case 9:
      trente_jours();
      break;
    case 10:
      trente_et_un_jours();
      break;
    case 11:
      trente_jours();
      break;
    case 12:
      trente_et_un_jours();
  }
}

void loopback() // permet de loop dans les deux sens (décrémenter lorsque ca affiche 0 ne donnera pas 255 (variable de type byte 0-255) mais 23 (si on modifie l'heure) et 59 si on modifie les secondes/minutes
{ // si on est a 59, incrementer la variable donnera 00 et non 60 (etc)
  if(modification_annee >= 100 && modification_annee != 255) modification_annee = 0;
  else if(modification_annee == 255) modification_annee = 99;
  
  if (modification_mois >= 13 && modification_mois != 255) modification_mois = 0;
  else if (modification_mois == 255) modification_mois = 12;

  if (modif_jour_en_lettres >= 7 && modif_jour_en_lettres != 255) modif_jour_en_lettres = 0;
  else if (modif_jour_en_lettres == 255) modif_jour_en_lettres = 6;

  if (modification_heure >= 24 && modification_heure != 255) modification_heure = 0;
  else if (modification_heure == 255) modification_heure = 23;

  if (modification_minute >= 60 && modification_minute != 255) modification_minute = 0;
  else if (modification_minute == 255) modification_minute = 59;

  if (modification_seconde >= 60 && modification_seconde != 255) modification_seconde = 0;
  else if (modification_seconde == 255) modification_seconde = 59;
}

void recupererAnnee(void)
{
  int annee;
  int aunite;
  int adizzaine;

  Wire.beginTransmission(104);
  Wire.write(0x06);
  Wire.endTransmission(false);
  Wire.requestFrom(104, 1, true);
  annee = Wire.read();

  aunite = annee & 0b00001111; // les unités sont les 4LSB
  adizzaine = ((annee >> 4) & 0b0011); // les dizaines sont les 2 bits après

  recupererTemps[0].annee[1] = adizzaine;
  recupererTemps[0].annee[0] = aunite;
}

void recupererMois(void)
{
  int mois;
  int munite;
  int mdizzaine;

  Wire.beginTransmission(104);
  Wire.write(0x05);
  Wire.endTransmission(false);
  Wire.requestFrom(104, 1, true);
  mois = Wire.read();

  munite = mois & 0b00001111; // les unités sont les 4LSB
  mdizzaine = ((mois >> 4) & 0b0011); // les dizaines sont les 2 bits après

  recupererTemps[0].mois[1] = mdizzaine;
  recupererTemps[0].mois[0] = munite;
}

void recupererJours(void)
{
  int jour;
  int junite;
  int jdizzaine;

  Wire.beginTransmission(104);
  Wire.write(0x04);
  Wire.endTransmission(false);
  Wire.requestFrom(104, 1, true);
  jour = Wire.read();

  junite = jour & 0b00001111; // les unités sont les 4LSB
  jdizzaine = ((jour >> 4) & 0b0011); // les dizaines sont les 2 bits après

  recupererTemps[0].jour[1] = jdizzaine;
  recupererTemps[0].jour[0] = junite;
}

void recupererJoursEnLettres(void) {
  Wire.beginTransmission(104);
  Wire.write(0x03);
  Wire.endTransmission(false);
  Wire.requestFrom(104, 1, true);
  modif_jour_en_lettres = Wire.read();

  if (modif_jour_en_lettres == 7) modif_jour_en_lettres = 0; // Pour passer de dimanche a lundi (dans le RTC et non le menu de modification de temps)

  recupererTemps[0].jour_en_lettres[modif_jour_en_lettres];
}

void recupererHeures(void) {
  int heures;
  int hunite;
  int hdizaine;

  Wire.beginTransmission(104);
  Wire.write(0x02);
  Wire.endTransmission(false);
  Wire.requestFrom(104, 1, true); // le 1 fait que le bus est relaché après avoir envoyé les données
  heures = Wire.read();

  hunite = heures & 0b00001111; // les unités sont les 4LSB
  hdizaine = ((heures >> 4) & 0b0011); // les dizaines sont les 2 bits après

  recupererTemps[0].heure[1] = hdizaine;
  recupererTemps[0].heure[0] = hunite;
}

void recupererMinutes(void) {
  int minutes = 0;
  int munite = 0;
  int mdizaine = 0;

  Wire.beginTransmission(104);
  Wire.write(0x01);
  Wire.endTransmission(false);
  Wire.requestFrom(104, 1, true);

  minutes = Wire.read();

  munite = minutes & 0b00001111; // les unités sont les 4LSB
  mdizaine = minutes >> 4; // les dizaines sont les 3 bits après (le quatrième est égal à 0

  recupererTemps[0].minute[1] = mdizaine;
  recupererTemps[0].minute[0] = munite;
}

void recupererSecondes(void) {
  int secondes = 0;
  int sdizaine = 0;
  int sunite = 0;

  Wire.beginTransmission(104);
  Wire.write(0x00);
  Wire.endTransmission(false);
  Wire.requestFrom(104, 1, true);

  secondes = Wire.read();

  sunite = secondes & 0b00001111;
  sdizaine = secondes >> 4; // le 7ème bit ici est à zéro tant que on n'arrête pas l'oscillateur

  recupererTemps[0].secondes[1] = sdizaine;
  recupererTemps[0].secondes[0] = sunite;
}

void confirmerTemps()
{ //Conversion des valeurs en decimale vers le format BCD
  // exemple: 59 secondes, = 59 / 10 = 5, 5(0b101) << 4 = 0101 0000, 59 % 10 = 9(0b1001), 0101 0000 | 0000 1001 = bcd_seconde = 0b0101 1001 = 0x59 = 0d89
  int bcd_seconde = ((modification_seconde / 10) << 4) | (modification_seconde % 10);
  int bcd_minute = ((modification_minute / 10) << 4) | (modification_minute % 10);
  int bcd_heure = ((modification_heure / 10) << 4) | (modification_heure % 10);
  int bcd_jour = ((modification_jour / 10) << 4) | (modification_jour % 10);
  int bcd_mois = ((modification_mois / 10) << 4) | (modification_mois % 10);
  int bcd_annee = ((modification_annee / 10) << 4) | (modification_annee % 10);

  Wire.beginTransmission(104); // Adresse du RTC (x68)
  Wire.write(0x00); // Adresse du registre des secondes
  Wire.write(bcd_seconde);// Format BCD pour le temps 4LSB unité des secondes 3 bits après dizaine des secondes
  Wire.endTransmission();

  Wire.beginTransmission(104);
  Wire.write(0x01); // Adresse du registre des minutes
  Wire.write(bcd_minute); // 4LSB unité des minutes 3 bits après dizaine des minutes
  Wire.endTransmission();

  Wire.beginTransmission(104);
  Wire.write(0x02);  // Adresse du registre des heures
  Wire.write(bcd_heure); // 4LSB unité des minutes 2 bits après dizaine des minutes
  Wire.endTransmission();

  Wire.beginTransmission(104);
  Wire.write(0x03);  // Adresse du registre des jours en lettres
  Wire.write(modif_jour_en_lettres); // 4LSB unité des minutes 2 bits après dizaine des minutes
  Wire.endTransmission();

  Wire.beginTransmission(104);
  Wire.write(0x04);  // Adresse du registre des jours
  Wire.write(bcd_jour); // 4LSB unité des minutes 2 bits après dizaine des minutes
  Wire.endTransmission();

  Wire.beginTransmission(104);
  Wire.write(0x05);  // Adresse du registre des mois
  Wire.write(bcd_mois);
  Wire.endTransmission();

  Wire.beginTransmission(104);
  Wire.write(0x06);  // Adresse du registre des annees
  Wire.write(bcd_annee);
  Wire.endTransmission();
}