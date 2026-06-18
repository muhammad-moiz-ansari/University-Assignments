#include <iostream>
#include <string>

class Item {
private:
    std::string itemName;
    int quantity;
    int pricePerUnit;

public:
    // Default Constructor
    Item() : itemName(""), quantity(0), pricePerUnit(0) {}

    // Parameterized Constructor
    Item(std::string name, int qty, int price) : itemName(name), quantity(qty), pricePerUnit(price) {}

    // Overload prefix ++ operator
    Item& operator++() {
        ++quantity;
        return *this;
    }

    // Overload prefix -- operator
    Item& operator--() {
        --quantity;
        return *this;
    }

    // Overload postfix ++ operator
    Item operator++(int) {
        Item temp = *this;
        quantity += 5;
        return temp;
    }

    // Overload postfix -- operator
    Item operator--(int) {
        Item temp = *this;
        quantity -= 5;
        return temp;
    }

    // Overload += operator
    Item& operator+=(int n) {
        quantity += n;
        return *this;
    }

    // Overload -= operator
    Item& operator-=(int n) {
        quantity -= n;
        return *this;
    }

    // Overload + operator
    Item operator+(const Item& other) const {
        if (itemName == other.itemName) {
            Item result = *this;
            result.quantity += other.quantity;
            return result;
        }
        else {
            return *this;
        }
    }

    // Overload ~ operator
    int operator~() const {
        return quantity * pricePerUnit;
    }

    // Overload ! operator
    friend std::ostream& operator<<(std::ostream& os, const Item& item) {
        os << "Item Name: " << item.itemName << ", Quantity: " << item.quantity << ", Price Per Unit: " << item.pricePerUnit;
        return os;
    }
};

int main() {
    Item item1("Item1", 10, 5);
    Item item2("Item2", 8, 3);

    std::cout << "Initial item1: " << item1 << std::endl;
    std::cout << "Initial item2: " << item2 << std::endl;

    ++item1;
    std::cout << "After prefix increment item1: " << item1 << std::endl;

    --item2;
    std::cout << "After prefix decrement item2: " << item2 << std::endl;

    item1++;
    std::cout << "After postfix increment item1: " << item1 << std::endl;

    item2--;
    std::cout << "After postfix decrement item2: " << item2 << std::endl;

    item1 += 3;
    std::cout << "After += operator item1: " << item1 << std::endl;

    item2 -= 2;
    std::cout << "After -= operator item2: " << item2 << std::endl;

    Item item3 = item1 + item2;
    std::cout << "After + operator item3 (with same item name): " << item3 << std::endl;

    int totalPrice = ~item1;
    std::cout << "Total price of item1: " << totalPrice << std::endl;

    std::cout << "Display item2 using ! operator: " << !item2 << std::endl;

    return 0;
}
