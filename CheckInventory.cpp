#include "CheckInventory.h"

vector<int> check;
extern product inventory;
extern product productExport;
Box_Product boxInventory = {'c','c',84,20};

//  
bool exists(int i)
{
    for (int j = 0; j < check.size(); ++j) {
            if (check[j] == i) {
            return true;
        }
    }
    return false;
}
// kiểm tra  tick và  bỏ tick sp
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
//đánh dấu những vị trí đã tick 
void markCheck(Box_Product box, int key, int page)
{
    gotoXY(boxInventory.getCursorRightText(),key+boxInventory.getTop()+2);
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
// cập nhật sp cho store từ kho
void updateStore(product& productChecked)
{
    for(int i = 0;i<check.size();i++){
        inventory.changeDataProduct(check[i],3,productChecked.getDataProduct(i).Price);
        inventory.changeDataProduct(check[i],4,inventory.getDataProduct(check[i]).Quantity - productChecked.getDataProduct(i).Quantity);
        if(productChecked.getDataProduct(i).Quantity > 0){
            int j;
            for(j = 0;j < productExport.getCountProduct();j++){
                if(productExport.getDataProduct(j).ID == productChecked.getDataProduct(i).ID){
                    productExport.changeDataProduct(j,4,productExport.getDataProduct(j).Quantity +
                                                       productChecked.getDataProduct(i).Quantity);
                break;
                }
            }
            if(j == productExport.getCountProduct())
                productExport.setDataProduct(productChecked.getDataProduct(i));
            productExport.addCost(productChecked.getDataProduct(i).Price*productChecked.getDataProduct(i).Quantity);
        }
    }
    check.clear();
    productChecked.clearDataProduct();
}
//
void setDataChecked(product& productChecked){
    int i = 0;
    productChecked.clearDataProduct();
    for(int i = 0;i<check.size();i++){
        productChecked.setDataProduct({inventory.getDataProduct(check[i]).ID,
                                       inventory.getDataProduct(check[i]).Categorize,
                                       inventory.getDataProduct(check[i]).Name,
                                       inventory.getDataProduct(check[i]).Price,
                                       0});
    }
}
// hiển thị box và sản phẩm store
void displayBoxPushToStore(Box_Product boxInventory,int page){
    system("cls");
    string str;
    int newvalue;
    product productChecked;
    productChecked.clearDataProduct();
    setDataChecked(productChecked);
    boxInventory.clearData();
    boxInventory.drawRectangle();
    boxInventory.textLabel(-2,-1,"UPDATED FOR EXPORT");
    boxInventory.displayLabel(1);
    for(int i = page*10;(i<productChecked.getCountProduct())&&(i<(page*10)+10);i++){
        string str = addSpace(productChecked.getDataProduct(i).ID,boxInventory.getWidthLabel(0)) + 
                    addSpace(productChecked.getDataProduct(i).Categorize,boxInventory.getWidthLabel(1)) +
                    addSpace(productChecked.getDataProduct(i).Name,boxInventory.getWidthLabel(2)) + 
                    addSpace(productChecked.getDataProduct(i).Price,boxInventory.getWidthLabel(3)) + 
                    addSpace(0,boxInventory.getWidthLabel(4)-1);
        boxInventory.textInBox(i%10+3,-1,str);

    }
    boxInventory.textEndInBox(boxInventory.getHeight()-6,-1,">> " + to_string(page+1) + " <<");
    boxInventory.textEndInBox(boxInventory.getHeight()-4,-1,"Export");
    boxInventory.textEndInBox(boxInventory.getHeight()-2,-1,"Exit");
    while(1){
        int key = boxInventory.getKey();
        
        if(key == boxInventory.getSizeData()){
            check.clear();
            return MainMenu();
        }
            
        else if(key == (boxInventory.getSizeData()-2)){
            int nextPage = (productChecked.getCountProduct()>(page+1)*10)?(page+1):0;
            return displayBoxPushToStore(boxInventory,nextPage);
        }
        else if(key == (boxInventory.getSizeData()-1))
            return loading([&productChecked](){updateStore(productChecked);},
                            [boxInventory](){displayBoxAndProduct(boxInventory,0);});
        else {
            gotoXY(boxInventory.getCursorRightText()-boxInventory.getWidthLabel(3)
                    -boxInventory.getWidthLabel(4),boxInventory.getTop()+2+key);
            cout<<setw(boxInventory.getWidthLabel(3)+boxInventory.getWidthLabel(4)+1)<<left<<"";
            gotoXY(boxInventory.getCursorRightText()-boxInventory.getWidthLabel(3)
                    -boxInventory.getWidthLabel(4),boxInventory.getTop()+2+key);
            if(inputOrSkip(newvalue))
                productChecked.changeDataProduct(key-1,3,newvalue);
            else{
                gotoXY(boxInventory.getCursorRightText()-boxInventory.getWidthLabel(3)
                    -boxInventory.getWidthLabel(4),boxInventory.getTop()+2+key);
                cout<<productChecked.getDataProduct(key-1).Price;
            }
            gotoXY(boxInventory.getCursorRightText()-boxInventory.getWidthLabel(4)
                    ,boxInventory.getTop()+2+key);
            if(inputOrSkip(newvalue))
                productChecked.changeDataProduct(key-1,4,newvalue);
            else{
                gotoXY(boxInventory.getCursorRightText()-boxInventory.getWidthLabel(4)
                    ,boxInventory.getTop()+2+key);
                cout<<productChecked.getDataProduct(key-1).Quantity;
            }
            str =   addSpace(productChecked.getDataProduct(key-1).ID,boxInventory.getWidthLabel(0)) + 
                    addSpace(productChecked.getDataProduct(key-1).Categorize,boxInventory.getWidthLabel(1)) +
                    addSpace(productChecked.getDataProduct(key-1).Name,boxInventory.getWidthLabel(2)) + 
                    addSpace(productChecked.getDataProduct(key-1).Price,boxInventory.getWidthLabel(3)) + 
                    addSpace(productChecked.getDataProduct(key-1).Quantity,boxInventory.getWidthLabel(4));
            boxInventory.changeTextInBox(key-1,str);
        }
    }
}
// hiển thị box và sản phẩm từ kho
void displayBoxAndProduct(Box_Product boxInventory, int page)
{
    system("cls");
    boxInventory.clearData();
    boxInventory.drawRectangle();
    boxInventory.textLabel(-2,-1,"STOREHOUSE");
    boxInventory.displayLabel(1);
    for(int i = page*10;(i<inventory.getCountProduct())&&(i<(page*10)+10);i++){
        string str = addSpace(inventory.getDataProduct(i).ID,boxInventory.getWidthLabel(0)) + 
                    addSpace(inventory.getDataProduct(i).Categorize,boxInventory.getWidthLabel(1)) +
                    addSpace(inventory.getDataProduct(i).Name,boxInventory.getWidthLabel(2)) + 
                    addSpace(inventory.getDataProduct(i).Price,boxInventory.getWidthLabel(3)) + 
                    addSpace(inventory.getDataProduct(i).Quantity,boxInventory.getWidthLabel(4));
        boxInventory.textInBox(i%10+3,-1,str);
        if(exists(i))
        {
            gotoXY(boxInventory.getCursorRightText(),i%10+boxInventory.getTop()+3);
            cout<<char(219);
            
        }
    }
    boxInventory.textEndInBox(boxInventory.getHeight()-6,-1,">> " + to_string(page+1) + " <<");
    boxInventory.textEndInBox(boxInventory.getHeight()-4,-1,"Fine_tune For Export");
    boxInventory.textEndInBox(boxInventory.getHeight()-2,-1,"Exit");
    while(1){
        int key = boxInventory.getKey();
        
        if(key == boxInventory.getSizeData()){
            check.clear();
            return MainMenu();
        }
            
        else if(key == (boxInventory.getSizeData()-2)){
            int nextPage = (inventory.getCountProduct()>(page+1)*10)?(page+1):0;
            return displayBoxAndProduct(boxInventory,nextPage);
        }
        else if(key == (boxInventory.getSizeData()-1))
            return displayBoxPushToStore(boxInventory,0);
        else markCheck(boxInventory,key,page);
    }
}
// kiểm tra những sp đã đc chọn để 
void CheckInventory()
{   
    int width[5] = {15,15,16,10,8};
    string label[5] = {"ID Product","Categorize","Name Product","Price","Quantity"};
    
    int page = 0;
    //callProductTest();
    boxInventory.setWidthLabel(width);
    boxInventory.setLabel(label);
    displayBoxAndProduct(boxInventory,0); 
    return ;
}