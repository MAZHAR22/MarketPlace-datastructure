#include "seller.h"
#include<string>
#include<fstream>
#include<map>
#include<iostream>
#include <cstdlib>
#include<windows.h>

using namespace std;
seller::seller(string sname)
{
	file_fetch(sname);
}
/*done*/void seller::file_fetch(string sname)
{
	ifstream product_file("products.txt");
	//fetch all saved data to map (file_data)
	while (product_file >> seller_name >> pid >> name >> price >> category >> quantity) {
		if (seller_name == sname)
			file_data[{seller_name, pid}] = productData(name, price, category, quantity);
		all_data[{seller_name, pid}] = productData(name, price, category, quantity);
	}
	seller_name = sname;
	product_file.close();
	//	remove("products.txt");
		//remove product file after file fetch 3shan lama ashil mn el map my2thrsh
}
/*done*/void seller::welcome()
{

}
void seller::addproduct()
{
	SetConsoleTextAttribute(h, 2);
	cout << "\nEnter the id, name, price, category, and quantity of the product you want to add:\n";
	SetConsoleTextAttribute(h, 7);
	cin >> pid >> name >> price >> category >> quantity;

	if (searchproduct(pid))//if it doesn't find the name
	{
		file_data[{seller_name, pid}] = productData(name, price, category, quantity);
		all_data[{seller_name, pid}] = productData(name, price, category, quantity);
		updateFile();
	}
	else {//the seller has a product with the same name
		SetConsoleTextAttribute(h, 4);
		cout << "this product already exists\n";
		SetConsoleTextAttribute(h, 7);
		cout << "1)add another product2)go back\n3)modify a product\n";
		int choice; cin >> choice;
		if (choice == 1) addproduct();
		else if (choice == 2)  welcome();
		else if (choice == 3) modifyproduct();
		else {
			SetConsoleTextAttribute(h, 4);
			cout << "invalid choice";
			SetConsoleTextAttribute(h, 7);
			welcome();
		}
	}
}
/*done*/void seller::displayproduct()
{

	if (file_data.empty())
	{
		SetConsoleTextAttribute(h, 4);
		cout << "\t\t" << "< no data was found >" << endl;
		SetConsoleTextAttribute(h, 7);
	}
	else
	{
		cout << "\t\tname   category\tid\tquantity\tprice\n";
	}
	for (auto p : file_data) {
		cout << p.first.first << " " << p.first.second << " " << p.second.name << " " << p.second.price << " " << p.second.category << " " << p.second.qty << "\n";
	}


}
/*done*/void seller::removeproduct()
{
	//display all product and let him choose which product he want to remove
	displayproduct();
	SetConsoleTextAttribute(h, 2);
	cout << "choose the id of product you want to remove: "; cin >> pid;
	SetConsoleTextAttribute(h, 7);
	if (searchproduct(pid)) {
		SetConsoleTextAttribute(h, 4);
		cout << pid << " doesn't exist\n";
		SetConsoleTextAttribute(h, 7);
		removeproduct(); //needs handling
	}
	else
	{
		file_data.erase(make_pair(seller_name, pid));
		all_data.erase(make_pair(seller_name, pid));
		updateFile();
	}
}
void seller::modifyproduct()
{
	//display all product and let him choose which product he want to modify
	displayproduct();
	SetConsoleTextAttribute(h, 2);
	cout << "choose the id of product you want to modify: "; cin >> pid;
	SetConsoleTextAttribute(h, 7);
	if (searchproduct(pid)) {
		SetConsoleTextAttribute(h, 4);
		cout << pid << " doesn't exist\n";
		SetConsoleTextAttribute(h, 7);
		int choice;

		cout << "1)Modify another"<<endl;
		SetConsoleTextAttribute(h, 14);
		cout << "any other key to go back" << endl;
		SetConsoleTextAttribute(h, 7);
		cin >> choice;
		if (choice == 1)
		{
			modifyproduct();
		}
		else
		{
			return ;
		}
	}
	else
	{

		SetConsoleTextAttribute(h, 2);
		cout << "what do you want to modify?\n";
		SetConsoleTextAttribute(h, 7);
		cout << "1)category\n2)quantity\n3)price\n";
		int choice; cin >> choice;
		if (choice == 1) {
			SetConsoleTextAttribute(h, 14);
			cout << "the past category name is ";
			SetConsoleTextAttribute(h, 7);
			cout << file_data[{seller_name, pid}].category;
			SetConsoleTextAttribute(h, 2);
			cout << "\n what do you want to change it with? ";
			SetConsoleTextAttribute(h, 7);
			string c; cin >> c;
			file_data[{seller_name, pid}].category = c;
			all_data[{seller_name, pid}].category = c;

		}
		else if (choice == 2) {
			SetConsoleTextAttribute(h, 14);
			cout << "the past quantity is ";
			SetConsoleTextAttribute(h, 7);
			cout << file_data[{seller_name, pid}].qty;
			SetConsoleTextAttribute(h, 2);
			cout << "\n what do you want to change it with? ";
			int q; cin >> q;
			file_data[{seller_name, pid}].qty = q;
			all_data[{seller_name, pid}].qty = q;

			updateFile();
		}
		else if (choice == 3) {
			SetConsoleTextAttribute(h, 14);
			cout << "the past price is ";
			SetConsoleTextAttribute(h, 7);
			cout << file_data[{seller_name, pid}].price;
			SetConsoleTextAttribute(h, 2);
			cout << "\n what do you want to change it with? ";
			double x; cin >> x;
			file_data[{seller_name, pid}].price = x;
			all_data[{seller_name, pid}].price = x;
			/*for (pr p : file_data)
			{
				if (p.first.second == name) {
					file_data[{seller_name,name}].price = x;
					break;
				}
			}
			updateFile();*/

		}
		else {
			SetConsoleTextAttribute(h, 4);
			cout << "invalid choice\n";
			SetConsoleTextAttribute(h, 7);
			modifyproduct();
		}
		updateFile();
	}
}
/*done*/bool seller::searchproduct(int id)
{
	map<pair<string, int>, productData>::iterator i;
	i = file_data.find({ seller_name,id });
	if (i == file_data.end())//if it doesn't find the name
		return true;
	else
		return false; //product is there 

}
/*done*/void seller::updateFile()
{
	ofstream product_file("products.txt", ios::out | ios::trunc);
	for (auto p : all_data) {
		product_file << p.first.first << " " << p.first.second << " " << p.second.name << " " << p.second.price << " " << p.second.category << " " << p.second.qty << "\n";
	}
}

void seller::fileData()
{
	SetConsoleTextAttribute(h, 2);
	cout << "data in all-data map:\n";
	SetConsoleTextAttribute(h, 7);
	for (auto p : all_data)
		cout << p.first.first << " " << p.first.second << " " << p.second.name << " " << p.second.price << " " << p.second.category << " " << p.second.qty << "\n";
	SetConsoleTextAttribute(h, 2);
	cout << "\n\ndata in file-data map:\n";
	SetConsoleTextAttribute(h, 7);
	for (auto p : file_data)
		cout << p.first.first << " " << p.first.second << " " << p.second.name << " " << p.second.price << " " << p.second.category << " " << p.second.qty << "\n";

}



seller::~seller()
{
}