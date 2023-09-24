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
    Serial.print("Ingrese posicion de los LEDS");
    imagen();
  }
  else if(opc==3){
    Serial.print("Mostrando patrones definidos");
    patrones();
  }
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





void imagen(){
  Serial.println("Patron ingresado");
}


void patrones(){
  Serial.println("Patron");
}

void publik(){
  Serial.println("a.Verificar LEDs");
  Serial.println("b.Imagen de prueba");
  Serial.println("c.Secuencia de patrones");
  
}

