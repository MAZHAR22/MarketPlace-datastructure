#pragma once
#include<string>
#include<map>
#include <fstream>
#include <utility>
#include<windows.h>

using namespace std;

struct productData {
    productData() :
        name(), price(), category(), qty() {}//it's better to take data with constructor
    productData(string pname, double pprice, string pcategory, int pqty) :
        name(pname), price(pprice), category(pcategory), qty(pqty) {}
    string category, name;
    int qty;
    double price;
};
class seller
{
public:
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    //buyer name , product name ,category pid quantity , price
    map<pair<string, int>, productData>file_data;// current seller products
    map<pair<string, int>, productData>all_data;// all products(for modify and delete functions)
    string seller_name;
    string name;
    string category;
    int pid;
    int quantity;
    double price;
public:
    seller(string sname);
    void file_fetch(string sname);
    void welcome();
    void addproduct();
    void removeproduct();
    void modifyproduct();
    void displayproduct();
    bool searchproduct(int id);
    void updateFile();
    void fileData();
    ~seller();
};