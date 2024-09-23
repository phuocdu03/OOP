#ifndef MAINMENU_H
#define MAINMENU_H
#include "MainMenu.h"
#endif

#ifndef IMPORTPRODUCT_H
#define IMPORTPRODUCT_H
#include "ImportProduct.h"
#endif

#ifndef DRAWBOX_H
#define DRAWBOX_H
#include "drawBox.h"

#endif
#ifndef DATAUSER_H
#define DATAUSER_H
#include "dataUser.h"
#endif

// #define userFilename "User.csv"
extern UserManager user;
extern product inventory;
extern product productExport;
void checkLogin(Box login);
void Login();