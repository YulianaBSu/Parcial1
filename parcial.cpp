// Definicion de pines para un Arduino Uno
byte pinData = 11;   // Pin de datos
byte pinLatch = 8;  // Pin de almacenamiento 
byte pinClock = 12;  // Pin de reloj
byte opc = 0;
const byte filas = 8;
const byte columnas = 8;
unsigned long duracionc;
unsigned long inicio;

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
	for (byte n=0; n<8; n++){
    verificacion();
	}
  }
  
  else if(opc==2){
    byte fila, columna, rep, repi=0;
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
    
    Serial.println("Ingrese el tiempo de duracion de ciclos en milisegundos:");
    while (Serial.available() == 0);
    unsigned long duracionc = Serial.parseInt();     
    Serial.print("Mostrando patrones definidos");    
    patrones(duracionc);
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





void imagen(byte fila, byte columna){
  Serial.println("Patron ingresado");
  digitalWrite(pinLatch, LOW);
  shiftOut(pinData, pinClock, MSBFIRST, ~(B00000001 << columna-1)); 
  shiftOut(pinData, pinClock, MSBFIRST, B10000000 >> fila-1); 
  digitalWrite(pinLatch, HIGH);
  delay(2000);
  digitalWrite(pinLatch, LOW);
  shiftOut(pinData, pinClock, MSBFIRST, B00000000);
  digitalWrite(pinLatch, HIGH);
}


void patrones(unsigned long duracion) {
  byte** leds = new byte*[filas]; 
  for (byte i = 0; i < filas; i++) {
    leds[i] = new byte[columnas]();
  }
  unsigned long inicio;
//Patron1
  inicio = millis();
  while (millis() - inicio < duracion) { 
  for (byte i = 0; i < filas; i++) {
    for (byte j = i; j < columnas - i; j++) {
      encenderLED(i + 4, j); 
      encenderLED(filas - i - 5, j); 
    }
  }
  }
  
//Patron2
  inicio = millis();
  while (millis() - inicio < duracion) { 
  for(byte i = 0; i < filas; i++) {
    encenderLED(i , i); 
    encenderLED(i, filas - i - 1); 
      digitalWrite(pinLatch, LOW);
  shiftOut(pinData, pinClock, MSBFIRST, B11111111); 
  shiftOut(pinData, pinClock, MSBFIRST, B00000000); 
  digitalWrite(pinLatch, HIGH);
    }
    
  }
  
//Patron3
  inicio = millis();
  while (millis() - inicio < duracion) { 
  for (byte i = 0; i < filas; i++) {
        for (byte j = 0; j < columnas; j++) {
            // Patrón de marcado
            if (
                (i==0 || i==1 || i==4 || i==5) &&
                (j==0 || j==1 || j==3 || j==4 || j==6 || j==7)
            ) 
            {
                encenderLED(i , j);
            }
            else if (
                (i==2 || i==3 || i==6 || i==7) &&
                (j==1 || j==2 || j==4 || j==5 || j==7)
            ) {
                encenderLED(i , j);;
            }
        }
    }
  }

//Patron4
  inicio = millis();
  while (millis() - inicio < duracion) { 
  for (byte i = 0; i < 4; i++) {
    for (byte j = 0; j < 4; j++) {
      encenderLED(i, i + j);
    }
  }

  for (byte i = 4; i < filas; i++) {
    for (byte j = 0; j < 4; j++) {
      encenderLED(i, (j - i + columnas - 1));
    }
  }
  }
    // Apagar todos los LEDs
  for (byte i = 0; i < filas; i++) {
    for (byte j = 0; j < columnas; j++) {
      apagarLEDs(i, j); }
  }
  

  // Liberar memoria
  liberarMemoria(leds);
}


void publik(){
  Serial.println("1.Verificar LEDs");
  
  Serial.println("b.Imagen de prueba");
  Serial.println("c.Secuencia de patrones");
  
}
void encenderLED(byte fila, byte columna) {
  digitalWrite(pinLatch, LOW);
  shiftOut(pinData, pinClock, MSBFIRST, ~(1 << (7 - fila))); 
  shiftOut(pinData, pinClock, MSBFIRST, B10000000 >> columna);   
  digitalWrite(pinLatch, HIGH);
}

void liberarMemoria(byte** leds) {
  for (byte i = 0; i < filas; i++) {
    delete[] leds[i];
  }
  delete[] leds;
}

void apagarLEDs(byte fila, byte columna) {
  digitalWrite(pinLatch, LOW);
  shiftOut(pinData, pinClock, MSBFIRST, ~(1 << (7 - fila))); 
  shiftOut(pinData, pinClock, MSBFIRST, B01111111 >> columna);  // Apagar todos los LEDs
  digitalWrite(pinLatch, HIGH);
}
