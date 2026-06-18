#pragma once
#include <iostream>
using namespace std;

static int item_no = 1;
int maxitems = 10;

struct Item
{
	string name;
	int quantity;
	float price;
};

class ShoppingList
{
	Item* item = new Item[maxitems];
};