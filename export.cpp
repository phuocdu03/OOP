#include "export.h"
Box_Product boxproductExport = {'c','c',60,20};
tm *ltm;
string getDate()
{
    char symbol = '/';
    return to_string(ltm->tm_mday) + symbol + to_string(1+ltm->tm_mon) + symbol + to_string(1900+ltm->tm_year);
}
void displayInfomationExport(int page)
{
    system("cls"); 
    boxproductExport.clearData();
    boxproductExport.drawRectangle();
    boxproductExport.textLabel(-2,-1,"Report Export Product");
    boxproductExport.textLabel(1,4,"Date: " + getDate());  
    boxproductExport.textLabel(2,4,"User name: " + user.getCurrentUserInfo().fullName);
    boxproductExport.textLabel(2,(boxproductExport.getWidth())/2 + 4,"Total cost: " + to_string(productExport.getCost()));
    boxproductExport.textLabel(3,4,"ID:  " + user.getCurrentUserInfo().ID);
    boxproductExport.textLabel(1,-1,"|");
    boxproductExport.textLabel(2,-1,"|");
    boxproductExport.textLabel(3,-1,"|");
    // boxproductExport.textLabel(4,-1,"|");
    boxproductExport.textLabel(4,-1,"********************************************************");
    boxproductExport.displayLabel(6);
    for(int i = page*5;(i<productExport.getCountProduct())&&(i<(page*5)+5);i++){
        string str = addSpace(productExport.getDataProduct(i).ID,boxproductExport.getWidthLabel(0)) + 
                    addSpace(productExport.getDataProduct(i).Categorize,boxproductExport.getWidthLabel(1)) +
                    addSpace(productExport.getDataProduct(i).Name,boxproductExport.getWidthLabel(2)) +  
                    addSpace(productExport.getDataProduct(i).Quantity,boxproductExport.getWidthLabel(3));
        boxproductExport.textLabel(i%5+3+4,-1,str);
    }
    boxproductExport.textEndInBox(boxproductExport.getHeight()-6,-1,">> " + to_string(page+1) + " <<");
    boxproductExport.textEndInBox(boxproductExport.getHeight()-4,-1,"Export to CSV File");
    boxproductExport.textEndInBox(boxproductExport.getHeight()-2,-1,"Exit");
    while(1){
        int key = boxproductExport.getKey();
        
        if(key == boxproductExport.getSizeData()){
            return MainMenu();
        }   
        else if(key == (boxproductExport.getSizeData()-1)){
            Export_CSV();
            boxproductExport.textLabel(boxproductExport.getHeight(),-1,
                            "Export Successfully, automatically exits after 3s ");
            _sleep(1000);
            boxproductExport.textLabel(boxproductExport.getHeight(),-1,
                            "Export Successfully, automatically exits after 2s ");
            _sleep(1000);
            boxproductExport.textLabel(boxproductExport.getHeight(),-1,
                            "Export Successfully, automatically exits after 1s ");
            _sleep(1000);
            return MainMenu();

        }
        else if(key == (boxproductExport.getSizeData()-2)){
            int nextPage = (productExport.getCountProduct()>(page+1)*5)?(page+1):0;
            return displayInfomationExport(nextPage);
        }
            
        // else if(key == (boxInventory.getSizeData()-2)){
        //     int nextPage = (inventory.getCountProduct()>(page+1)*10)?(page+1):0;
        //     return displayBoxAndProduct(boxInventory,nextPage);
        // }
        // else if(key == (boxInventory.getSizeData()-1))
        //     return displayBoxPushToStore(boxInventory,0);
        // else markCheck(boxInventory,key,page);
    }
    system("pause");
}

void Export()
{
    time_t now = time(0);
    ltm = localtime(&now);
    int width[5] = {15,15,16,8,0};
    string label[5] = {"ID Product","Categorize","Name Product","Quantity",""};
    boxproductExport.setWidthLabel(width);
    boxproductExport.setLabel(label);
    return displayInfomationExport(0);
}

void Export_CSV()
{
    // time_t now;
    // tm *ltm = localtime(&now);
    int year = 1900 + ltm->tm_year;
    int mon = 1 + ltm->tm_mon;
    int day = ltm->tm_mday;
    int hour = ltm->tm_hour;
    int min = ltm->tm_min;
    int sec = ltm->tm_sec;
    char symbol = '_';
    string filename = user.getCurrentUserInfo().fullName + symbol + 
        to_string(day) + to_string(mon) + to_string(year) + symbol + 
        to_string(hour) + to_string(min) + to_string(sec) + ".csv";
    ofstream fileOut(filename);
    if (!fileOut.is_open()) {
        cout << "Không thể mở file" << endl;
        return;
    }

    fileOut << "Date: "<< getDate()<<endl;
    fileOut << "Username: "<< user.getCurrentUserInfo().fullName<<endl;
    fileOut << "ID: " << user.getCurrentUserInfo().ID<<endl;
    fileOut << "-------------------------------------"<<endl;
    fileOut << "Total cost: "<<productExport.getCost()<<endl;
    fileOut << "***********************************************************************************"<<endl;

    for (int i = 0;i < productExport.getCountProduct();i++) {
        fileOut << productExport.getDataProduct(i).ID <<',' ;
        fileOut << productExport.getDataProduct(i).Categorize << ',';
        fileOut << productExport.getDataProduct(i).Name << ',';
        fileOut << productExport.getDataProduct(i).Quantity << endl;
    }
    fileOut.close();
    // cout << "Number of sec since January 1,1970 is:: " << now << endl;
    // cout << "Year:" << 1900 + ltm->tm_year<<endl;
    // cout << "Month: "<< 1 + ltm->tm_mon<< endl;
    // cout << "Day: "<< ltm->tm_mday << endl;
    // cout << "Time: "<< 5+ltm->tm_hour << ":";
    // cout << 30+ltm->tm_min << ":";
    // cout << ltm->tm_sec << endl;

}
