/*************Définition des paramètres****************/
#define MAX_DISTANCE      200   // Distance pour laquelle nous desirons attendre en centimètres. 
                                // Possibilité d'atteindre 500, mais plus de délai
#define VIT_RAPIDE        222   // Vitesse Max
#define VIT_MOYENNE       120   // Vitesse intermediaire
#define VIT_LENTE         90    // Vitesse basse

#define VIT_RANGE         30    // Variation de vitesse acceptée


/*************Définition des Pins****************/
// Matrice de LED 8x8 MAX7219
#define SDCARD_CS_PIN   45 
#define MATRIX_CS_PIN   53  // Pin CS vers la matrice de LED

// Senseur de distance à ultrasons
#define TRIGGER_PIN   35    // Pin du déclencheur du senseur à ultrasons
#define ECHO_PIN      33    // Pin de la sortie du senseur à ultrasons

// LCD         
#define LCD_LED_PIN   A15   // Pin numérique pour controler l'éclairage du LCD (active HIGH)

// Moustaches
#define MOUSTG_PIN    A11   // Pin numérique de la moustache gauche
#define MOUSTD_PIN    A12   // Pin numérique de la moustache droite
#define MOUST3_PIN  A13 // Pin numérique de la moustache supplementaire 3
#define MOUST4_PIN  A14 // Pin numérique de la moustache supplementaire 4
// Joystick
#define JOY_SW_PIN    28    // Pin numérique pour lire le bouton poussoir
#define JOY_X_PIN     5     // Pin analogique pour lire l'axe des X
#define JOY_Y_PIN     4     // Pin analogique pour lire l'axe des Y


#define PILE_PIN   7   // broche avec diviseur de tension pour mesurer la pile

// LED RGB
#define RGB_R_PIN     13     // Pin numérique de la LED rouge (partagé avec la sortie 2 du moteur 4)
#define RGB_G_PIN     12    // Pin numérique de la LED verte
#define RGB_B_PIN     5    // Pin numérique de la LED bleue

//  Switch S2, S3 et S4
#define SW_S2_PIN     24    // Pin numérique de la switch S2
#define SW_S3_PIN     26    // Pin numérique de la switch S3
#define SW_S4_PIN     18

// LED D7 et D8
#define LED_D7_PIN    43    // Pin numérique de la LED D7 BLEUE
#define LED_D8_PIN    47    // Pin numérique de la LED D8 JAUNE

// Moteurs
#define MOTR_SLEEP     36    // Désactiver moteurs à LOW
#define MOTR_FL1       11    // Moteur Avant Gauche 1
#define MOTR_FL2       10    // Moteur Avant Gauche 2
#define MOTR_BL1       8     // Moteur Arrière Gauche 1
#define MOTR_BL2       9     // Moteur Arrière Gauche 2
#define MOTR_BR1       7     // Moteur Avant Droite 1
#define MOTR_BR2       6     // Moteur Avant Droite 2
#define MOTR_FR1       5     // Moteur Avant Droite 1 Partagé avec RED_PIN (PWM #5)
#define MOTR_FR2       4     // Moteur Avant Droite 2
