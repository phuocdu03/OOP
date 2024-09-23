#include "ImportProduct.h"

extern product inventory;
vector<int> numProduct;

Box_Product boxImport = {'c','c',68,20};
void displayBoxImport(Box_Product boxImport,int page){
    system("cls");
    string str;
    int newvalue;
    //product productChecked;
    //productChecked.clearDataProduct();
    //setDataChecked(productChecked);
    boxImport.clearData();
    boxImport.drawRectangle();
    boxImport.textLabel(-2,-1,"Existing Products");
    boxImport.displayLabel(1);
    for(int i = page*10;(i<inventory.getCountProduct())&&(i<(page*10)+10);i++){
        string str = addSpace(inventory.getDataProduct(i).ID,boxImport.getWidthLabel(0)) + 
                    addSpace(inventory.getDataProduct(i).Categorize,boxImport.getWidthLabel(1)) +
                    addSpace(inventory.getDataProduct(i).Name,boxImport.getWidthLabel(2))  + 
                    addSpace(numProduct[i],boxImport.getWidthLabel(3));
        boxImport.textInBox(i%10+3,-1,str);

    }
    boxImport.textEndInBox(boxImport.getHeight()-6,-1,">> " + to_string(page+1) + " <<");
    boxImport.textEndInBox(boxImport.getHeight()-4,-1,"PUSH TO WAREHOUSE");
    boxImport.textEndInBox(boxImport.getHeight()-2,-1,"Exit");
    while(1){
        int key = boxImport.getKey();
        
        if(key == boxImport.getSizeData())
            return MainMenu();
        else if(key == (boxImport.getSizeData()-2)){
            int nextPage = (inventory.getCountProduct()>(page+1)*10)?(page+1):0;
            return displayBoxImport(boxImport,nextPage);
        }
        else if(key == (boxImport.getSizeData()-1))
            return loading([](){importToWarehouse();},[](){MainMenu();});
        else {
            gotoXY(boxImport.getCursorRightText()-boxImport.getWidthLabel(3)
                    -boxImport.getWidthLabel(4),boxImport.getTop()+2+key);
            cout<<setw(boxImport.getWidthLabel(3)+boxImport.getWidthLabel(4)+1)<<left<<"";
            gotoXY(boxImport.getCursorRightText()-boxImport.getWidthLabel(3)
                    -boxImport.getWidthLabel(4),boxImport.getTop()+2+key);
            cin>>newvalue;
            numProduct[key-1+page*10] = newvalue;
            str = addSpace(inventory.getDataProduct(key-1).ID,boxImport.getWidthLabel(0)) + 
                    addSpace(inventory.getDataProduct(key-1).Categorize,boxImport.getWidthLabel(1)) +
                    addSpace(inventory.getDataProduct(key-1).Name,boxImport.getWidthLabel(2)) + 
                    addSpace(numProduct[key-1+page*10],boxImport.getWidthLabel(3));
                    
            boxImport.changeTextInBox(key-1,str);
        }
    }
}

void importToWarehouse()
{
    for(int i = 0;i<inventory.getCountProduct();i++){
        inventory.changeDataProduct(i,4,inventory.getDataProduct(i).Quantity + numProduct[i]);
    }
    numProduct.clear();
}

