#include <iostream>
using namespace std;

#pragma once
class Item
{
	private:
		string name;
		double price;

	public:
		Item(string name, double price) : name(name), price(price) {}
		string getName() { return name; }
		double getPrice() { return price;  }

		bool operator == (const Item& other) const {
			return name == other.name && price == other.price;
		}
};

