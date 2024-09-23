#include "ImportOption.h"

void ImportOption()
{
    Box importOption_Box;
    const int left = 10;
    system("cls");
    importOption_Box = {'c','c',48,10};
    importOption_Box.drawRectangle();
    importOption_Box.textLabel(-3,-1,"IMPORT OPTION");
    importOption_Box.textInBox(3,left,"1. Import existing product");
    importOption_Box.textInBox(4,left,"2. Import new product");
    importOption_Box.textInBox(5,left,"3. Import from file");
    importOption_Box.textInBox(7,left,"Exit");
        switch(importOption_Box.getKey())
    {
        case 1: ImportProduct();break;
        case 2: ImportNewProduct(); break;
        case 3: ImportFromFile(); break;
        case 4: MainMenu();           break;
        case 5: exit(0);    break;
    }
    system("pause");
}