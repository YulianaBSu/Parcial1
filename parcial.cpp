// Definicion de pines para un Arduino Uno
int pinData = 11;   // Pin de datos
int pinLatch = 8;  // Pin de almacenamiento 
int pinClock = 12;  // Pin de reloj
int opc = 0;

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
  menu();
}

void loop(){
  if(Serial.available() > 0){
  opc = Serial.read()- '0';
  
  if(opc==1){
	for (int n=0; n<8; n++){
    verificacion();
	}
  }
  
  else if(opc==2){
    Serial.println("Ingreso de patron");
    int fila, columna;
    while (Serial.available() == 0);
    fila = Serial.parseInt();
    while (Serial.available() == 0);
    columna = Serial.parseInt();
    Serial.println("Ingrese posicion de los LEDS");
	Serial.println("Indique numero de fila y columna (1-8) separado por un espacio");
	Serial.println("Ej: (1 2)");
	if (fila >= 1 && fila <= 8 && columna >= 1 && columna <= 8) {
    imagen(fila, columna);
	}
	else {
	  Serial.println("Opcion invalida. Por favor ingresa valores entre 1 y 8.");
	}
	digitalWrite(pinLatch, LOW);
    shiftOut(pinData, pinClock, MSBFIRST, B00000000);
    digitalWrite(pinLatch, HIGH);
  }
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
}


void patrones(){
  Serial.println("Patron");
}

void publik(){
  Serial.println("a.Verificar LEDs");
  Serial.println("b.Imagen de prueba");
  Serial.println("c.Secuencia de patrones");
  
}

