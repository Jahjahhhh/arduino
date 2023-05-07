// Appuyer sur le joystick pour changer la valeur que l'on modifie (variable compteurMode, qui est le compteur des variables, "mode minutes, mode secondes etc")
// Appuyer sur S2 pour incrementer et S3 pour decrementer
// Appuyer sur le joystick et S4 pour envoyer l'heure au RTC (confirmer la modification de l'heure)
#include <LiquidCrystal.h>
#include <Wire.h>
#include "definitions21.h"
#include "RTC.h"

// initialiser la librairie avec les bonnes broches pour s'interfacer en 4 bits paralleles
LiquidCrystal lcd(38, 40, 42, 44, 46, 48);  // branchement au SHIELD_20X

//************************************** CONFIGURATION   *****************************
void setup() {
  Serial.begin(115200);
  // configuration de départ de l'affichage LCD (nombre de colonnes et de lignes)
  lcd.begin(16, 2);

  pinMode(JOY_SW_PIN, INPUT);
  digitalWrite(JOY_SW_PIN, HIGH);  // classique pour pouvoir lire un LOW quand l'interrupteur est pressé

  pinMode(LCD_LED_PIN, OUTPUT);
  digitalWrite(LCD_LED_PIN, HIGH);  // par defaut on allume l'éclairage du LCD

  pinMode(MOUSTG_PIN, INPUT);
  digitalWrite(MOUSTG_PIN, HIGH);  // classique pour pouvoir lire un LOW quand l'interrupteur est pressé

  pinMode(MOUSTD_PIN, INPUT);
  digitalWrite(MOUSTD_PIN, HIGH);  // classique pour pouvoir lire un LOW quand l'interrupteur est pressé

  pinMode(MOUST3_PIN, INPUT);
  digitalWrite(MOUST3_PIN, HIGH);  // classique pour pouvoir lire un LOW quand l'interrupteur est pressé

  pinMode(MOUST4_PIN, INPUT);
  digitalWrite(MOUST4_PIN, HIGH);  // classique pour pouvoir lire un LOW quand l'interrupteur est pressé

  pinMode(SW_S2_PIN, INPUT);
  digitalWrite(SW_S2_PIN, HIGH);  // classique pour pouvoir lire un LOW quand l'interrupteur est pressé

  pinMode(SW_S3_PIN, INPUT);
  digitalWrite(SW_S3_PIN, HIGH);  // classique pour pouvoir lire un LOW quand l'interrupteur est pressé

  pinMode(SW_S4_PIN, INPUT);
  digitalWrite(SW_S4_PIN, HIGH);

  Wire.begin();
}

//********************** PROGRAMME PRINCIPAL  **********************************
void loop() {
  lcd.display();
  TestRTC();
}
//****************************** fonctions ***********************************
void TestRTC() { // En construction
  static bool premiereFois = true; // Permet d'aller chercher l'heure la première fois parce qu'on ne connait pas la valeur

  lcd.clear();
  while (digitalRead(SW_S4_PIN)) {
    if (premiereFois == true) {
      optionChangerTemps();
      recupererJoursEnLettres();
      recupererJours();
      recupererSecondes();
      recupererMinutes();
      recupererHeures();
      premiereFois = false;
    }

    recupererSecondes(); //  Les secondes changent entre chaque lecture

    if ((recupererTemps[0].secondes[1] == 0) && (recupererTemps[0].secondes[0] == 0)) { // si les dizaines et les unités des secondes sont à zéro, aller chercher les minutes puisqu'elles ont changé
      recupererMinutes();
      if ((recupererTemps[0].minute[1] == 0) && (recupererTemps[0].minute[0] == 0)) { // si les dizaines et les unités des minutes sont à zéro, aller chercher l'heure puisqu'elle a changé
        recupererHeures();
        if ((recupererTemps[0].heure[1] == 0) && (recupererTemps[0].heure[0] == 0)) { // si les dizaines et les unités des heures sont à zéro, aller chercher le jour puisqu'il a changé
          recupererJoursEnLettres();
          recupererJours();
          if ((recupererTemps[0].jour[1] == 0) && (recupererTemps[0].jour[0] == 0)) {
            recupererMois();
            if((recupererTemps[0].mois[1] == 0) && (recupererTemps[0].mois[0] == 0)) {
              recupererAnnee();
            }
          }
        }
      }
    }
    afficherTemps(NULL);
    delay(1000);
  }
}

void optionChangerTemps()
{
  bool changer, garder;
  byte compteurMode = 7;
  String mode[compteurMode] = {"Mois", "Jours   ", "Heures   ", "Min   ", "Sec   "};

  do
  { // Garder l'heure en mémoire?
    lcd.setCursor(0, 0); lcd.print("S2: Changer");
    lcd.setCursor(0, 1); lcd.print("S3: Garder");
    changer = digitalRead(SW_S2_PIN);
    garder = digitalRead(SW_S3_PIN);
    delay(150);
  } while (changer && garder); // Tant que le user n'a pas choisit S2 ou S3.
  lcd.clear();

  if (changer == LOW)
  {
    modification_rtc = true;
    do
    {
      if (compteurMode == 7) compteurMode = 0;
      do
      {
        changerTemps(compteurMode);
      } while (digitalRead(JOY_SW_PIN));
      delay(150); while(!digitalRead(JOY_SW_PIN)); delay(150);
      compteurMode++;
      lcd.clear();
    } while (digitalRead(SW_S4_PIN) == HIGH);
    if(modification_mois == 0) modification_mois = 1; // Le mois 0 n'existe pas, si l'utilisateur ne configure pas la variable du mois, on la met a janvier (modification_mois = 1)
    confirmerTemps();
  }
  modification_rtc = false;
  lcd.clear();
}

