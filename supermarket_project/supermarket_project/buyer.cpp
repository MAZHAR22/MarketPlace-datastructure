#include "buyer.h"
#include<string>
#include<fstream>
#include<map>
#include<iostream>
#include<windows.h>

using namespace std;

buyer::buyer(string name)
{
	logineduser = name;
	sellerrateintialize();
	cart_map();
	file_fetch();
	productcheck();
	rateupdate();
	sellerrateupdate();
}
void buyer::sellerrateintialize()
{
	ifstream thefile("products.txt");
	while (thefile >> seller_name >> id >> name >> price >> category >> quantity)
	{
		sellerrate[seller_name] = make_pair(0, 0);
	}
	thefile.close();
}
void buyer::sellerrateupdate()
{
	ifstream thefile("sellerrates.txt");
	while (thefile >> seller_name >> stars >> numberofpeople)
	{
		sellerrate[seller_name] = make_pair(stars, numberofpeople);
	}
	thefile.close();
}
void buyer::sellerrate_file()
{
	fstream product("sellerrates.txt", ios::out);
	map < string, pair<double, double>> ::iterator prod = sellerrate.begin();
	for (; prod != sellerrate.end(); prod++)
	{
		product << prod->first<< " " << prod->second.first << " " << prod->second.second << endl;
	}
	product.close();
}

void buyer::rateupdate()
{
	ifstream thefile("rate.txt");
	while (thefile >> seller_name >> id >> stars>>numberofpeople)
	{
		rate[{seller_name, id}] = make_pair(stars,numberofpeople);
	}
	thefile.close();
}
void buyer::rate_file()
{
	fstream product("rate.txt", ios::out);
	map < pair<string, int>, pair<double, double>> ::iterator prod = rate.begin();
	for (; prod != rate.end(); prod++)
	{
		product << prod->first.first << " " << prod->first.second << " " << prod->second.first << " " << prod->second.second << endl;
	}
	product.close();
}

void buyer::productcheck()
{
	map< pair<string, int>, productDataa> ::iterator prod = cart.begin();
	for (; prod != cart.end(); prod++)
	{
		cartcheck[{prod->first.first, { prod->first.second, prod->second.p_name}}] = prod->second.qty;
		remove.insert({ prod->first.second , cartcheck[{prod->first.first, { prod->first.second, prod->second.p_name }}] });
	}
}

void buyer::file_fetch()
{
	//seller name ,id , product name ,category , quantity, price 
	//fetch all saved data to map (products)
	ifstream thefile("products.txt");
	while (thefile >> seller_name >> id >> name >> price >> category >> quantity)
	{
		
		products[{seller_name , id}] = productDataa(name, price, category, quantity);
	}
	thefile.close();
}

void buyer::file_edit()
{
	fstream product("products.txt", ios::out );
	map< pair<string, int>, productDataa> :: iterator prod = products.begin();
	for (; prod != products.end(); prod++)
	{
		product << prod->first.first << " " << prod->first.second << " " << prod->second.p_name << " " << prod->second.price << " " << prod->second.category << " " << prod->second.qty<<endl;
	}
	product.close();
}

void buyer::cart_edit()
{
	fstream product(logineduser, ios::out );
	map< pair<string, int>, productDataa> ::iterator prod = cart.begin();
	for (; prod != cart.end(); prod++)
	{
		product << prod->first.first << " " << prod->first.second << " " << prod->second.p_name << " " << prod->second.price << " " <<prod->second.category<<" " << cartcheck[{prod->first.first, {prod->first.second, prod->second.p_name}}] << endl;
	}
	product.close();
}

void buyer::cart_map()
{
	ifstream thefile(logineduser);
	cart.clear();
	while (thefile >> seller_name >> id >> name >> price >> category >> quantity)
	{
		
		cart[{seller_name, id}] = productDataa(name, price, category, quantity);
		remove.insert({ id , quantity });
	}
	thefile.close();
}

void buyer::clear()
{
	fstream ofs;
	ofs.open(logineduser, ios::out | ios::trunc);
	ofs << "";
	ofs.close();
}

