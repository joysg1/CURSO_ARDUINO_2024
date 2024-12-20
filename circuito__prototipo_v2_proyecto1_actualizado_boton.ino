#include <LiquidCrystal.h>

LiquidCrystal lcd(5, 6, 9, 10, 11, 12);

float tempCap, volt, tempConv;
int tempFin;
int buttonState = 0;
int lastButtonState = HIGH; // Estado anterior del botón (asumimos pull-up, por lo que HIGH es el estado no presionado)
bool motorState = false;   // Estado del motor: false = apagado, true = encendido

void setup() {
  pinMode(A0, INPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(13, INPUT_PULLUP); // Configuración con resistencia de pull-up interna
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  // Lee el estado actual del botón
  buttonState = digitalRead(13);

  // Verifica si hubo un cambio en el estado del botón
  if (buttonState == LOW && lastButtonState == HIGH) { // Cambio de HIGH a LOW
    motorState = !motorState; // Alterna el estado del motor
    delay(50); // Anti-rebote
  }

  lastButtonState = buttonState; // Actualiza el estado anterior del botón

  // Lee y calcula la temperatura
  tempCap = analogRead(A0);
  volt = tempCap * (5.0 / 1024.0);
  tempConv = (volt - 0.5) * 100;
  tempFin = tempConv;

  // Control del motor basado en `motorState`
  if (motorState) {
    digitalWrite(7, HIGH);  // Motor encendido
    digitalWrite(8, LOW);
  } else {
    digitalWrite(7, LOW);   // Motor apagado
    digitalWrite(8, LOW);
  }

  // Control de los LEDs basado en la temperatura
  if (tempFin >= 28) {
    digitalWrite(4, HIGH);  // LED de calor encendido
    digitalWrite(3, LOW);   // LED templado apagado
    digitalWrite(2, LOW);   // LED frío apagado
    Serial.println("--- TEMPERATURA CALIENTE --- ");
    lcd.print(tempFin);
    lcd.print(" C");
    lcd.print(" CALOR ");
    delay(1000);
  } else if (tempFin < 28 && tempFin >= 25) {
    digitalWrite(3, HIGH);  // LED templado encendido
    digitalWrite(2, LOW);   // LED frío apagado
    digitalWrite(4, LOW);   // LED de calor apagado
    Serial.println("--- TEMPERATURA TEMPLADA --- ");
    lcd.print(tempFin);
    lcd.print(" C");
    lcd.print(" TEMPLADO ");
    delay(1000);
  } else {
    digitalWrite(2, HIGH);  // LED frío encendido
    digitalWrite(3, LOW);   // LED templado apagado
    digitalWrite(4, LOW);   // LED de calor apagado
    Serial.println("--- TEMPERATURA FRIA --- ");
    lcd.print(tempFin);
    lcd.print(" C");
    lcd.print(" FRIO ");
    delay(1000);
  }

 
 
  
  

  
  lcd.clear(); // Limpia la pantalla LCD para la próxima lectura
}







