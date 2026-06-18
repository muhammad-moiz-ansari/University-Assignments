#include <iostream>

class Matrix {
private:
    int rows;
    int columns;
    int** arr;

public:
    // Default constructor
    Matrix() : rows(0), columns(0), arr(nullptr) {}

    // Parameterized constructor
    Matrix(int r, int c, int** p) : rows(r), columns(c) {
        arr = new int* [rows];
        for (int i = 0; i < rows; ++i) {
            arr[i] = new int[columns];
            for (int j = 0; j < columns; ++j) {
                arr[i][j] = p[i][j];
            }
        }
    }

    // Copy constructor
    Matrix(const Matrix& copy) {
        rows = copy.rows;
        columns = copy.columns;
        arr = new int* [rows];
        for (int i = 0; i < rows; ++i) {
            arr[i] = new int[columns];
            for (int j = 0; j < columns; ++j) {
                arr[i][j] = copy.arr[i][j];
            }
        }
    }

    // Destructor
    ~Matrix() {
        if (arr != nullptr) {
            for (int i = 0; i < rows; ++i) {
                delete[] arr[i];
            }
            delete[] arr;
        }
    }

    // Setter and getter methods
    void setRows(int r) {
        rows = r;
    }

    int getRows() const {
        return rows;
    }

    void setColumns(int c) {
        columns = c;
    }

    int getColumns() const {
        return columns;
    }

    int** getArr() const {
        return arr;
    }

    // Function for scalar multiplication
    void multiplyMatrix(int scalar) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                arr[i][j] *= scalar;
            }
        }
    }

    // Function for scalar addition
    void addMatrix(int scalar) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                arr[i][j] += scalar;
            }
        }
    }

    // Function to display the matrix
    void display() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                std::cout << arr[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    int row = 3;
    int column = 3;
    int** p = new int* [row];
    for (int i = 0; i < row; ++i) {
        p[i] = new int[column];
    }

    // Initialize the matrix
    p[0][0] = 1; p[0][1] = 5; p[0][2] = 7;
    p[1][0] = 4; p[1][1] = 8; p[1][2] = 3;
    p[2][0] = 6; p[2][1] = 4; p[2][2] = 1;

    // Use copy constructor to assign values
    Matrix matrix1(row, column, p);
    Matrix matrix2(matrix1);

    std::cout << "Resultant Matrix after calling function multiplyMatrix(4):" << std::endl;
    matrix1.multiplyMatrix(4);
    matrix1.display();

    std::cout << "\nResultant Matrix after calling function addMatrix(3):" << std::endl;
    matrix2.addMatrix(3);
    matrix2.display();

    // Deallocate memory
    for (int i = 0; i < row; ++i) {
        delete[] p[i];
    }
    delete[] p;

    return 0;
}
