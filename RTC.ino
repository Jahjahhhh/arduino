/*
  Programme pour régler et afficher l'heure dans le DS1307 (RTC)
  par Jia Peng XU
  Date de la dernière modification: 4 octobre 2023
  datasheet: https://www.analog.com/media/en/technical-documentation/data-sheets/DS1307.pdf
  Wire.h   : https://www.arduino.cc/reference/en/language/functions/communication/wire/

  Réglage du temps:
    S2: Decrementer
    S3: Incrementer
    JOYSTICK: appuyer pour passer à la prochaine unite de temps
      (secondes, minutes, heures, jour de la semaine(lun-dim), jour(0-31), mois, année)

  Pour confirmer et envoyer le temps aux registres du RTC:
    Maintenir S4 et appuyer sur le JOYSTICK (réessayer si ça ne fonctionne pas au premier coup)

  Navigation du "manuel" (les instructions)
    Les directions sont relatives par rapport au LCD. (et non par rapport au robot)
    Droite du joystick == droite du LCD != droite du robot
      Ouvrir le manuel (ne fonctionne que lorsqu'on règle l'heure): joystick vers le haut
      Prochaine page du manuel: joystick à droite
      Page précédente du manuel: joystick à gauche
      Quitter le manuel: joystick vers le bas
*/

#include "setup.h"
#include "fonctionsRTC.h"
#include "definitions21.h"

void setup() {
  LeSetup();
  menu();
}

void loop() {
  horloge();
}
