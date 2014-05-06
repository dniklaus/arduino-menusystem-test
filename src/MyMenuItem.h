/*
 * MyMenuItem.h
 *
 *  Created on: 05.05.2014
 *      Author: niklausd
 */

#ifndef MYMENUITEM_H_
#define MYMENUITEM_H_

#include <MenuSystem.h>

class MyMenuItemAction
{
public:
  virtual void handle() = 0;
};

class Menu;

class MyMenuItem: public MenuItem
{
public:
  MyMenuItem(const char* name, Menu* parentMenu, MyMenuItemAction* action);
  virtual ~MyMenuItem();

  MyMenuItemAction* action();

public:
  static void on_select(MenuItem* callingItem);

private:
  MyMenuItemAction* m_action;
};

#endif /* MYMENUITEM_H_ */
