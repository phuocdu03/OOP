#ifndef LOGIN_H
#define LOGIN_H
#include "Login.h"
#endif // LOGIN_H

#ifndef MAINMENU_H
#define MAINMENU_H

#include "MainMenu.h"

#endif // MAINMENU_H

#ifndef USERINFORMATION
#define USERINFORMATION
#include "UserInformation.h"
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

void UserAccount();
void ChangePassword();
void LogoutProduct();
void LoadInitalProduct();