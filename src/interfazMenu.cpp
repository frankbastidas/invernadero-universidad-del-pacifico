#include "InterfazMenu.h"

InterfazMenu::InterfazMenu(int encoderPinA, int encoderPinB, int encoderButtonPin, LiquidSystem &sys, LiquidCrystal_I2C &lcd)
    : _encoderPinA(encoderPinA), _encoderPinB(encoderPinB), _encoderButtonPin(encoderButtonPin), _sys(sys), _lcd(lcd)
{
    _menuPrincipal = LiquidMenu(_lcd);
    _menuMonitorizar = LiquidMenu(_lcd);
    _menuControlTemp = LiquidMenu(_lcd);
    _menuControlLuz = LiquidMenu(_lcd);
    _menuGrabar = LiquidMenu(_lcd);
}

void InterfazMenu::mensajeInicial()
{

    _lcd.setCursor(0, 0);
    _lcd.print("Universidad del");
    _lcd.setCursor(0, 1);
    _lcd.print("pacifico");
}

void InterfazMenu::configurarMenuPrincipal()
{

    LiquidLine line1(1, 0, "Monitorizar");
    LiquidLine line2(1, 1, "Control Temp");
    LiquidLine line3(1, 1, "Control Luz");
    LiquidLine line4(1, 1, "Grabar");
    // Add more "lines" than the display has. The extra will be scrolled.
    LiquidScreen screenMenuPrincipal(line1, line2, line3, line4);
    // Attaching a function to the lines is required for scrolling to work.
    line1.attach_function(1, &InterfazMenu::blankFunction);
    line2.attach_function(1, &InterfazMenu::blankFunction);
    line3.attach_function(1, &InterfazMenu::blankFunction);
    line4.attach_function(1, &InterfazMenu::blankFunction);
    
    screenMenuPrincipal.set_displayLineCount(2);

    // _menuPrincipal.init();
    _menuPrincipal.add_screen(screenMenuPrincipal);
    _menuPrincipal.set_focusedLine(0);
    _menuPrincipal.set_focusPosition(Position::LEFT);
    // Set the number of decimal places for a "line".
    //line1.set_decimalPlaces(5);

    //_menuPrincipal.update();
    _sys.add_menu(_menuPrincipal);
    //_menuPrincipal.update();

}

void InterfazMenu::configurarMenuMonitorizar(){

    LiquidLine line1(1, 0, "T: ", "24");
    LiquidLine line2(8, 1, "H: ","10");
    
    // Add more "lines" than the display has. The extra will be scrolled.
    LiquidScreen screenMenuMonitorizar(line1, line2);

    _menuMonitorizar.add_screen(screenMenuMonitorizar);

    _menuMonitorizar.update();
}

void InterfazMenu::configurarMenuControlTemperatura(){

    LiquidLine line1(1, 0, "T: ", "24");
    LiquidLine line2(8, 1, "H: ","10");
    
    // Add more "lines" than the display has. The extra will be scrolled.
    LiquidScreen screenMenuMonitorizar(line1, line2);

    _menuMonitorizar.add_screen(screenMenuMonitorizar);

    _menuMonitorizar.update();
}

void InterfazMenu::blankFunction() {
      return;
  }

// void InterfazMenu::fn_monitorizar() {
//       return;
//   }

// void InterfazMenu::fn_controlTemp() {
//       return;
//   }

// void InterfazMenu::fn_controlLuz() {
//       return;
//   }

// void InterfazMenu::fn_grabar() {
//       return;
//}