void buyer::remove_from_cart()
{
	//input what product user want to remove from cart and remove it from file (cart)
	int i = 1;
	int ch;
	fstream cartt(logineduser, ios::in | ios::app);
	if (cart.empty())
	{
		SetConsoleTextAttribute(h, 4);
		cout << "\t\t your cart is empty " << endl;
		SetConsoleTextAttribute(h, 7);
	}
	else
	{

	cout << "\tSeller Name , Id , Product Name , Price , Category , Quantity " << endl;
	while (!cartt.eof())
	{
		string line;
		getline(cartt, line);

		if (line == "")break;
		cout << i << ") " << line << endl;
		q.push(i);
		s.push(line);
		i++;
	}
	cartt.close();
	clear();

		ofstream file(logineduser);
		SetConsoleTextAttribute(h, 2);
		cout << "Enter the number of product you want to remove : ";
		SetConsoleTextAttribute(h, 7);
		cin >> ch; 
		cout << endl;
		cartt >> seller_name >> id >> name >> price >> category >> quantity;
		while (!q.empty())
		{
			if (ch != q.front())
			{
				file << s.front() << endl;
			}
			else
			{
			}
			q.pop();
			s.pop();
		}
		file.close();
		map<int, int > ::iterator it = remove.begin();
		map< pair<string, int>, productDataa> :: iterator prod;
		for (; it != remove.end(); it++)
		{
			for (prod = products.begin(); prod != products.end(); prod++)
			{
				if (it->first == prod->first.second)
				{
					prod->second.qty += it->second;
					break;
				}
			}
		}
		file_edit();
		cart_map();
		SetConsoleTextAttribute(h, 2);
		cout << "Product removed successfully" << endl;
		SetConsoleTextAttribute(h, 7);
	}
}

void buyer::buy_product()
{
	//display make buyer choose which product he want and quantity
m:
	file_fetch();
	int choice;
	int pn;
	int qu;
	cout << "\t_____________________________________________________________________\n";
	cout << "\t\t\t\t LIST OF PRODUCT : \n";
	cout << "\t______________________________________________________________________\n";
	map< pair<string, int>, productDataa>::iterator it = products.begin();

	int i = 1;
	for (; it != products.end(); it++)
	{
		SetConsoleTextAttribute(h, 14);
		cout << "| " << i << ") " << " Name : ";
		SetConsoleTextAttribute(h, 7);
		cout << it->second.p_name;
		SetConsoleTextAttribute(h, 14);
		cout << " | " << "Price: ";
		SetConsoleTextAttribute(h, 7);
		cout << it->second.price;
		SetConsoleTextAttribute(h, 14);
		cout << " | " << "Quantity: ";
		SetConsoleTextAttribute(h, 7);
		cout << it->second.qty;
		SetConsoleTextAttribute(h, 14);
		cout << " | " << "Category: ";
		SetConsoleTextAttribute(h, 7);
		cout << it->second.category;
		SetConsoleTextAttribute(h, 14);
		cout << " | " << "Product Id : ";
		SetConsoleTextAttribute(h, 7);
		cout<< it->first.second;
		cout << endl;
		//takes the number of product , id and quantity
		// the number of product -> i
		//id -> first.second.first
		//quantity ->second.second.second
		check.insert({ i,{ it->first.second,it->second.qty } });
		ratecarry.insert({ i,{ it->first.first,it->second.p_name } });
		i++;
	}
k:
	SetConsoleTextAttribute(h, 2);
	cout << "Product Number : ";
	SetConsoleTextAttribute(h, 7);
	cin >> pn;
	cout << endl;
	if (pn > i || pn == 0)
	{
		SetConsoleTextAttribute(h, 4);
		cout << "Invalid choice " << endl;
		SetConsoleTextAttribute(h, 7);
		system("cls");
		goto m;
	}
	else
	{
		SetConsoleTextAttribute(h, 2);
		cout << "Product Quantity : ";
		SetConsoleTextAttribute(h, 7);
		cin >> qu;
		cout << endl;
		if (check[pn].second < qu)
		{
			SetConsoleTextAttribute(h, 4);
			cout << "we don't have this quantity of this product please try again\n";
			SetConsoleTextAttribute(h, 7);
			goto k;
		}
		//takes the number of product and quantity
		items_added.insert({ pn,qu });
		ratesystem(ratecarry[pn].first, check[pn].first, ratecarry[pn].second);
		SetConsoleTextAttribute(h, 14);
		cout << "press 1 to add another product \nany other key if u don't want to add  " << endl;
		SetConsoleTextAttribute(h, 7);
		cin >> choice;
		cout << endl;

		add_to_cart();
		if (choice == 1)
		{
			system("cls");
			goto m;
		}
	}
	
}
void buyer::show_sellers()
{
	map<string,double> leaderboard;
	map < string, pair<double, double>> ::iterator seller = sellerrate.begin();
	for (; seller != sellerrate.end(); seller++)
	{
		if(seller->second.second==0)
		leaderboard[seller->first] = 0.0;
		else
		leaderboard[seller->first] = (seller->second.first / seller->second.second);
	}
	cout << " seller_name\t\trate" << endl;

	for (auto p : leaderboard)
	{
		cout <<" "<< p.first << "\t\t\t" << p.second << endl;
	}
}
void buyer::ratesystem(string seller_name,int id,string product_name)
{
	int choice;
	double score=100;
	double sellerscore = 100;

	SetConsoleTextAttribute(h, 2);
	cout << "do you want to rate " << product_name <<" and seller "<<seller_name<< endl;
	if (rate[{seller_name, id}].second == 0)
	{
		cout << "<product not rated yet>" << endl;
	}
	else
	{
		cout << " rate : " << (rate[{seller_name, id}].first / rate[{seller_name, id}].second) << endl;
	}
	SetConsoleTextAttribute(h, 14);
	cout << "press 1 if you want to rate else press any other key : " << endl ;
	cin >> choice;
	if (choice == 1)
	{
		while (score>5)
		{
			cout << "rate product "<<product_name<<" of 5 : " << endl;
			cin >> score;
		}
		rate[{seller_name, id}].first += score;
		rate[{seller_name, id}].second++;
		rate_file();
		while (sellerscore > 5)
		{
			cout << "can you please rate seller "<<seller_name <<" out of 5 : " << endl;
			cin >> sellerscore;
		}
		sellerrate[seller_name].first += sellerscore;
		sellerrate[seller_name].second++;
		sellerrate_file();
	}
	else
	{
		return;
	}
}

