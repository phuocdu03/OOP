#ifndef DATAPRODUCT_H
#define DATAPRODUCT_H
#include "dataProduct.h"
#endif // DATAPRODUCT_H

#ifndef DRAWBOX_PRODUCT_H
#define DRAWBOX_PRODUCT_H
#include "drawBox_Product.h"
#endif // DRAWBOX_PRODUCT_H

extern product productExport;
Box_Product boxShopping = {'c','c',84,20};
bool exists(int i);
void addOrRemove(int i);
void markCheck(Box_Product box,int key,int page);
void displayBoxShopping();