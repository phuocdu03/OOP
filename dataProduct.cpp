#include "dataProduct.h"

void product::setDataProduct(dataProduct data)
{
    dataP.push_back(dataProduct());
    dataP[countProduct] = data;
    countProduct++;
}

void product::changeDataProduct(int i, int column, int data)
{    
    switch(column)
    {
    case 3:
        dataP[i].Price = data;
        break;
    case 4:
        dataP[i].Quantity = data;
        break;

    default:
        break;
    }
}

void product::changeDataProduct(int i, int column, string data)
{
    switch(column)
    {
    case 0:
        dataP[i].ID = data;
        break;
    case 1:
        dataP[i].Categorize = data;
        break;
    case 2:
        dataP[i].Name = data;
        break;
    default:
        break;
    }
}

void product::addProductByID(string ID, int quantity)
{
    for(int i = 0;i<dataP.size();i++){
        if(dataP[i].ID == ID){
            dataP[i].Quantity += quantity;
            return;
        }
    }
}

bool product::productExist(string ID)
{
    for(int i = 0;i<dataP.size();i++){
        if(dataP[i].ID == ID){
            return true;
        }
    }
    return false;
}

void product::clearDataProduct()
{
    dataP.clear();
    countCheck = 0;
    countProduct = 0;
}

int product::getCountCheck()
{
    return countCheck;
}
int product::getCountProduct()
{
    return countProduct;
}

long product::getCost()
{
    return cost;
}

void product::addCost(long value)
{
    cost += value;
}

dataProduct product::getDataProduct(int i)
{
    return dataP[i];
}

void product::exportToCSV(const string &filename)
{
    ofstream outFile(filename, ios::out | ios::app);

    if (!outFile) {
        cerr << "Unable to open file " << filename << endl;
        return;
    }

    // If file is empty, write header
    if (outFile.tellp() == 0) {
        outFile << "ID,Categorize,Name,Price,Quantity\n";
    }

    // Write data
    for (int i = 0; i < getCountProduct(); ++i) {
        dataProduct currentProduct = getDataProduct(i); // Lấy thông tin của sản phẩm tại vị trí i
        if (currentProduct.Price > 0) {
            outFile << currentProduct.ID << ","
                    << currentProduct.Categorize << ","
                    << currentProduct.Name << ","
                    << currentProduct.Price << ","
                    << currentProduct.Quantity << "\n";
        }
    }

    outFile.close();    
}

bool inputOrSkip(int &variable)
{
    string line;
    bool inputIsValid = false;
    //cin.ignore();
    while (!inputIsValid) {
        getline(cin, line);
        if (line.empty()) {
            return false;
        } else {
            try {
                variable = stoi(line);
                inputIsValid = true;
                return true;
            } catch (invalid_argument& e) {
                cout << "Nhap khong hop le! Vui long nhap lai." << endl;
            } catch (out_of_range& e) {
                cout << "So qua lon hoac qua nho! Vui long nhap lai." << endl;
            }
        }
    }
    return false;
}


product inventory;
product productExport;