void createQuantityInsertVitual()
{
    
    vector<int> quantityInsert;
    int page = 0;
    int width[5] = {15,15,16,8,0};
    string label[5] = {"ID Product","Categorize","Name Product","Quantity"};
    numProduct.clear();
    numProduct.assign(inventory.getCountProduct(),0);
    boxImport.setLabel(label);
    boxImport.setWidthLabel(width);
    displayBoxImport(boxImport,page);
    //quantityInsert.assign(inventory.getCountProduct(),0);
}
void ImportProduct(){

    createQuantityInsertVitual();
    system("pause");
}
// ---------------------------------------------------
bool loadCSVFile(string filename) {
    // Mở file CSV
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    string line;
    // Duyệt qua từng dòng trong file
    while (getline(file, line)) {
        istringstream iss(line);
        string ID, categorize, name, quantity_str;
        int quantity;

        // Tách dữ liệu từng ô trong dòng bằng dấu phẩy (CSV)
        if (getline(iss, ID, ',') && 
            getline(iss, categorize, ',') &&
            getline(iss, name, ',') && 
            getline(iss, quantity_str, ',')) {
            // Chuyển đổi quantity từ string sang int
            istringstream(quantity_str) >> quantity;

            // Kiểm tra xem ID đã tồn tại trong vector hay chưa
            bool found = false;
            for (int i = 0;i<inventory.getCountProduct();i++) {
                if (inventory.getDataProduct(i).ID == ID) {
                    inventory.changeDataProduct(i,4,inventory.getDataProduct(i).Quantity + quantity); // Cộng thêm quantity nếu ID đã tồn tại
                    found = true;
                    break;
                }
            }

            // Nếu ID chưa tồn tại, thêm dữ liệu mới vào vector
            if (!found) {
                inventory.setDataProduct({ID, name, categorize, 0, quantity});
            }
        }
    }
    // Đóng file sau khi đọc xong
    file.close();
    return true;
}
void ImportFromFile()
{
    Box importFromFile;
    string name;
    char key;
    const int left = 2;
    importFromFile = {'c',8,40,5};
    
    while(1){
        system("cls");
        importFromFile.drawRectangle();
        importFromFile.textLabel(-3,-1,"IMPORT FROM FILE");
        importFromFile.textLabel(2,left,"File name:");

        gotoXY(importFromFile.getLeft()+left+10+2,importFromFile.getTop()+2);
        getline(cin,name);
        if(loadCSVFile(name)){
            return loading([](){},[](){MainMenu();});
        }
        else{
            gotoXY(importFromFile.getLeft()+left+10+2,importFromFile.getTop()+2);
            erase(name.length());
            importFromFile.textLabel(5,-1,"Can't Load File, press 'Enter' to retry or 'e' to exit");
            while(1){
            key = _getch();
            if(key == 'e' || key == 'E')
                return MainMenu();
            if(key == '\r')
                break;
            }
        }
    }
    _getch();
}
// ------------------------------------------------------
void ImportNewProduct()
{
    system("cls");
    Box_Product importNewProduct_Box;
    product newProduct;
    dataProduct dataProduct;
    newProduct.clearDataProduct();
    int width[5] = {17,17,17,10,0};
    string label[5] = {"ID Product","Categorize","Name Product","Quantity",""};
    int num = 0;
    char key;
    const int left = 2;
    importNewProduct_Box.clearData();
    importNewProduct_Box = {'c',8,84,5};
    importNewProduct_Box.setWidthLabel(width);
    importNewProduct_Box.setLabel(label);
    importNewProduct_Box.drawRectangle();
    importNewProduct_Box.displayLabel(1);
    while(1){
        importNewProduct_Box.addLine();
        gotoXY(importNewProduct_Box.getCursorRightText()-
            importNewProduct_Box.getWidthLabel(4)-
            importNewProduct_Box.getWidthLabel(3)-
            importNewProduct_Box.getWidthLabel(2)-
            importNewProduct_Box.getWidthLabel(1)-
            importNewProduct_Box.getWidthLabel(0),
            importNewProduct_Box.getTop()+2+num);
            getline(cin>>ws,dataProduct.ID);
        gotoXY(importNewProduct_Box.getCursorRightText()-
            importNewProduct_Box.getWidthLabel(4)-
            importNewProduct_Box.getWidthLabel(3)-
            importNewProduct_Box.getWidthLabel(2)-
            importNewProduct_Box.getWidthLabel(1),
            importNewProduct_Box.getTop()+2+num);
            getline(cin>>ws,dataProduct.Categorize);
        gotoXY(importNewProduct_Box.getCursorRightText()-
            importNewProduct_Box.getWidthLabel(4)-
            importNewProduct_Box.getWidthLabel(3)-
            importNewProduct_Box.getWidthLabel(2),
            importNewProduct_Box.getTop()+2+num);
            getline(cin>>ws,dataProduct.Name);
        gotoXY(importNewProduct_Box.getCursorRightText()-
            importNewProduct_Box.getWidthLabel(4)-
            importNewProduct_Box.getWidthLabel(3),
            importNewProduct_Box.getTop()+2+num);
            cin>>dataProduct.Quantity;
        newProduct.setDataProduct(dataProduct);
        num++;
        if(num<10)
            importNewProduct_Box.textLabel(importNewProduct_Box.getHeight(),-1,
                            "Press 'Enter to continue,'E' to exit, 'L' to load");
        else    
            importNewProduct_Box.textLabel(importNewProduct_Box.getHeight(),-1,
                            "Maximun product,'E' to exit, 'L' to load");                
        while(1){
            key = _getch();
            if(key == '\r' && num<10)
               break;
            else if(key == 'e' || key == 'E')
               return MainMenu();
            else if(key == 'l' || key == 'L'){
                for(int i = 0;i < newProduct.getCountProduct();i++)
                    if(inventory.productExist(newProduct.getDataProduct(i).ID)){
                        importNewProduct_Box.textLabel(importNewProduct_Box.getHeight(),-1,
                            "Import fail, There is a product that already exists");
                        importNewProduct_Box.textLabel(importNewProduct_Box.getHeight()+1,-1,
                            "Press 'Enter' to retry or 'e' to exit");
                        while(1){
                            key = _getch();
                            if(key == 'e' || key == 'E')
                                return MainMenu();
                            if(key == '\r')
                                return ImportNewProduct();
                        }
                    }
                for(int i = 0;i < newProduct.getCountProduct();i++)
                    inventory.setDataProduct(newProduct.getDataProduct(i));
                return loading([](){},[](){MainMenu();});
            }
            
        }
    }
}

