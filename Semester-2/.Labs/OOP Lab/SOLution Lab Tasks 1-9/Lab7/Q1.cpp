#include <iostream>
#include <string>

class Block {
private:
    int length;
    int width;
    int height;
    const std::string material;
    std::string color;
    static int countOfBlocks;

public:
    // Default constructor
    Block() : material("Card") {
        length = 0;
        width = 0;
        height = 0;
        color = "";
        countOfBlocks++;
    }

    // Parameterized constructor
    Block(int l, int w, int h, std::string mat = "Card", std::string col = "") : material(mat) {
        length = l;
        width = w;
        height = h;
        color = col;
        countOfBlocks++;
    }

    // Destructor
    ~Block() {
        countOfBlocks--;
    }

    // Getter and setter methods
    int getLength() const {
        return length;
    }

    void setLength(int l) {
        length = l;
    }

    int getWidth() const {
        return width;
    }

    void setWidth(int w) {
        width = w;
    }

    int getHeight() const {
        return height;
    }

    void setHeight(int h) {
        height = h;
    }

    const std::string& getMaterial() const {
        return material;
    }

    const std::string& getColor() const {
        return color;
    }

    void setColor(const std::string& c) {
        color = c;
    }

    // Static member function for countOfBlocks
    static int getCountOfBlocks() {
        return countOfBlocks;
    }

    // Function to compute volume of the Block
    int getVolume() const {
        return length * width * height;
    }

    // Function to compute surface area of a block
    int getSurfaceArea() const {
        return 2 * (length * width + length * height + width * height);
    }
};

int Block::countOfBlocks = 0;

int main() {
    std::cout << "CountOfBlocks = " << Block::getCountOfBlocks() << std::endl;

    // Example 1
    std::cout << "Example 1:" << std::endl;
    Block* block1 = new Block(5, 4, 2);
    std::cout << "- Length = " << block1->getLength() << ", width = " << block1->getWidth() << ", height = " << block1->getHeight() << std::endl;
    std::cout << "- Volume = " << block1->getVolume() << std::endl;
    std::cout << "- Surface Area = " << block1->getSurfaceArea() << std::endl;

    // Example 2
    std::cout << "\nExample 2:" << std::endl;
    Block* block2 = new Block();
    block2->setLength(5);
    block2->setWidth(8);
    block2->setHeight(7);
    std::cout << "- Length = " << block2->getLength() << ", width = " << block2->getWidth() << ", height = " << block2->getHeight() << std::endl;
    std::cout << "- Volume = " << block2->getVolume() << std::endl;
    std::cout << "- Surface Area = " << block2->getSurfaceArea() << std::endl;

    std::cout << "\nCountOfBlocks = " << Block::getCountOfBlocks() << std::endl;

    // Deallocate memory and delete both objects
    delete block1;
    delete block2;

    std::cout << "CountOfBlocks = " << Block::getCountOfBlocks() << std::endl;

    return 0;
}
