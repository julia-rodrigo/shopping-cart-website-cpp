#include <iostream>
#include <vector>
#include <string>
#include "Item.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <windows.data.json.h>
#include <fstream>
#include <sstream>


using namespace std;

#pragma once
class ShoppingCart
{
	private: 
		vector<Item> items;

	public:
		void addItem(Item item) {
			items.push_back(item);
		}

		void removeItem(Item item) {
			items.erase(remove(items.begin(), items.end(), item), items.end());
		}

		int getNumItems() { // possible loss of data
			return items.size();
		}

		double getTotalCost() {
			double totalCost = 0;
			for (auto& item : items) {
				totalCost += item.getPrice();
			}
			return totalCost;
		}

		nlohmann::json serialize() {
			nlohmann::json json_items;
			for (auto& item : items) {
				json_items.push_back({
					{"name", item.getName()},
					{"price", item.getPrice()}
				});
			}

			nlohmann::json json_cart;
			json_cart["items"] = json_items;
			return json_cart;
		}

		void save() {
			ofstream file("cart.json");
			file << this->serialize().dump(4);
			file.close();
		}



		string getCartContentsAsHTMLTable() {
			string table = "<table style='border: 1px solid black; border-collapse: collapse; width: 100%'>"
				"<tr style='border: 1px solid black;'>"
				"<th style='border: 1px solid black; padding: 5px;'>Name</th>"
				"<th style='border: 1px solid black; padding: 5px;'>Price</th>"
				"</tr>\n";
			for (auto& item : items) {
				table +=
					"<tr style='border: 1px solid black;'>"
					"<td style='border: 1px solid black; padding: 5px;'>" + item.getName() + "</td>"
					"<td style='border: 1px solid black; padding: 5px;'>" + to_string(item.getPrice()) + "</td>"
					"</tr>";
			}
			table += "</table>";
			return table;
		}

		void readFromJSON(string jsonFile) {
			ifstream jsonStream(jsonFile);
			string jsonString(
				(std::istreambuf_iterator<char>(jsonStream)),
				std::istreambuf_iterator<char>()
			);

			// parse json
			nlohmann::json json;

			try {
				json = nlohmann::json::parse(jsonString);
			}
			catch (nlohmann::json::parse_error& e) {
				return;
			}

			///iterate
			for (auto& item : json["items"]) {
				// Get name and proice of item
				string name = item["name"];
				double price = item["price"];

				// cREate item and add to cart
				Item item_to_add(name, price);
				this->addItem(item_to_add);
			}
		}
};

