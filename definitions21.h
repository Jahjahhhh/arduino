/*************REGISTRES DU DS1306****************/
#define REGISTRE_SEC 0x00
#define REGISTRE_MIN 0x01
#define REGISTRE_HRS 0x02
#define REGISTRE_JRS 0x03
#define REGISTRE_DATE 0x04
#define REGISTRE_MOIS 0x05
#define REGISTRE_AN 0x06
/*************DS1306(RTC)****************/
#define RTC 104
#define SECONDES 1
#define MINUTES 2
#define HEURES 3
#define JOURS 4
#define DATE 5
#define MOIS 6
#define ANNEES 7

#define LCD_LED_PIN   A15   // Pin numérique pour controler l'éclairage du LCD (active HIGH)

// Joystick
#define JOY_SW_PIN    28    // Pin numérique pour lire le bouton poussoir
#define JOY_X_PIN     5     // Pin analogique pour lire l'axe des X
#define JOY_Y_PIN     4     // Pin analogique pour lire l'axe des 

//  Switch S2, S3 et S4
#define SW_S2_PIN     24    // Pin numérique de la switch S2
#define SW_S3_PIN     26    // Pin numérique de la switch S3
#define SW_S4_PIN     18
