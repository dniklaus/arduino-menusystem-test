// MenuHandler.h

#ifndef _MENUHANDLER_h
#define _MENUHANDLER_h

class LiquidTWI2;
class MenuSystem;
class Menu;
class MyMenuItem;
class MyMenuItemAction;

class MenuHandler
{

private:
  static const unsigned int LCD_I2C_ADDR;
  // Menu variables
  LiquidTWI2* m_lcd;
  MenuSystem* m_menu;
	Menu* m_mRoot;
	MyMenuItem* m_mi1;
	MyMenuItem* m_mi2;

	void handleInput();
	void displayMenu();

public:
	MenuHandler();
	virtual ~MenuHandler();
	void init();

private: // forbidden default functions
	MenuHandler& operator = (const MenuHandler& src); // assignment operator
	MenuHandler(const MenuHandler& src);              // copy constructor
};

#endif
