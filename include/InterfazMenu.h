#ifndef InterfazMenu_h
#define InterfazMenu_h

#include "Arduino.h"
#include <LiquidMenu.h>
#include <LiquidCrystal_I2C.h>
#include <Encoder.h>

// Used for attaching something to the lines, to make them focusable.


class InterfazMenu {
public:
  InterfazMenu(int encoderPinA, int encoderPinB, 
  int encoderButtonPin, LiquidSystem &sys, LiquidCrystal_I2C &lcd);
  
  void configurarMenuPrincipal();
  void configurarMenuMonitorizar();
  void configurarMenuControlTemperatura();
  void configurarMenuControlLuz();
  void configurarMenuGrabar();
  void mensajeInicial();
  // Used for attaching something to the lines, to make them focusable.
  static void blankFunction();
  

  LiquidMenu _menuPrincipal;
  LiquidMenu _menuMonitorizar;
  LiquidMenu _menuControlTemp;
  LiquidMenu _menuControlLuz;
  LiquidMenu _menuGrabar;
  

private:
  int _encoderPinA;
  int _encoderPinB;
  int _encoderButtonPin;
  LiquidCrystal_I2C &_lcd;
  LiquidSystem &_sys;

};

#endif