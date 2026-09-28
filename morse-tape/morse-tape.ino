const int LED = 12;
const int Button = 3;

// Seuils de temps (en millisecondes) 
const int seuilPointTiret = 250; 
const int seuilLettre = 600;     // Feu vert pour la LETTRE suivante (affiche "/")
const int seuilMot = 1500;       // Feu vert pour le MOT suivant (affiche "#")
const int seuilPhrase = 5000;    // Traduction complète de la phrase (5 secondes)

unsigned long tempsAppui = 0;
unsigned long tempsRelache = 0;
bool etatPrecedent = HIGH;       
String sequenceEnCours = "";
String phraseEnCours = "";       
bool lettreValidee = true;
bool espaceValide = true;
bool phraseValidee = true;       

// Dictionnaire de traduction (Lettres + Chiffres)
const int nbCaracteres = 36;
const String codeMorse[nbCaracteres] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", 
  "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",   
  "..-", "...-", ".--", "-..-", "-.--", "--..",                          
  "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----." 
};
const char alphabet[nbCaracteres] = {
  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
  'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
  'u', 'v', 'w', 'x', 'y', 'z',
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
};

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(Button, INPUT_PULLUP); 
  
  Serial.begin(9600);
  Serial.println("Pret a ecouter !");
  Serial.println("- Un '/' apparait = tu peux taper la LETTRE suivante.");
  Serial.println("- Un '#' apparait = tu peux taper le MOT suivant.");
  Serial.println("- Attends 5s pour voir la traduction.");
  Serial.println("---------------------------------------------------------");
}

void loop() {
  bool etatActuel = digitalRead(Button);
  unsigned long tempsActuel = millis(); 

  // 1. Le bouton vient d'être appuyé
  if (etatActuel == LOW && etatPrecedent == HIGH) {
    if (tempsActuel - tempsRelache > 50) { // Anti-rebond
      tempsAppui = tempsActuel;
      lettreValidee = false;
      espaceValide = false;
      phraseValidee = false;
      digitalWrite(LED, HIGH); 
    }
  }
  
  // 2. Le bouton vient d'être relâché
  else if (etatActuel == HIGH && etatPrecedent == LOW) {
    if (tempsActuel - tempsAppui > 50) { 
      tempsRelache = tempsActuel;
      digitalWrite(LED, LOW); 
      
      unsigned long dureeAppui = tempsRelache - tempsAppui;
      
      // Affichage du morse en direct
      if (dureeAppui < seuilPointTiret) {
        sequenceEnCours += ".";
        Serial.print("."); 
      } else {
        sequenceEnCours += "-";
        Serial.print("-"); 
      }
    }
  }

  // 3. Gestion des pauses
  if (etatActuel == HIGH) {
    unsigned long dureePause = tempsActuel - tempsRelache;

    // Fin d'une lettre (600ms)
    if (!lettreValidee && dureePause > seuilLettre) {
      char lettre = traduireSequence(sequenceEnCours);
      phraseEnCours += lettre; 
      
      Serial.print("/"); // TON REPERE VISUEL : la lettre est finie !
      
      sequenceEnCours = ""; 
      lettreValidee = true;
    }

    // Fin d'un mot (1.5s)
    if (lettreValidee && !espaceValide && dureePause > seuilMot) {
      phraseEnCours += " "; // Ajoute l'espace dans la phrase en latin
      
      Serial.print("#"); // TON 2EME REPERE : le mot est fini !
      
      espaceValide = true;
    }

    // Fin de la phrase (5s)
    if (lettreValidee && espaceValide && !phraseValidee && dureePause > seuilPhrase) {
      Serial.println();              
      Serial.println(phraseEnCours); // Affiche la phrase latine complète
      Serial.println();              
      
      phraseEnCours = "";            
      phraseValidee = true;
    }
  }

  etatPrecedent = etatActuel; 
}

// Fonction qui cherche la lettre et la renvoie
char traduireSequence(String sequence) {
  for (int i = 0; i < nbCaracteres; i++) {
    if (codeMorse[i] == sequence) {
      return alphabet[i]; 
    }
  }
  return '?'; 
}