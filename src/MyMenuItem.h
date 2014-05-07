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
protected:
  // interface class, constructor forbidden
  MyMenuItemAction() { }

public:
  virtual ~MyMenuItemAction() { }
  virtual void handle() = 0;

private: // forbidden default functions
  MyMenuItemAction& operator = (const MyMenuItemAction& src); // assignment operator
  MyMenuItemAction(const MyMenuItemAction& src);              // copy constructor
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

private: // forbidden default functions
  MyMenuItem& operator = (const MyMenuItem& src); // assignment operator
  MyMenuItem(const MyMenuItem& src);              // copy constructor
};

#endif /* MYMENUITEM_H_ */
