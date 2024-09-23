#include "UserAccount.h"

void UserAccount()
{
    Box UserAccount_Box;
    const int left = 10;
    system("cls");
    UserAccount_Box = {'c','c',48,9};
    UserAccount_Box.drawRectangle();
    UserAccount_Box.textLabel(-2,-1,"USER ACCOUNT");
    // UserAccount_Box.textLabel(-3,-1,"MAIN UserAccount_Box");
    UserAccount_Box.textInBox(2,left,"1. Change Password");
    UserAccount_Box.textInBox(3,left,"2. Information");
    UserAccount_Box.textInBox(4,left,"3. Logout");    
    UserAccount_Box.textInBox(6,left,"Exit");
    switch(UserAccount_Box.getKey())
    {
        case 1: return ChangePassword(); break;
        case 2: return UserInformation();
        case 3: {
            LogoutProduct();
            return Login();
        }
        case 4: return MainMenu();

    }
    system("pause");
}

void ChangePassword()
{
    system("cls");
    Box password_Box = {'c','c',48,11};
    int left = 3;
    string oldPassword,password,passwordAgain;
    int key;
    password_Box.drawRectangle();
    password_Box.textLabel(-2,-1,"Change Password");
    password_Box.textLabel(3,left,"Current Password:");
    password_Box.textLabel(5,left,"New Password:");
    password_Box.textLabel(7,left,"New Password (again):");

    gotoXY(password_Box.getLeft()+left+20+3,password_Box.getTop()+3);
    getline(cin>>ws,oldPassword);
    gotoXY(password_Box.getLeft()+left+20+3,password_Box.getTop()+5);
    getline(cin>>ws,password);
    gotoXY(password_Box.getLeft()+left+20+3,password_Box.getTop()+7);
    getline(cin>>ws,passwordAgain);
    if(passwordAgain != password){
        password_Box.textLabel(password_Box.getHeight(),-1,
                                "New password and confirmation do not match");
        password_Box.textLabel(password_Box.getHeight()+1,-1,
                                "Press 'Enter' to retry or 'e' to exit");
        while(1){
            key = _getch();
            if(key == 'e' || key == 'E')
                return MainMenu();
            if(key == '\r')
                return ChangePassword();
            }
    }
    if(oldPassword == user.getPassword()){
        user.changePassword(password);
        password_Box.textLabel(password_Box.getHeight(),-1,
                            "password has been changed successfully");
        password_Box.textLabel(password_Box.getHeight()+1,-1,
                            "Press 'Enter' to exit");
        while(1){ 
            key = _getch();
            if(key == '\r')
                return MainMenu();
            }
    }
    else{
        password_Box.textLabel(password_Box.getHeight(),-1, 

                            "Can't change the password, incorrect current password");
        password_Box.textLabel(password_Box.getHeight()+1,-1,
                                "Press 'Enter' to retry or 'e' to exit");
        while(1){
            key = _getch();
            if(key == 'e' || key == 'E')
                return MainMenu();
            if(key == '\r')
                return ChangePassword();
            }
    }
    system("pause");
}

void LogoutProduct()
{
    ofstream fileOut("data_Load.csv");
    if (!fileOut.is_open()) {
        cout << "Không thể mở file" << endl;
        return;
    }
    for (int i = 0;i < inventory.getCountProduct();i++) {
        if(inventory.getDataProduct(i).Quantity > 0){
            fileOut << inventory.getDataProduct(i).ID <<',' ;
            fileOut << inventory.getDataProduct(i).Categorize << ',';
            fileOut << inventory.getDataProduct(i).Name << ',';
            fileOut << inventory.getDataProduct(i).Price << ',';
            fileOut << inventory.getDataProduct(i).Quantity << endl;
        }
    }
    fileOut.close();
}

void LoadInitalProduct()
{
        ifstream file("data_Load.csv");

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string ID, categorize, name, quantity_str, price_str;
        int quantity, price;
        dataProduct data;
        // Tách dữ liệu từng ô trong dòng bằng dấu phẩy (CSV)
        if (getline(iss, ID, ',') && 
            getline(iss, categorize, ',') &&
            getline(iss, name, ',') && 
            getline(iss, price_str, ',') && 
            getline(iss, quantity_str, ',')) {
            // Chuyển đổi quantity từ string sang int
            istringstream(price_str) >> price;
            istringstream(quantity_str) >> quantity;
            // Kiểm tra xem ID đã tồn tại trong vector hay chưa
            data = {ID,categorize,name,price,quantity};
            inventory.setDataProduct(data);
        }
    }
    // Đóng file sau khi đọc xong
    file.close();
}