void buyer::add_to_cart()
{
	//choose to add to cart
	fstream thisfile;
	thisfile.open(logineduser,  ios::app );
	map<int, int>::iterator it = items_added.begin();	
	map<int, pair<int, int>> ::iterator it2 = check.begin();
	map< pair<string, int>, productDataa>::iterator cartin = cart.begin();
	map< pair<string, int>, productDataa>::iterator prod = products.begin();
	for (; it != items_added.end(); it++)
	{
		for (it2 = check.begin(); it2 != check.end(); it2++)
		{
			//check id
			if (it->first == it2->first)
			{
				for (prod = products.begin(); prod != products.end(); prod++)
				{

					if (prod->first.second == it2->second.first)
					{
						cartcheck[{prod->first.first, { prod->first.second, prod->second.p_name }}] += it->second;

						//cart.insert({ {prod->first.first , { prod->first.second ,prod->second.p_name }  }  ,  { prod->second.price  ,  { prod->second.category , it->second }  } });
						cart[{prod->first.first,prod->first.second}] = productDataa(prod->second.p_name, prod->second.price, prod->second.category, prod->second.qty);
						//thisfile << prod->first.first << " " << prod->first.second << " " << prod->second.p_name << " " << prod->second.price << " " <<prod->second.category<< " " << it->second << endl;
						prod->second.qty = prod->second.qty - it->second;
						//takes id and quantity of the selected product
						remove.insert({ prod->first.second , cartcheck[{prod->first.first, { prod->first.second, prod->second.p_name }}] });
						break;
					}
				}
			}
			
		}
	}
	items_added.clear();
	check.clear();
	file_edit();
	cart_edit();
	cart_map();

}

void buyer::displaycart()
{
	//display all products from file(cart)
	if (cart.empty())
	{
		SetConsoleTextAttribute(h, 4);
		cout << "\t\t your cart is empty " << endl;
		SetConsoleTextAttribute(h, 7);
		
	}
	else
	{
		map< pair<string, int>, productDataa>  ::iterator disp = cart.begin();
		for (; disp != cart.end(); disp++)
		{
			
			cout <<"Seller Name :" << disp->first.first << " ID:" << disp->first.second << " Product Name : " << disp->second.p_name << " Price : " << disp->second.price << " Category : " << disp->second.category << " Quantity : " << disp->second.qty << endl;
		}
	}
}

