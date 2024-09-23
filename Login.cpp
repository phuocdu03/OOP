#include "Login.h"
// #define User "user1"
// #define Pass "123"
#define left 10

void checkLogin(Box login){
    string username,password;
    int key;
    while(1){
        gotoXY(login.getLeft()+left+10+2,login.getTop()+3);
        getline(cin>>ws,username);
        gotoXY(login.getLeft()+left+10+2,login.getTop()+5);
        getline(cin>>ws,password);
        if(user.login(username,password)){
            system("cls");
            inventory.clearDataProduct();
            productExport.clearDataProduct();
            LoadInitalProduct();
            login.drawRectangle();
            login.textLabel(3,10,"Login successful !:");
            login.textLabel(5,10,"Press 'r' to continue...:");
            while((key = _getch()) !=  'r');
            return MainMenu();
        }
        else{
            gotoXY(login.getLeft()+left+10+2,login.getTop()+3);
            erase(username.length());
            gotoXY(login.getLeft()+left+10+2,login.getTop()+5);
            erase(password.length());
            login.textLabel(8,-1,"Wrong username or password");
        }
    }
}
void Login()
{
    Box login;
    system("cls");
    login = {'c',8,48,10};
    login.drawRectangle();
    login.textLabel(-5,-1,"GROCERY STORE MANAGMENT");
    login.textLabel(-3,-1,"Login");
    login.textLabel(3,left,"Username:");
    login.textLabel(5,left,"Password:");
    login.textLabel(8,-1,"Welcome user");
    checkLogin(login);
}