// Do not remove the include below
#include "arduino_menusystem_test.h"

#include "MenuHandler.h"
#include "LcdKeypad.h"
#include "Timer.h"

MenuHandler* menuHandler = 0;

//The setup function is called once at startup of the sketch
void setup()
{
  //---------------------------------------------------------------------------
  // Debugging
  //---------------------------------------------------------------------------
  Serial.begin(115200);
  Serial.println("-----------------------------------------------------------------");
  Serial.println("Hello from Arduino MenuSystem Test!");
  Serial.println("-----------------------------------------------------------------");
  Serial.println("Press 'l' or 'a' for left, 'r' or 'd' for right, 's' for select");
  Serial.println("Press 'o' for LCD Backlight On, 'k' for LCD Backlight Off");
  Serial.println("-----------------------------------------------------------------\n");

  //---------------------------------------------------------------------------
  // MenuHandler
  //---------------------------------------------------------------------------
  menuHandler = new MenuHandler();
  menuHandler->init();
}

/*
 SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent()
{
  while (Serial.available())
  {
    // get the new byte:
    char inChar = (char)Serial.read();
    if ('s' == inChar)
    {
      menuHandler->selectKeyEvent();
    }
    else if (('l' == inChar) || ('a' == inChar))
    {
      menuHandler->leftKeyEvent();
    }
    else if (('r' == inChar) || ('d' == inChar))
    {
      menuHandler->rightKeyEvent();
    }
    else if ('o' == inChar)
    {
      menuHandler->lcd()->setBackLightOn(true);
    }
    else if ('k' == inChar)
    {
      menuHandler->lcd()->setBackLightOn(false);
    }
  }
}

// The loop function is called in an endless loop
void loop()
{
  scheduleTimers();
}
