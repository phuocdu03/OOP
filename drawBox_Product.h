#ifndef DRAWBOX_H
#define DRAWBOX_H
#include "drawBox.h"
#endif
#include <functional>
class Box_Product: public Box{
    int w[5] = {0,0,0,0,0};
    int page = 0;
    string Label[5] = {"","","","",""};
    public:
    Box_Product():Box(){};
    Box_Product(int l,int t,int w,int h):Box(l,t,w,h){};
    Box_Product(char l, char t,int w,int h):Box(l,t,w,h){};
    Box_Product(int l, char t,int w,int h):Box(l,t,w,h){};
    Box_Product(char l, int t,int w,int h):Box(l,t,w,h){};
    int getCursorRightText();
    int* getWidthLabel();
    int getWidthLabel(int column);
    void setWidthLabel(int width[5]);
    void setWidthLabel(int column, int width);
    void setPage(int Page);
    void setLabel(string label[5]);
    void setLabel(int column,string name);
    void displayLabel(int row);



};
void loading(function<void()> callback1, function<void()> callback2, string str = "Finished upload ! Press 'r' to continue..." );
string addSpace(string str, int n);
string addSpace(int num, int n);