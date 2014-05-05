// 
// 
// 

#include "MenuHandler.h"

MenuHandler::MenuHandler()
	: m_lcd(0), 
	m_menu(),
	m_mRoot("Root Menu"),
	m_mi1("Item 1"),
	m_mi2("Item 2")
{ }

MenuHandler::~MenuHandler()
{ }

void MenuHandler::init()
{
	m_lcd.setMCPType(LTI_TYPE_MCP23017); 
	// set up the LCD's number of rows and columns:
	m_lcd.begin(16, 2);

	m_mRoot.add_item(&m_mi1, &MenuHandler::on_item1_selected);
	m_mRoot.add_item(&m_mi2, &MenuHandler::on_item2_selected);
	m_menu.set_root_menu(&m_mRoot);
	displayMenu();

}

void MenuHandler::handleInput()
{
}

void MenuHandler::displayMenu()
{
	m_lcd.clear();
	m_lcd.setCursor(0,0);
	// Display the menu
	Menu const* cp_menu = m_menu.get_current_menu();

	//m_lcd.print("Current menu name: ");
	m_lcd.print(cp_menu->get_name());

	m_lcd.setCursor(0,1);

	m_lcd.print(cp_menu->get_selected()->get_name());
}


void MenuHandler::on_item1_selected(MenuItem* p_menu_item)
{
	//TODO
}

void MenuHandler::on_item2_selected(MenuItem* p_menu_item)
{
	//TODO
}


