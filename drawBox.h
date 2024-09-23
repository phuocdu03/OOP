#include <iostream>
#include <windows.h>
#include <vector>
#include <conio.h>
#include <iomanip>
using namespace std;
struct saveData{
    int cursorX;
    int cursorY;
    string Text;
    bool check = 0;
};

class Box{
    public:
    Box(){
        this->left = 0;
        this->top = 0;
        this->width = 0;
        this->height = 0;
        this->count = 0;
        this->index = 1;
    }
    Box(int l,int t,int w,int h);
    Box(char l, char t,int w,int h);
    Box(int l, char t,int w,int h);
    Box(char l, int t,int w,int h);
    int getLeft();
    int getTop();
    int getWidth();
    int getHeight();
    void drawRectangle();
    void addLine();
    void textLabel(int line, int alignText,string text);
    void textInBox(int line, int alignText,string text);
    void textEndInBox(int line, int alignText,string text);
    void changeTextInBox(int line,string text);
    void clearData();
    int getKey();
    int getSizeData();
    saveData getData(int i);
    private:

    int count = 0;
    int countEnd = 0;
    int index = 0;
    int key;
    int left;
    int top;
    int width;
    int height;
    
    vector<saveData> data;
    void colorIndex(int cur,int next);
};

void setColor(int color);
int getTerminalWidth();
int getTerminalHeight();
void gotoXY(int x, int y);
int countDigits(int number);
void erase(int i);

string hideInput();
// void pushData(saveData &data,int n);