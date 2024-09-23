#ifndef DATAPRODUCT_H
#define DATAPRODUCT_H
#include "dataProduct.h"
#endif // DATAPRODUCT_H

#ifndef MAINMENU_H
#define MAINMENU_H
#include "MainMenu.h"
#endif

#ifndef DRAWBOX_PRODUCT_H
#define DRAWBOX_PRODUCT_H
#include "drawBox_Product.h"
#endif // DRAWBOX_PRODUCT_H

#ifndef DATAUSER_H
#define DATAUSER_H
#include "dataUser.h"
#endif
#include <ctime>

extern product productExport;
extern UserManager user;

string getDate();
void displayInfomationExport(int page);
void Export();
void Export_CSV();