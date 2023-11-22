#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidMenu.h>
#include <Encoder.h>
#include <InterfazMenu.h>

// Configuración del encoder y pulsador
Encoder myEncoder(2, 3);
#define encoderButtonPin 6
long oldPosition = -999;

// Configuración del LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Configuración de la interfaz del menú
LiquidSystem sys;
InterfazMenu interfazMenu(myEncoder.read(), myEncoder.read(), encoderButtonPin, sys, lcd);

void setup() {
  // lcd.begin(16, 2);
  lcd.init();
  pinMode(encoderButtonPin, INPUT_PULLUP);

  interfazMenu.mensajeInicial();
  delay(1000);
  interfazMenu.configurarMenuPrincipal();
  oldPosition = myEncoder.read();
}

void selectOption(){
  if(digitalRead(encoderButtonPin)==LOW){
    interfazMenu._menuPrincipal.call_function(1);
    delay(500);
  }
}

void loop() {
  long newPosition = myEncoder.read();
  if (newPosition != oldPosition) {
    if (newPosition > oldPosition)
      interfazMenu._menuPrincipal.switch_focus(false);
    else
      interfazMenu._menuPrincipal.switch_focus(true);
    
    oldPosition = newPosition;
    //Serial.println(newPosition);
    // lcd.setCursor(0, 0);
    // lcd.print(newPosition);
    
  }
  

  // encoderPos = myEncoder.read();
  // encoderButtonState = digitalRead(encoderButtonPin);

  // if (encoderPos != lastEncoderPos) {
  //   sys.update();
  // }

  // if (encoderButtonState != lastEncoderButtonState) {
  //   if (encoderButtonState == LOW) {
  //     //sys.next();
  //   }
  // }

  // lastEncoderPos = encoderPos;
  // lastEncoderButtonState = encoderButtonState;
}
