#include "dataUser.h"

// Constructor
UserManager::UserManager(const string& filename) : filename(filename) {
    loadUsersFromCSV();
}

// Phương thức đăng nhập
bool UserManager::login(const string& username, const string& password) {
    for (const auto& user : users) {
        if (user.username == username && user.password == password) {
            loggedInUser = username; // Lưu username của người dùng đã đăng nhập
            return true;
        }
    }
    return false;
}

// Phương thức đổi mật khẩu
bool UserManager::changePassword(const string& newPassword) {
    for (auto& user : users) {
        if (user.username == loggedInUser) {
            user.password = newPassword;
            updateUsersToFile();
            return true;
        }
    }
    return false;
}

// Phương thức lấy mật khẩu của người dùng đăng nhập
string UserManager::getPassword() const {
    for (const auto& user : users) {
        if (user.username == loggedInUser) {
            return user.password;
        }
    }
    return "";
}

// Phương thức lấy thông tin của người dùng đăng nhập
User UserManager::getCurrentUserInfo() const {
    for (const auto& user : users) {
        if (user.username == loggedInUser) {
            return user;
        }
    }
    // Trả về user rỗng nếu không tìm thấy
    return User();
}

// Phương thức đổi thông tin từng phần
bool UserManager::changeUserInfo(const string& field, const string& newValue) {
    for (auto& user : users) {
        if (user.username == loggedInUser) {
            if (field == "fullName") user.fullName = newValue;
            else if (field == "gender") user.gender = newValue;
            else if (field == "ID") user.ID = newValue;
            else if (field == "dateOfBirth") user.dateOfBirth = newValue;
            updateUsersToFile();
            return true;
        }
    }
    return false;
}

// Phương thức cập nhật lại thông tin từ file
void UserManager::reloadUsersFromFile() {
    loadUsersFromCSV();
}

// Phương thức load thông tin người dùng từ file CSV
void UserManager::loadUsersFromCSV() {
    users.clear();
    ifstream file(filename);
    string line;
    User user;
    int count = 0;
    while (getline(file, line)) {
        if (!line.empty()) { // Bỏ qua dòng trống
            switch (count % 6) {
                case 0:
                    user.username = line;
                    break;
                case 1:
                    user.password = line;
                    break;
                case 2:
                    user.fullName = line;
                    break;
                case 3:
                    user.gender = line;
                    break;
                case 4:
                    user.ID = line;
                    break;
                case 5:
                    user.dateOfBirth = line;
                    users.push_back(user);
                    break;
            }
            count++;
        }
    }
    file.close();
}

// Phương thức cập nhật thông tin người dùng vào file CSV
void UserManager::updateUsersToFile() {
    ofstream fileOut(filename);
    if (!fileOut.is_open()) {
        cout << "Không thể mở file" << endl;
        return;
    }

    for (const auto& user : users) {
        fileOut << user.username << endl;
        fileOut << user.password << endl;
        fileOut << user.fullName << endl;
        fileOut << user.gender << endl;
        fileOut << user.ID << endl;
        fileOut << user.dateOfBirth << endl << endl; // Thêm dòng trống
    }
    fileOut.close();
}
#define userFilename "User.csv"
UserManager user(userFilename);