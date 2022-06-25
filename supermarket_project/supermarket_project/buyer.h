#pragma once
#include<string>
#include<map>
#include<queue>
#include<windows.h>
using namespace std;

struct productDataa 
{
	productDataa() :
		category(), qty(), price() {}//it's better to take data with constructor
	productDataa(string pname, double p_price, string pcategory , int pqut) :
		category(pcategory), p_name(pname), qty(pqut), price(p_price) {}
	string category;
	string p_name;
	int  qty;
	double price;
};

class buyer
{
public:
	//seller name ,id , product name ,category , ptoduct id, quantity, price 
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	map< pair<string, int>, pair<double,double>>rate;
	map< string, pair<double,double>>sellerrate;
	map< pair<string,int>, productDataa>products;
	map< pair<string, pair<int, string>>, int > cartcheck;
	map< pair<string, int>, productDataa> cart;
	map<int, pair< int, int>> check;
	map<int, pair< string, string>> ratecarry;
	map<int, int> items_added;
	map<int, int> remove;
	queue<int> q;
	queue<string>s;
	string category;
	string seller_name;
	string name;
	string username;
	string logineduser;
	double stars;
	double numberofpeople;
	int id;
	int quantity;
	double price;
	double totalprice;
public:
	buyer(string);
	void clear();
	void ratesystem(string,int,string);
	void rateupdate();
	void rate_file();
	void sellerrateintialize();
	void sellerrateupdate();
	void sellerrate_file();
	void productcheck();
	void file_edit();
	void cart_map();
	void cart_edit();
	void product_category();
	void display_search(); 
	void file_fetch(); 
	void buy_product();
	void show_sellers();
	void pay();
	void add_to_cart();
	void remove_from_cart();
	void displaycart(); 
	~buyer();
};