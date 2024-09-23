#include <iostream>
#include <vector>
#include <conio.h>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;
struct dataProduct
{
    string ID;
    string Categorize;
    string Name;
    int Price = 0;
    int Quantity = 0;
};
class product{
    private:
    vector<dataProduct> dataP;
    int countCheck = 0;
    int countProduct = 0;
    long cost = 0;
    public:
    void setDataProduct(dataProduct dataP);
    void changeDataProduct(int i,int column,int data);
    void changeDataProduct(int i,int column,string data);
    void addProductByID(string ID,int quantity);
    bool productExist(string ID);
    void clearDataProduct();
    int getCountCheck();
    int getCountProduct();
    long getCost();
    void addCost(long value);
    dataProduct getDataProduct(int i);
    void exportToCSV(const string& filename);
};

bool inputOrSkip(int& variable);

