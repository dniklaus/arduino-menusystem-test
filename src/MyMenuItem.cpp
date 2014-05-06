/*
 * MyMenuItem.cpp
 *
 *  Created on: 05.05.2014
 *      Author: niklausd
 */

#include "MenuSystem.h"
#include "MyMenuItem.h"

MyMenuItem::MyMenuItem(const char* name, Menu* parentMenu, MyMenuItemAction* action)
: MenuItem(const_cast<char*>(name))
, m_action(action)
{
  if (0 != parentMenu)
  {
    parentMenu->add_item(this, &(MyMenuItem::on_select));
  }
}

MyMenuItem::~MyMenuItem()
{ }

MyMenuItemAction* MyMenuItem::action()
{
  return m_action;
}

void MyMenuItem::on_select(MenuItem* callingItem)
{
  if (0 != callingItem)
  {
    MyMenuItem* myMenuItem = static_cast<MyMenuItem*>(callingItem);
    if (myMenuItem->action())
    {
      myMenuItem->action()->handle();
    }
  }
}
