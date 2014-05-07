// 
// 
// 

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Wire.h"
#include "LiquidTWI2.h"
#include "MenuSystem.h"
#include "MyMenuItem.h"
#include "MenuHandler.h"

class Item1MenuAction: public MyMenuItemAction
{
public:
  Item1MenuAction(MenuHandler* mHandler)
  : m_mHandler(mHandler)
  { }

  virtual ~Item1MenuAction() { }

  void handle()
  {
    if (0 != m_mHandler)
    {
      // m_mHandler->do();
    }
  }

private:
  MenuHandler* m_mHandler;

private: // forbidden default functions
  Item1MenuAction& operator = (const Item1MenuAction& src); // assignment operator
  Item1MenuAction(const Item1MenuAction& src);              // copy constructor
};

class Item2MenuAction: public MyMenuItemAction
{
public:
  Item2MenuAction(MenuHandler* mHandler)
  : m_mHandler(mHandler)
  { }

  virtual ~Item2MenuAction() { }

  void handle()
  {
    if (0 != m_mHandler)
    {
      // m_mHandler->do();
    }
  }

private:
  MenuHandler* m_mHandler;

private: // forbidden default functions
  Item2MenuAction& operator = (const Item2MenuAction& src); // assignment operator
  Item2MenuAction(const Item2MenuAction& src);              // copy constructor
};

const unsigned int MenuHandler::LCD_I2C_ADDR = 0xC1;

MenuHandler::MenuHandler()
: m_lcd(new LiquidTWI2(LCD_I2C_ADDR))
, m_menu(new MenuSystem())
, m_mRoot(new Menu("Root Menu"))
, m_mi1(new MyMenuItem("Item 1", m_mRoot, new Item1MenuAction(this)))
, m_mi2(new MyMenuItem("Item 2", m_mRoot, new Item2MenuAction(this)))
{ }

MenuHandler::~MenuHandler()
{
  delete m_mi1->action();
  delete m_mi1; m_mi1 = 0;

  delete m_mi2->action();
  delete m_mi2; m_mi2 = 0;

  delete m_mRoot; m_mRoot = 0;
  delete m_menu;  m_menu  = 0;

  delete m_lcd;   m_lcd   = 0;
}

void MenuHandler::init()
{
  m_lcd->setMCPType(LTI_TYPE_MCP23017);
  // set up the LCD's number of rows and columns:
  m_lcd->begin(16, 2);

  m_menu->set_root_menu(m_mRoot);
  displayMenu();
}

void MenuHandler::handleInput()
{ }

void MenuHandler::displayMenu()
{
  m_lcd->clear();
  m_lcd->setCursor(0, 0);

  // Display the menu
  Menu const* cp_menu = m_menu->get_current_menu();

  //m_lcd.print("Current menu name: ");
  m_lcd->print(cp_menu->get_name());

  m_lcd->setCursor(0, 1);

  m_lcd->print(cp_menu->get_selected()->get_name());
}

