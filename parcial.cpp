// Definicion de pines para un Arduino Uno
int pinData = 11;   // Pin de datos
int pinLatch = 8;  // Pin de almacenamiento 
int pinClock = 12;  // Pin de reloj
int opc = 0;
const int filas = 8;
const int columnas = 8;

void menu();
void verificacion();
void imagen();
void patrones();
void publik();

void setup(){
  Serial.begin(9600);
  // Configurar pines como salida
  pinMode(pinData, OUTPUT);
  pinMode(pinLatch, OUTPUT);
  pinMode(pinClock, OUTPUT);
}

void loop(){
  menu();
  while (Serial.available() == 0);
  opc = Serial.parseInt();
  
  if(opc==1){
	for (int n=0; n<8; n++){
    verificacion();
	}
  }
  
  else if(opc==2){
    int fila, columna, rep, repi=0;
    Serial.println("Ingrese cantidad de posiciones que desea indicar: ");
    while (Serial.available() == 0);
    rep = Serial.parseInt();
    
    while (repi < rep) {
      
    Serial.println("Ingrese posicion de los LEDS");
	Serial.println("Indique numero de fila y columna (1-8) separado por un espacio");
	Serial.println("Ej: (1 2)");
      
    while (Serial.available() == 0);
    columna = Serial.parseInt();
    while (Serial.available() == 0);
    fila = Serial.parseInt();

	if (fila >= 1 && fila <= 8 && columna >= 1 && columna <= 8) {
    imagen(fila, columna);
    repi++;
	}
	else {
	  Serial.println("Opcion invalida. Por favor ingresa valores entre 1 y 8.");
	}
	digitalWrite(pinLatch, LOW);
    shiftOut(pinData, pinClock, MSBFIRST, B00000000);
    digitalWrite(pinLatch, HIGH);
  }
    Serial.println("Ejecucion finalizada.");
    return;
  }
  
  else if(opc==3){
    
    Serial.print("Mostrando patrones definidos");
    patrones();
  }
}
void menu(){
  Serial.println("MENU PRINCIPAL");
  Serial.println("1. Encender todos los LEDs");
  Serial.println("2. Ingresar patron");
  Serial.println("3. Visualizar patrones");
  Serial.println("4. Ejecutar todos los anteriores");
  Serial.println("Ingrese una opcion: ");
  
}


void verificacion(){ //Funcion para encender todos los LEDs
  Serial.println("Encendiendo LEDs en matriz");
  digitalWrite(pinLatch, LOW);
  shiftOut(pinData, pinClock, MSBFIRST, 255); //Encender leds
  digitalWrite(pinLatch, HIGH);
  delay(2000);
  digitalWrite(pinLatch, LOW);
  shiftOut(pinData, pinClock, MSBFIRST, 0); //Apagar leds
  digitalWrite(pinLatch, HIGH);
  delay(2000);
}





void imagen(int fila, int columna){
  Serial.println("Patron ingresado");
  digitalWrite(pinLatch, LOW);
  shiftOut(pinData, pinClock, MSBFIRST, ~(B00000001 << fila-1)); 
  shiftOut(pinData, pinClock, MSBFIRST, B10000000 >> columna-1); 
  digitalWrite(pinLatch, HIGH);
  delay(2000);
  digitalWrite(pinLatch, LOW);
  shiftOut(pinData, pinClock, MSBFIRST, B00000000);
  digitalWrite(pinLatch, HIGH);
}


void patrones() {
  int** leds = new int*[filas]; 
  for (int i = 0; i < filas; i++) {
    leds[i] = new int[columnas]();
  }
//Patron1
  for (int i = 0; i < filas; i++) {
    for (int j = i; j < columnas - i; j++) {
      encenderLED(i + 4, j); 
      encenderLED(filas - i - 5, j); 
    }
  }
  
  delay(1000);
  
  digitalWrite(pinLatch, LOW);
  shiftOut(pinData, pinClock, MSBFIRST, B11111111); 
  shiftOut(pinData, pinClock, MSBFIRST, B00000000);
  digitalWrite(pinLatch, HIGH);

  // Liberar memoria
  liberarMemoria(leds);
}


void publik(){
  Serial.println("a.Verificar LEDs");
  Serial.println("b.Imagen de prueba");
  Serial.println("c.Secuencia de patrones");
  
}
void encenderLED(int fila, int columna) {
  digitalWrite(pinLatch, LOW);
  shiftOut(pinData, pinClock, MSBFIRST, ~(1 << (7 - fila))); 
  shiftOut(pinData, pinClock, MSBFIRST, B10000000 >> columna);   
  digitalWrite(pinLatch, HIGH);
}

void liberarMemoria(int** leds) {
  for (int i = 0; i < filas; i++) {
    delete[] leds[i];
  }
  delete[] leds;
}

