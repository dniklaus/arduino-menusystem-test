// 
// 
// 

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Wire.h"
//#include "LiquidTWI2.h"
#include "LcdKeypad.h"
#include "MenuSystem.h"
#include "MyMenuItem.h"
#include "MenuHandler.h"

class Item1MenuAction: public MyMenuItemAction
{
private:
  MenuHandler* m_mHandler;

public:
  Item1MenuAction(MenuHandler* mHandler)
  : m_mHandler(mHandler)
  { }

  void handle()
  {
    if (0 != m_mHandler)
    {
      Serial.println("Item1MenuAction performed.");
      m_mHandler->setItem1Active(!m_mHandler->isItem1Active());
    }
  }

private: // forbidden default functions
  Item1MenuAction& operator = (const Item1MenuAction& src); // assignment operator
  Item1MenuAction(const Item1MenuAction& src);              // copy constructor
};

class Item2MenuAction: public MyMenuItemAction
{
private:
  MenuHandler* m_mHandler;

public:
  Item2MenuAction(MenuHandler* mHandler)
  : m_mHandler(mHandler)
  { }

  void handle()
  {
    if (0 != m_mHandler)
    {
      Serial.println("Item2MenuAction performed.");
      m_mHandler->setItem2Active(!m_mHandler->isItem2Active());
    }
  }

private: // forbidden default functions
  Item2MenuAction& operator = (const Item2MenuAction& src); // assignment operator
  Item2MenuAction(const Item2MenuAction& src);              // copy constructor
};

class MyLcdKeypadAdapter : public LcdKeypadAdapter
{
public:
  MyLcdKeypadAdapter(/*LcdKeypad* lcdKeypad*/ MenuHandler* menuHandler = 0)
  : m_menuHandler(menuHandler)
  { }

private:
  MenuHandler* m_menuHandler;

  void handleKeyChanged(LcdKeypad::Key newKey)
  {
    Serial.print("MyLcdKeypadAdapter::handleKeyChanged(), newKey: ");
    Serial.println((LcdKeypad::NO_KEY == newKey)     ? "NO_KEY"     :
                   (LcdKeypad::SELECT_KEY == newKey) ? "SELECT_KEY" :
                   (LcdKeypad::LEFT_KEY == newKey)   ? "LEFT_KEY"   :
                   (LcdKeypad::UP_KEY == newKey)     ? "UP_KEY"     :
                   (LcdKeypad::DOWN_KEY == newKey)   ? "DOWN_KEY"   :
                   (LcdKeypad::RIGHT_KEY == newKey)  ? "RIGHT_KEY"  : "OOPS!! Invalid value!!");

    if (0 != m_menuHandler)
    {
      LcdKeypad* lcdKeypad = m_menuHandler->lcd();
      if (0 != lcdKeypad)
      {
        if (LcdKeypad::UP_KEY == newKey)
        {
          lcdKeypad->setBackLightOn(true);
        }
        if (LcdKeypad::DOWN_KEY == newKey)
        {
          lcdKeypad->setBackLightOn(false);
        }
      }
      if (LcdKeypad::SELECT_KEY == newKey)
      {
        m_menuHandler->selectKeyEvent();
      }
      if (LcdKeypad::LEFT_KEY == newKey)
      {
        m_menuHandler->leftKeyEvent();
      }
      if (LcdKeypad::RIGHT_KEY == newKey)
      {
        m_menuHandler->rightKeyEvent();
      }
    }
  }
};


//const unsigned int MenuHandler::LCD_I2C_ADDR = 0xC1;

MenuHandler::MenuHandler()
: m_lcd(new LcdKeypad() /*new LiquidTWI2(LCD_I2C_ADDR)*/)
, m_menu(new MenuSystem())
, m_mRoot(new Menu("Root Menu"))
, m_mi1(new MyMenuItem("Item 1", m_mRoot, new Item1MenuAction(this)))
, m_mi2(new MyMenuItem("Item 2", m_mRoot, new Item2MenuAction(this)))
, m_isItem1Active(false)
, m_isItem2Active(false)
{
  m_lcd->attachAdapter(new MyLcdKeypadAdapter(this));
}

MenuHandler::~MenuHandler()
{
  delete m_mi1->action();
  delete m_mi1; m_mi1 = 0;

  delete m_mi2->action();
  delete m_mi2; m_mi2 = 0;

  delete m_mRoot; m_mRoot = 0;
  delete m_menu;  m_menu  = 0;

  delete m_lcd; m_lcd   = 0;
}

void MenuHandler::init()
{
//  m_lcd->setMCPType(LTI_TYPE_MCP23017);
  // set up the LCD's number of rows and columns:
  m_lcd->begin(16, 2);
  m_lcd->setBackLightOn(true);

  m_menu->set_root_menu(m_mRoot);
  displayMenu();
}

void MenuHandler::selectKeyEvent()
{
   m_menu->select();
}

void MenuHandler::leftKeyEvent()
{
  m_menu->prev(false);
  displayMenu();
}

void MenuHandler::rightKeyEvent()
{
  m_menu->next(false);
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
  m_lcd->print("    ");

  bool isMenuItemActive = false;
  const char* selectedName = const_cast<char*>(cp_menu->get_selected()->get_name());
  if (0 == strcmp(selectedName, m_mi1->get_name()))
  {
    isMenuItemActive = isItem1Active();
    Serial.print("MenuHandler::displayMenu(), m_mi1->get_name() matches selectedName: ");
    Serial.println(selectedName);
  }
  if (0 == strcmp(selectedName, m_mi2->get_name()))
  {
    isMenuItemActive = isItem2Active();
    Serial.print("MenuHandler::displayMenu(), m_mi2->get_name() matches selectedName: ");
    Serial.println(selectedName);
  }

  m_lcd->print(isMenuItemActive ? "active" : "      ");
}

LcdKeypad* MenuHandler::lcd()
{
  return m_lcd;
}

void MenuHandler::setItem1Active(bool isActive)
{
  m_isItem1Active = isActive;
  Serial.print("MenuHandler::m_isItem1Active: ");
  Serial.println(m_isItem1Active ? "1" : "0");
  displayMenu();
}

void MenuHandler::setItem2Active(bool isActive)
{
  m_isItem2Active = isActive;
  Serial.print("MenuHandler::m_isItem2Active: ");
  Serial.println(m_isItem2Active ? "1" : "0");
  displayMenu();
}

bool MenuHandler::isItem1Active()
{
  return m_isItem1Active;
}

bool MenuHandler::isItem2Active()
{
  return m_isItem2Active;
}
