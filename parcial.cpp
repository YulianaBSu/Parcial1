// Definición de pines para un Arduino Uno
int pinData = 11;   // Pin de datos
int pinLatch = 8;  // Pin de almacenamiento 
int pinClock = 12;  // Pin de reloj
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
  opc == Serial.parseInt();
  
  if(opc==1){
    verificacion();
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


void verificacion(){
  Serial.println("Encendiendo LEDs en matriz");
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
