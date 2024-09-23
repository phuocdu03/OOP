#include "drawBox_Product.h"


int Box_Product::getCursorRightText()
{
    return getLeft()-1+(getWidth()+w[0]+w[1]+w[2]+w[3]+w[4]+2)/2;
}

int *Box_Product::getWidthLabel()
{
    return w;
}

int Box_Product::getWidthLabel(int column)
{
    return w[column];
}

void Box_Product::setWidthLabel(int width[5])
{
    for(int i = 0;i<5;i++)
        w[i] = width[i];
}

void Box_Product::setWidthLabel(int column, int width)
{
    w[column] = width; 
}

void Box_Product::setPage(int Page)
{
    page = Page;
}

void Box_Product::setLabel(string label[5])
{
    for(int i = 0;i<5;i++)
        Label[i] = label[i];
}

void Box_Product::setLabel(int column, string name)
{
    Label[column] = name;
}

void Box_Product::displayLabel(int row)
{
    string label = addSpace(Label[0],w[0]) + addSpace(Label[1],w[1]) +
                    addSpace(Label[2],w[2]) + addSpace(Label[3],w[3]) + addSpace(Label[4],w[4]);
    textLabel(row,-1,label);
}

void loading(function<void()> callback1, function<void()> callback2,string str)
{
    Box load;
    load = {'c','c',48,7};
    system("cls");
    load.drawRectangle();
    load.textLabel(1,1,"Uploading...");
    callback1();
    gotoXY(load.getLeft()+2,load.getTop()+2);
    for(int i = 0; i< load.getWidth()-4;i++){
        cout<<char(219);
        Sleep(10);
    }
    Sleep(100);
    load.textLabel(4,1,str);
    while(1){
        int key = _getch();
        if(key == 'r')
            return callback2();;
    }
}

string addSpace(string str, int n)
{
    int add = n - str.length() ;
    string strSpace = str;
    for(int i = 0;i<add;i++)
        strSpace += " ";
    return strSpace;
}

string addSpace(int num, int n)
{
    int add;
    string strSpace = "";
    if(num == -1) 
        add = n;
    else{
        add = n - countDigits(num);
        strSpace = to_string(num);
    }
    for(int i = 0;i<add;i++)
        strSpace += " ";
    return strSpace;
}