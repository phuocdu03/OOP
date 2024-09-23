#include "MainMenu.h"


using namespace std;
void MainMenu(){
    Box menu;
    const int left = 10;
    system("cls");
    menu = {'c','c',48,10};
    menu.drawRectangle();
    menu.textLabel(-5,-1,"GROCERY STORE MANAGMENT");
    menu.textLabel(-3,-1,"MAIN MENU");
    menu.textInBox(3,left,"1. User Account");
    menu.textInBox(4,left,"2. Import Products");
    menu.textInBox(5,left,"3. Export Products");
    menu.textInBox(6,left,"4. Report Export");
    // menu.textInBox(8,left,"Exit");
    switch(menu.getKey())
    {
        case 1: return UserAccount();
        case 2: return ImportOption();
        case 3: return CheckInventory();
        case 4: return Export();
        // case 5: return Login();

    }
    system("pause");
}