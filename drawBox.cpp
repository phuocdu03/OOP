
#include "drawBox.h"

#define KEY_UP    72
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_DOWN  80

using namespace std;
void setColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
int getTerminalWidth(){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwSize.X;
}
int getTerminalHeight() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Bottom+1;
}
void gotoXY(int x, int y)
{
	COORD coordinate;
	coordinate.X = x;
	coordinate.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}
Box::Box(int l, int t, int w, int h)
{
    this->left = l;
    this->top = t;
    this->width = w;
    this->height = h;
    this->count = 0;
    this->index = 1;
}
Box::Box(char l, char t, int w, int h)
{
    this->left = l=='c'?((getTerminalWidth()-w)/2):0;
    this->top = t=='c'?((getTerminalHeight()-h)/2):0;
    this->width = w;
    this->height = h;
    this->count = 0;
    this->index = 1;
}
Box::Box(int l, char t, int w, int h)
{
    this->left = l;
    this->top = t=='c'?((getTerminalHeight()-h)/2):0;
    this->width = w;
    this->height = h;
    this->count = 0;
    this->index = 1;
}
Box::Box(char l, int t, int w, int h)
{
    this->left = l=='c'?((getTerminalWidth()-w)/2):0;
    this->top = t;
    this->width = w;
    this->height = h;
    this->count = 0;
    this->index = 1;
}
int Box::getLeft()
{
    return left;
}
int Box::getTop()
{
    return top;
}
int Box::getWidth()
{
    return width;
}
int Box::getHeight()
{
    return height;
}

void Box::addLine()
{
    gotoXY(getLeft(),getTop()+getHeight()-1);
    cout<<setw(getWidth()-1)<<std::left<<char(186);
    cout<<char(186);
    gotoXY(getLeft(),getTop()+getHeight());
    cout << char(200);
    for (int i = 0; i < width-2; ++i) {
        cout << char(205);
    }
    cout << char(188);
    height++;
}

int Box::getSizeData()
{
    return data.size();
}

saveData Box::getData(int i)
{
    return data[i];
}

void Box::drawRectangle()
{
    gotoXY(left, top);
    cout << char(201);
    for (int i = 0; i < width-2; ++i) {
        cout << char(205);
    }
    cout << char(187);

    for (int i = 0; i < height-2; ++i) {
        gotoXY(left, top + i + 1);
        cout << char(186);
    }
    gotoXY(left, top + height - 1);
    cout << char(200);
    for (int i = 0; i < width-2; ++i) {
        cout << char(205);
    }
    cout << char(188);
    for (int i = 0; i < height-2; ++i) {
        gotoXY(left+width-1, top +i+1);
        cout << char(186);
    }
}
void Box::textLabel(int line, int alignText,string text){
        int X;
        int Y = line + top;
        if (alignText == -1)
            X = left + (width-text.length())/2;
        else
            X = left + 1 + alignText;
        
        gotoXY(X,Y);
        cout<<text;
    }
void Box::textInBox(int line, int alignText,string text){
    count++;
    data.insert(data.end()-countEnd,saveData());
    data[data.size()-countEnd-1].cursorY = line + top;
    data[data.size()-countEnd-1].Text = text;
    if (alignText == -1)
        data[data.size()-countEnd-1].cursorX = left + (width-text.length())/2;
    else
        data[data.size()-countEnd-1].cursorX = left + 1 + alignText;
    
    gotoXY(data[data.size()-countEnd-1].cursorX,data[data.size()-countEnd-1].cursorY);
    cout<<data[data.size()-countEnd-1].Text;
    colorIndex(1,1);
}
void Box::textEndInBox(int line, int alignText, string text)
{
    countEnd++; count++;
    data.push_back(saveData());
    data[count-1].cursorY = line + top;
    data[count-1].Text = text;
    if (alignText == -1)
        data[count-1].cursorX = left + (width-text.length())/2;
    else
        data[count-1].cursorX = left + 1 + alignText;
    
    gotoXY(data[count-1].cursorX,data[count-1].cursorY);
    cout<<data[count-1].Text;
}

void Box::changeTextInBox(int line, string text)
{
    data[line].Text = text;
    setColor(3);
    gotoXY(data[line].cursorX,data[line].cursorY);
    cout<<text;
}

void Box::clearData()
{
    data.clear();
    count = 0;
    countEnd = 0;
    index = 1;
}

int Box::getKey(){

    while(1){
        key = _getch();
        if(key == 'w' && index>1){  
                colorIndex(index,index-1);  
                index--;
        }
        else if(key == 's' && index<count){  
                colorIndex(index,index+1);  
                index++;
        }
        else if(key == 0 || key == 224)
            switch(key = _getch()){
                case KEY_UP:
                    if(index>1){
                        colorIndex(index,index-1);  
                        index--;
                    }
                    break;
                case KEY_DOWN:
                    if(index<count){
                        colorIndex(index,index+1);  
                        index++;
                    }
                    break;
                default: break;
            }
        if(key == '\r')
            return index;
        
    }
    
}


void Box::colorIndex(int cur,int next){
    setColor(7);
    gotoXY(data[cur-1].cursorX,data[cur-1].cursorY);
    cout<<data[cur-1].Text;
    setColor(3);
    gotoXY(data[next-1].cursorX,data[next-1].cursorY);
    cout<<data[next-1].Text;
    setColor(7);
    
}

int countDigits(int number) {
    if(number == 0 ) return 1;
    int count = 0;
    while (number != 0) {
        number /= 10;
        count++;
    }
    return count;
}

void erase(int i){
    while(i--) cout<<" ";
}

string hideInput() {
    string input = "";
    char ch;
    while ((ch = getch()) != '\r') { // 13 là mã ASCII của ký tự Enter
        if (ch == '\b') { // Kiểm tra xem có phải là ký tự backspace không
            if (!input.empty()) { // Kiểm tra xem có ký tự nào để xóa không
                cout << "\b \b"; // Xóa ký tự vừa nhập và dấu *
                input.pop_back(); // Xóa ký tự cuối cùng khỏi chuỗi
            }
        } else {
            std::cout << '*'; // In ra dấu *
            input += ch; // Thêm ký tự vào chuỗi
        }
    }
    cout << std::endl; // In xuống dòng sau khi nhập xong
    return input;
}