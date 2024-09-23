// #include "CheckInventory.h"
#ifndef DATAPRODUCT_H
#define DATAPRODUCT_H
#include "dataProduct.h"
#endif // DATAPRODUCT_H

#ifndef DRAWBOX_PRODUCT_H
#define DRAWBOX_PRODUCT_H
#include "drawBox_Product.h"
#endif // DRAWBOX_PRODUCT_H

#ifndef MAINMENU_H
#define MAINMENU_H
#include "MainMenu.h"
#endif // MAINMENU_H

#ifndef DRAWBOX_H
#define DRAWBOX_H
#include "drawBox.h"
#endif

#include <fstream>
#include <sstream>

void displayBoxImport(Box_Product boxImport,int page);
void importToWarehouse();
void createQuantityInsertVitual();
bool loadCSVFile(string filename);
void ImportProduct();
// ----------------------------------------------------
void ImportFromFile();

// -----------------------------------------------------
void ImportNewProduct();
// -------------------------------------------------------
