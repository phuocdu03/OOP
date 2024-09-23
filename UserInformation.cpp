#include "UserInformation.h"

#define left 4
void UserInformation()
{
    system("cls");
    Box UserInformation_Box = {'c','c',48,11};
    UserInformation_Box.drawRectangle();
    UserInformation_Box.textLabel(-2,-1,"User Information");
    UserInformation_Box.textLabel(2,left,"Name:          "+ user.getCurrentUserInfo().fullName);
    UserInformation_Box.textLabel(4,left,"Gender:        "+ user.getCurrentUserInfo().gender);
    UserInformation_Box.textLabel(6,left,"ID:            "+ user.getCurrentUserInfo().ID);
    UserInformation_Box.textLabel(8,left,"Date of Birth: "+ user.getCurrentUserInfo().dateOfBirth);
    UserInformation_Box.textLabel(UserInformation_Box.getHeight(),-1,
                                "Press 'Enter' or 'e' to exit");
    while(1){
        char key = _getch();
    if(key == 'e' || key == 'E' || key == '\r')
        // return ;
        return MainMenu();
    }
}