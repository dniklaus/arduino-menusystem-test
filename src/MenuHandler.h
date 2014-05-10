// MenuHandler.h

#ifndef _MENUHANDLER_h
#define _MENUHANDLER_h

//class LiquidTWI2;
class LcdKeypad;
class MenuSystem;
class Menu;
class MyMenuItem;
class MyMenuItemAction;

class MenuHandler
{

private:
//  static const unsigned int LCD_I2C_ADDR;
  // Menu variables
//  LiquidTWI2* m_lcd;
  LcdKeypad* m_lcd;
  MenuSystem* m_menu;
  Menu* m_mRoot;
  MyMenuItem* m_mi1;
  MyMenuItem* m_mi2;

  bool m_isItem1Active;
  bool m_isItem2Active;

  void handleInput();
  void displayMenu();

public:
  MenuHandler();
  virtual ~MenuHandler();
  void init();

  void selectKeyEvent();
  void leftKeyEvent();
  void rightKeyEvent();

  void setItem1Active(bool isActive);
  void setItem2Active(bool isActive);

  bool isItem1Active();
  bool isItem2Active();

//  LiquidTWI2* lcd();
  LcdKeypad* lcd();

private: // forbidden default functions
	MenuHandler& operator = (const MenuHandler& src); // assignment operator
	MenuHandler(const MenuHandler& src);              // copy constructor
};

#endif