void buyer::display_search()
{

	map< pair<string, int>, productDataa> :: iterator it = products.begin();
	string N;
	bool  flag = 0;
	SetConsoleTextAttribute(h, 2);
	cout << "enter product name : " << endl;
	SetConsoleTextAttribute(h, 7);
	cin >> N;
	int i = 1;
	for (; it != products.end(); it++)
	{
		if (N == it->second.p_name)
		{
			flag = 1;
			cout << "| " << i << ") " << " Name : " << it->second.p_name
				<< " | " << "Price: " << it->second.price
				<< " | " << "Quantity: " << it->second.qty
				<< " | " << "Category: " << it->second.category
				<< " | " << "Product Id : " << it->first.second;
			cout << endl;
			check.insert({ i,{ it->first.second,it->second.qty } });
			i++;
		}
	}

	if (!flag)
	{
		SetConsoleTextAttribute(h, 4);
		cout << "NO DATA FOUND" << endl;
		SetConsoleTextAttribute(h, 7);
	}
	else
	{
		int pn;
		int qu;
		SetConsoleTextAttribute(h, 2);
		cout << "Product Number : ";
		SetConsoleTextAttribute(h, 7);
		cin >> pn;
		cout << endl;
		SetConsoleTextAttribute(h, 2);
		cout << "Product Quantity : ";
		SetConsoleTextAttribute(h, 7);
		cin >> qu;
		cout << endl;
		//takes the number of product and quantity
		items_added.insert({ pn,qu });
		add_to_cart();
	}

}

void buyer::product_category()
{

	map< pair<string, int>, productDataa>::iterator it = products.begin();
	string C;
	bool  flag = 0;
	SetConsoleTextAttribute(h, 2);
	cout << "enter product category" << endl;
	SetConsoleTextAttribute(h, 7);
	cin >> C;
	int i = 1;
	for (; it != products.end(); it++)
	{
		if (C == it->second.category)
		{
			flag = 1;
			cout << "| " << i << ") " << " Name : " << it->second.p_name
				<< " | " << "Price: " << it->second.price
				<< " | " << "Quantity: " << it->second.qty
				<< " | " << "Category: " << it->second.category
				<< " | " << "Product Id : " << it->first.second;
			cout << endl;
			check.insert({ i,{ it->first.second,it->second.qty } });
			i++;
		}
	}

	if (!flag)
	{
		SetConsoleTextAttribute(h, 4);
		cout << "NO DATA FOUND" << endl;
		SetConsoleTextAttribute(h, 7);
	}
	else
	{
		int pn;
		int qu;
		SetConsoleTextAttribute(h, 2);
		cout << "Product Number : ";
		SetConsoleTextAttribute(h, 7);
		cin >> pn;
		cout << endl;
		SetConsoleTextAttribute(h, 2);
		cout << "Product Quantity : ";
		SetConsoleTextAttribute(h, 7);
		cin >> qu;
		cout << endl;
		//takes the number of product and quantity
		items_added.insert({ pn,qu });
		add_to_cart();
	}

}

void buyer::pay()
{
	system("cls");
	map< pair<string, int>, productDataa>  ::iterator it = cart.begin();
	double Amount = 0;
	double Total = 0;
	SetConsoleTextAttribute(h, 2);
	cout << "\n\t\t\t_______RECIEPT_______\n";
	SetConsoleTextAttribute(h, 7);
	for (; it != cart.end(); it++)
	{
		Amount = it->second.price * it->second.qty;
		Total += Amount;
		SetConsoleTextAttribute(h, 14);
		cout << " Seller Name : ";
		SetConsoleTextAttribute(h, 7);
		cout << it->first.first << " ";
		SetConsoleTextAttribute(h, 14);
		cout << " id : ";
		SetConsoleTextAttribute(h, 7);
		cout << it->first.second << " ";
		SetConsoleTextAttribute(h, 14);
		cout << "Product Name: ";
		SetConsoleTextAttribute(h, 7);
		cout << it->second.p_name << " ";
		SetConsoleTextAttribute(h, 14);
		cout << "price: ";
		SetConsoleTextAttribute(h, 7);
		cout << it->second.price<< " ";
		SetConsoleTextAttribute(h, 14);
		cout << "category: ";
		SetConsoleTextAttribute(h, 7);
		cout << it->second.category << " ";
		SetConsoleTextAttribute(h, 14);
		cout << "quantity: ";
		SetConsoleTextAttribute(h, 7);
		cout<< it->second.qty << endl;
	}
	SetConsoleTextAttribute(h, 2);
	cout << "\n\n\t________________________" << endl;
	cout << "\n Total Amount : ";
	SetConsoleTextAttribute(h, 7);
	cout<< Total<<endl;
	clear();
	cart.clear();
}

buyer::~buyer()
{}