// MenuHandler.h

#ifndef _MENUHANDLER_h
#define _MENUHANDLER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "MenuSystem.h"
#include "Wire.h"
#include "LiquidTWI2.h"

class MenuHandler
{

private:
	// Menu variables
	MenuSystem m_menu;
	Menu m_mRoot;
	MenuItem m_mi1;
	MenuItem m_mi2;
	LiquidTWI2 m_lcd;

	void handleInput();
	void displayMenu();

protected:


public:
	MenuHandler();
	virtual ~MenuHandler();
	void init();

	static void on_item1_selected(MenuItem* p_menu_item);
	static void on_item2_selected(MenuItem* p_menu_item);

};


#endif

