#ifndef DATAPRODUCT_H
#define DATAPRODUCT_H
#include "dataProduct.h"
#endif // DATAPRODUCT_H

#ifndef MAINMENU_H
#define MAINMENU_H
#include "MainMenu.h"
#endif // MAINMENU_H

#ifndef DRAWBOX_PRODUCT_H
#define DRAWBOX_PRODUCT_H
#include "drawBox_Product.h"
#endif // DRAWBOX_PRODUCT_H

#ifndef DRAWBOX_H
#define DRAWBOX_H
#include "drawBox.h"
#endif



bool exists(int i);
void addOrRemove(int i);
void markCheck(Box_Product box,int key,int page);
void setDataChecked(product& productChecked);
void updateStore(product& productChecked);
// void loading(product& productChecked);
void displayBoxPushToStore(Box_Product box,int page);
void displayBoxAndProduct(Box_Product box, int page);
void CheckInventory();
