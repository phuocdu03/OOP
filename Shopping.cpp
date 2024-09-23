#include "Shopping.h"
bool exists(int i)
{
    for (int j = 0; j < check.size(); ++j) {
            if (check[j] == i) {
            return true;
        }
    }
    return false;
}

void addOrRemove(int i)
{
    bool found = false;
    for (int j = 0; j < check.size(); ++j) {
        if (check[j] == i) {
            check.erase(check.begin() + j);
            found = true;
            break;
        }
    }
    if (!found) {
        check.push_back(i);
    }
}
void markCheck(Box_Product box, int key, int page)
{
    gotoXY(boxShopping.getCursorRightText(),key+boxInventory.getTop()+2);
    addOrRemove(page*10+key-1);
    if(exists(page*10+key-1)){
        setColor(7);
        cout<<char(219);
    }
    else{
        setColor(7);
        cout<<" ";
    }
}
void displayBoxShopping(Box_Product boxShopping,int page)
{
    system("cls");
    boxShopping.clearData();
    boxShopping.drawRectangle();
    boxShopping.displayLabel(1);
    for(int i = page*10;(i<shop.getCountProduct())&&(i<(page*10)+10);i++){
        string str = addSpace(shop.getDataProduct(i).ID,boxShopping.getWidthLabel(0)) + 
                    addSpace(shop.getDataProduct(i).Categorize,boxShopping.getWidthLabel(1)) +
                    addSpace(shop.getDataProduct(i).Name,boxShopping.getWidthLabel(2)) + 
                    addSpace(shop.getDataProduct(i).Price,boxShopping.getWidthLabel(3)) + 
                    addSpace(shop.getDataProduct(i).Quantity,boxShopping.getWidthLabel(4));
        boxShopping.textInBox(i%10+3,-1,str);
        // if(exists(i))
        // {
        //     gotoXY(boxShopping.getCursorRightText(),i%10+boxShopping.getTop()+3);
        //     cout<<char(219);
            
        // }
    }
    boxShopping.textEndInBox(boxShopping.getHeight()-6,-1,">> " + to_string(page+1) + " <<");
    boxShopping.textEndInBox(boxShopping.getHeight()-4,-1,"LOAD TO STORE");
    boxShopping.textEndInBox(boxShopping.getHeight()-2,-1,"Exit");
    while(1){
        int key = boxShopping.getKey();
        
        if(key == boxShopping.getSizeData()){
            check.clear();
            return StoreOption();
        }
            
        else if(key == (boxShopping.getSizeData()-2)){
            int nextPage = (shop.getCountProduct()>(page+1)*10)?(page+1):0;
            return displayBoxShopping(boxShopping,nextPage);
        }
        else if(key == (boxShopping.getSizeData()-1))
            return displayBill(boxShopping,0);
        else markCheck(boxShopping,key,page);
    }

}