void changerTemps(byte compteurMode)
{
  switch (compteurMode)
  {
    case 0:
      if (digitalRead(SW_S2_PIN) == LOW) modification_jour++;
      else if (digitalRead(SW_S3_PIN) == LOW) modification_jour--;
      recupererTemps[0].jour[0] = modification_jour % 10;
      recupererTemps[0].jour[1] = modification_jour / 10;
      break;
    case 1:
      if (digitalRead(SW_S2_PIN) == LOW) modification_mois++;
      else if (digitalRead(SW_S3_PIN) == LOW) modification_mois--;
      recupererTemps[0].mois[0] = modification_mois % 10;
      recupererTemps[0].mois[1] = modification_mois / 10;
      break;
    case 2:
      if(digitalRead(SW_S2_PIN) == LOW) modification_annee++;
      else if(digitalRead(SW_S3_PIN) == LOW) modification_annee--;
      recupererTemps[0].annee[0] = modification_annee % 10;
      recupererTemps[0].annee[1] = modification_annee / 10;
      break;
    case 3:
      if (digitalRead(SW_S2_PIN) == LOW) modif_jour_en_lettres++;
      else if (digitalRead(SW_S3_PIN) == LOW) modif_jour_en_lettres--;
      break;
    case 4:
      if (digitalRead(SW_S2_PIN) == LOW) modification_heure++;
      else if (digitalRead(SW_S3_PIN) == LOW) modification_heure--;
      recupererTemps[0].heure[0] = modification_heure % 10;
      recupererTemps[0].heure[1] = modification_heure / 10;
      break;
    case 5:
      if (digitalRead(SW_S2_PIN) == LOW) modification_minute++;
      else if (digitalRead(SW_S3_PIN) == LOW) modification_minute--;
      recupererTemps[0].minute[0] = modification_minute % 10;
      recupererTemps[0].minute[1] = modification_minute / 10;
      break;
    case 6:
      if (digitalRead(SW_S2_PIN) == LOW) modification_seconde++;
      else if (digitalRead(SW_S3_PIN) == LOW) modification_seconde--;
      recupererTemps[0].secondes[0] = modification_seconde % 10;
      recupererTemps[0].secondes[1] = modification_seconde / 10;
  }
  loopback(); // voir dans RTC.h
  jours_dans_mois(); // Pour savoir si on s'arrete a 28, 29 ,30 ou 31 selon le mois

  afficherTemps(compteurMode);
  delay(100);
}

void afficherTemps(byte compteurMode) { // Va chercher dans notre structure l'heure et l'affiche au moniteur série
  // RTC (affichage de l'heure) RTC* (affichage de l'heure quand on la modifie)
  lcd.setCursor(0, 0);
  lcd.print("RTC"); 
  if(modification_rtc == true) lcd.print("*   "); // Afficher un * si on est en train de régler l'heure.
  else lcd.print("    ");
  // jours
  if(recupererTemps[0].jour[1] == 0 && recupererTemps[0].jour[0] == 0 && modification_rtc == true) lcd.print("jj"); 
  else {lcd.print(recupererTemps[0].jour[1]); lcd.print(recupererTemps[0].jour[0]);}
  if(compteurMode == 0 && modification_rtc == true) lcd.print("*"); // Si jour = 0, afficher jj et afficher * pour la modif de la valeur
  // mois
  lcd.print("/");
  if(recupererTemps[0].mois[1] == 0 && recupererTemps[0].mois[0] == 0 && modification_rtc == true) lcd.print("mm"); 
  else {lcd.print(recupererTemps[0].mois[1]); lcd.print(recupererTemps[0].mois[0]);}
  if(compteurMode == 1 && modification_rtc == true) lcd.print("*"); // Si mois = 0, afficher mm et * pour la modif de la valeur
  // annee
  lcd.print("/");
  if(recupererTemps[0].annee[1] == 0 && recupererTemps[0].annee[0] == 0 && modification_rtc == true) lcd.print("aa"); 
  else {lcd.print(recupererTemps[0].annee[1]); lcd.print(recupererTemps[0].annee[0]);}
  if(compteurMode == 2 && modification_rtc == true) lcd.print("*"); // Si annee = 0, afficher aa et * pour la modif de la valeur
  
  lcd.setCursor(0, 1);
  // jours de la semaine en lettres
  lcd.print(recupererTemps[0].jour_en_lettres[modif_jour_en_lettres]);
  if(compteurMode == 3 && modification_rtc == true) lcd.print("*   "); 
  else lcd.print("    "); //afficher * si on est en train de travailler avec les jours de la semaine (compteurMode = 3)
  // heures
  if(recupererTemps[0].heure[1] == 0 && recupererTemps[0].heure[0] == 0 && modification_rtc == true) lcd.print("hh"); 
  else {lcd.print(recupererTemps[0].heure[1]); lcd.print(recupererTemps[0].heure[0]);}
  if(compteurMode == 4 && modification_rtc == true) lcd.print("*"); // etc 
  // minutes
  lcd.print(":");
  if(recupererTemps[0].minute[1] == 0 && recupererTemps[0].minute[0] == 0 && modification_rtc == true) lcd.print("mm"); 
  else {lcd.print(recupererTemps[0].minute[1]); lcd.print(recupererTemps[0].minute[0]);}
  if(compteurMode == 5 && modification_rtc == true) lcd.print("*");
  // secondes
  lcd.print(":");
  if(recupererTemps[0].secondes[1] == 0 && recupererTemps[0].secondes[0] == 0 && modification_rtc == true) lcd.print("ss"); 
  else {lcd.print(recupererTemps[0].secondes[1]); lcd.print(recupererTemps[0].secondes[0]);}
  if(compteurMode == 6 && modification_rtc == true) lcd.print("*");
}