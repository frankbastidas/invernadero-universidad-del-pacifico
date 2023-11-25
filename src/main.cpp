#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "SHT2x.h"
#include <Encoder.h>
#include <I2C_RTC.h>
#include <SPI.h>
#include <SD.h>
#include <LiquidMenu.h>

// ------ Configuración del LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ------ Configuración de Menus/submenus
//menuPrincipal
LiquidLine Prin_L1(1, 0, "Monitorizar");
LiquidLine Prin_L2(1, 1, "Control Temp");
LiquidLine Prin_L3(1, 0, "Control Luz");
LiquidLine Prin_L4(1, 1, "Grabar");

LiquidScreen pantallaMenuPrincipal;
LiquidScreen pantallaMenuMonitorizar;
LiquidScreen pantallaMenuControltemp;
LiquidScreen pantallaMenuControlLuz;
LiquidScreen pantallaMenuGrabar;

//menuMonitorizar
LiquidLine Mon_L1(1, 0, "T: 15");
LiquidLine Mon_L2(1, 1, "H: 50");

LiquidMenu menuInvernadero (lcd, pantallaMenuPrincipal);

uint8_t fcline_menuAnterior = 0;

// ------ Configuración sensor temp/humedad
SHT2x sht;

// ------ Configuración Encoder
Encoder myEncoder(2, 3);
#define encoderBotonPin 6
long oldPosition = -999;

// ------ Configuración Reloj
static DS1307 RTC;

// ------ Configuración SD
const int chipSelect = 4;



// the follow variables is a long because the time, measured in miliseconds
// will quickly become a bigger number than can be stored in an int.

long interval = 100;  // interval at which to blink (milliseconds)

void blankFunction()
{
    return;
}

void atras()
{
    menuInvernadero.previous_screen();
    menuInvernadero.set_focusedLine(fcline_menuAnterior);
    delay(100);
}

void fn_monitorizar()
{
  fcline_menuAnterior = menuInvernadero.get_focusedLine();
  menuInvernadero.change_screen(2);
  //menuInvernadero.set_focusedLine(0);
  delay(100);
}

void selectOption(){
  if(digitalRead(encoderBotonPin)==LOW){
    if (menuInvernadero.is_callable(1))
      menuInvernadero.call_function(1);
    else
      atras();
    menuInvernadero.update();
    delay(100);
  }
}

void setup() {

  // ------ Iniciar Entradas/Salidas
  pinMode(encoderBotonPin, INPUT);

  // ------ Iniciar LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.println("Universidad del");
  lcd.setCursor(0, 1);
  lcd.println("    Pacifico");
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.println("  Invernadero");
  lcd.setCursor(0, 1);
  lcd.println("     v0.1");
  delay(500);
  lcd.clear();

  //sht.begin();

  // ------ Iniciar Reloj
  RTC.begin();
  lcd.setCursor(0, 0);
  lcd.println("Reloj: ");
  lcd.setCursor(0, 1);
  if (!RTC.isRunning()) 
    lcd.println("Error. Iniciar Sin");
  lcd.println("Encendido");
  delay(500);
  lcd.clear();

  // ------ Iniciar SD
  lcd.setCursor(0, 0);
  lcd.print("SD: ");
  lcd.setCursor(0, 1);
  if (!SD.begin(chipSelect)) 
    lcd.print("No conectado");
  lcd.println("Conectado");
  delay(500);
  lcd.clear();

  // ------ Iniciar menus/submenus
  //menuPrincipal
  pantallaMenuPrincipal.add_line(Prin_L1);
  pantallaMenuPrincipal.add_line(Prin_L2);
  pantallaMenuPrincipal.add_line(Prin_L3);
  pantallaMenuPrincipal.add_line(Prin_L4);

  Prin_L1.attach_function(1, fn_monitorizar);
  Prin_L2.attach_function(1, blankFunction);
  Prin_L3.attach_function(1, blankFunction);
  Prin_L4.attach_function(1, blankFunction);

  pantallaMenuPrincipal.set_focusPosition(Position::LEFT);
  pantallaMenuPrincipal.set_displayLineCount(2);

  //menuPrincipal
  pantallaMenuMonitorizar.add_line(Mon_L1);
  pantallaMenuMonitorizar.add_line(Mon_L2);

  
  //Mon_L1.attach_function(1, atras);
  //Mon_L2.attach_function(1, atras);

  menuInvernadero.add_screen(pantallaMenuMonitorizar);

  menuInvernadero.init();
  menuInvernadero.set_focusedLine(0);
  menuInvernadero.update();

  /*uint8_t stat = sht.getStatus();
  lcd.setCursor(7, 1);
  lcd.print(stat, HEX);*/
  //Serial.print(stat, HEX);

  /*

  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Hour Mode : ");
  lcd.setCursor(0, 1);
  if (RTC.getHourMode() == CLOCK_H24)
    lcd.println("24 Hours");
  else
    lcd.println("12 Hours");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Is Out Pin Enabled : ");
  lcd.setCursor(0, 1);
  if (RTC.isOutPinEnabled())
    lcd.println("Yes");
  else
    lcd.println("No");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.setCursor(0, 1);
  lcd.print("Is SQWE Enabled : ");
  if (RTC.isSqweEnabled())
    lcd.println("Yes");
  else
    lcd.println("No");

  delay(1000);*/

  oldPosition = myEncoder.read();
}

void loop() {

selectOption();
if (menuInvernadero.is_callable(1)){
  long newPosition = myEncoder.read();
  if (newPosition != oldPosition) {
    if (newPosition > oldPosition) // cambiar deacuerdo al caso
        //uint8_t current_line = menuInvernadero.get_focusedLine();
        menuInvernadero.switch_focus(true);
    else
        menuInvernadero.switch_focus(false);
    
    menuInvernadero.update();
    oldPosition = newPosition;
    delay(200);
  }
}
  //lcd.setCursor(1, 1);
  //lcd.print(SHT2x_LIB_VERSION);
  //lcd.clear();
  /* sht.read();

  lcd.setCursor(9, 1);
  lcd.print("T: ");
  lcd.print(sht.getTemperature(), 2);

  lcd.setCursor(9, 0);
  lcd.print("H: ");
  lcd.print(sht.getHumidity(), 2);

  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    //Serial.println(newPosition);
    lcd.setCursor(0, 0);
    lcd.print(newPosition);
  }
*/

  /*lcd.setCursor(0, 0);
  lcd.print(RTC.getDay());
  lcd.print("-");
  lcd.print(RTC.getMonth());
  lcd.print("-");
  lcd.print(RTC.getYear());

  lcd.setCursor(0, 1);
  lcd.print(RTC.getHours());
  lcd.print(":");
  lcd.print(RTC.getMinutes());
  lcd.print(":");
  lcd.print(RTC.getSeconds());
  delay(1000);*/

  /*
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  // if the file is available, write to it:
  // make a string for assembling the data to log:
  String dataString = "";
  lcd.setCursor(0, 1);
  if (dataFile) {
    dataString = String(RTC.getHours()) + ":" + String(RTC.getMinutes()) + ":" + String(RTC.getSeconds());
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    lcd.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    lcd.println("error opening datalog.txt");
  }*/

}
