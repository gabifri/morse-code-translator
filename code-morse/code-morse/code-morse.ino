int digitpin = 12; //set your pin led here

//On définie le point et le trait pour simplifier le code par la suite

int point(){
  Serial.print("."); //on écrit dans la console le point
  digitalWrite(digitpin, HIGH); //On allume la led
  delay(200);  // un delais court pour le point
  digitalWrite(digitpin, LOW);
  delay(200);
}

int line(){
  Serial.print("-");
  digitalWrite(digitpin, HIGH);
  delay(400); // un delai long pour le trait
  digitalWrite(digitpin, LOW);
  delay(400);
}

//on définit l'alphabet morse lettre par lettre

int a(){
  point(); //on appel notre fonction point pour allumé la led de manière courte et ecrire un point dans le console
  line();
}
int b(){
  line();
  point();
  point();
  point();
}
int c(){
  line();
  point();
  line();
  point();
}
int d(){
  line();
  point();
  point();
}
int e(){
  point();
}
int f(){
  point();
  point();
  line();
  point();
}
int g(){
  line();
  line();
  point();
}
int h(){
  point();
  point();
  point();
  point();
}
int I(){
  point();
  point();
}
int j(){
  point();
  line();
  line();
  line();
}
int k(){
  line();
  point();
  line();
}
int l(){
  point();
  line();
  point();
  point();
}
int m(){
  line();
  line();
}
int n(){
  line();
  point();
}
int o(){
  line();
  line();
  line();
}
int p(){
  point();
  line();
  line();
  point();
}
int q(){
  line();
  line();
  point();
  line();
}
int r(){
  point();
  line();
  point();
}
int s(){
  point();
  point();
  point();
}
int t(){
  line();
}
int u(){
  point();
  point();
  line();
}
int v(){
  point();
  point();
  point();
  line();
}
int w(){
  point();
  line();
  line();
}
int x(){
  line();
  point();
  point();
  line();
}
int y(){
  line();
  point();
  line();
  line();
}
int z(){
  line();
  line();
  point();
  point();
}
int zero(){
  line();
  line();
  line();
  line();
  line();
}
int one(){
  point();
  line();
  line();
  line();
  line();
}
int two(){
  point();
  point();
  line();
  line();
  line();
}
int three(){
  point();
  point();
  point();
  line();
  line();
}
int four(){
  point();
  point();
  point();
  point();
  line();
}
int five(){
  point();
  point();
  point();
  point();
  point();
}
int six(){
  line();
  point();
  point();
  point();
  point();
}
int seven(){
  line();
  line();
  point();
  point();
  point();
}
int eight(){
  line();
  line();
  line();
  point();
  point();
}
int nine(){
  line();
  line();
  line();
  line();
  point();
}

int space(){
  Serial.print(" ");
  delay(600);
}

//on crée une fonction qui parcours lettre par lettre notre phrase et vient trouver à quel code morse correspond chaque lettre
void morse(String sentence) {
  Serial.print(sentence); //on écrit la phrase latine dans la console
  Serial.println(""); //on retourne a la ligne
  
  sentence.toLowerCase(); //on passe la phrase en minuscule

  // on répéte cette boucle autant de fois qu'il y a de caractère
  for (int i = 0; i < sentence.length(); i++) {
    char cases = sentence.charAt(i);

    //on viens comparé chaque caractère de la phrase a notre alphabet
    switch (cases) {
      case 'a': a(); break; //si le caractère i correspond à "a" on s'arrête
      case 'b': b(); break;
      case 'c': c(); break;
      case 'd': d(); break;
      case 'e': e(); break;
      case 'f': f(); break;
      case 'g': g(); break;
      case 'h': h(); break;
      case 'i': I(); break;
      case 'j': j(); break;
      case 'k': k(); break;
      case 'l': l(); break;
      case 'm': m(); break;
      case 'n': n(); break;
      case 'o': o(); break;
      case 'p': p(); break;
      case 'q': q(); break;
      case 'r': r(); break;
      case 's': s(); break;
      case 't': t(); break;
      case 'u': u(); break;
      case 'v': v(); break;
      case 'w': w(); break;
      case 'x': x(); break;
      case 'y': y(); break;
      case 'z': z(); break;
      case '0': zero(); break;
      case '1': one(); break;
      case '2': two(); break;
      case '3': three(); break;
      case '4': four(); break;
      case '5': five(); break;
      case '6': six(); break;
      case '7': seven(); break;
      case '8': eight(); break;
      case '9': nine(); break;
      case ' ': space(); break; 
      default: //si ça ne correspond a rien on considère que c'est un caractère spécial et on met une erreur
        Serial.println(" ");
        Serial.print("Error : special case forbiden");
        Serial.println("");
        break;
    }
    delay(400);
  }
}

void setup() {
  Serial.begin(9600); //on initialise la console
  Serial.print("Hi - Code by VLTV"); //on fait un teste pour vérifier que la console fonctionne
  pinMode(digitpin, OUTPUT);
}

void loop() {
  morse("We Love Arduino :)"); //on appel notre fonction pour traduire notre phrase en morse
  Serial.println("");
}
