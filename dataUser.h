#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm> // for std::find

using namespace std;

// Struct to store user information
struct User {
    string username;
    string password;
    string fullName;
    string gender;
    string ID;
    string dateOfBirth;
};

class UserManager {
private:
    vector<User> users;
    string filename;
    string loggedInUser; // Username của người dùng đã đăng nhập

public:
    // Constructor
    UserManager(const string& filename);

    // Phương thức đăng nhập
    bool login(const string& username, const string& password);

    // Phương thức đổi mật khẩu
    bool changePassword(const string& newPassword);

    // Phương thức lấy mật khẩu của người dùng đăng nhập
    string getPassword() const;

    // Phương thức lấy thông tin của người dùng đăng nhập
    User getCurrentUserInfo() const;

    // Phương thức đổi thông tin từng phần
    bool changeUserInfo(const string& field, const string& newValue);

    // Phương thức cập nhật lại thông tin từ file
    void reloadUsersFromFile();

private:
    // Phương thức load thông tin người dùng từ file CSV
    void loadUsersFromCSV();

    // Phương thức cập nhật thông tin người dùng vào file CSV
    void updateUsersToFile();
};


