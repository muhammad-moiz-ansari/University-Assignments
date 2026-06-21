#include <iostream>
using namespace std;

const int rows = 3, cols = 4;

template <typename T>
T* spiralOrder(const T(&matrix)[rows][cols], int& size)
{
	size = rows * cols;

    T** ind = new T*[rows];
    for (int i = 0; i < rows; ++i)
        ind[i] = new T[cols];

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            ind[i][j] = 1;

    //Array new:
    T* arr = new T[rows * cols];

    bool up = 0, down = 0, left = 0, right = 1,
        ru = 0, rd = 0, cu = 0, cd = 0;
    int i = 0, j = 0, k = 0;

    for (; k < rows * cols; )
    {
        if (up)
        {
            ru = 0, rd = 1, cu = 0, cd = 0;
        }
        if (down)
        {
            ru = 1, rd = 0, cu = 0, cd = 0;
        }
        if (left)
        {
            ru = 0, rd = 0, cu = 0, cd = 1;
        }
        if (right)
        {
            ru = 0, rd = 0, cu = 1, cd = 0;
        }

        if (cu == 1)
        {
            if (ind[i][j] > 0)
            {
                arr[k] = matrix[i][j];
                k++;
                ind[i][j++] = -1;

                if (j >= cols)
                {
                    --j;
                    ++i;
                    down = 1;
                    right = 0;
                }
            }
            else
            {
                --j;
                ++i;
                down = 1;
                right = 0;
            }
        }

        else if (ru == 1)
        {
            if (ind[i][j] > 0)
            {
                arr[k] = matrix[i][j];
                k++;
                ind[i++][j] = -1;

                if (i >= rows)
                {
                    --i;
                    --j;
                    left = 1;
                    down = 0;
                }
            }
            else
            {
                --i;
                --j;
                left = 1;
                down = 0;
            }
        }
        else if (cd == 1)
        {
            if (ind[i][j] > 0)
            {
                arr[k] = matrix[i][j];
                k++;
                ind[i][j--] = -1;

                if (j < 0)
                {
                    ++j;
                    --i;
                    up = 1;
                    left = 0;
                }
            }
            else
            {
                ++j;
                --i;
                up = 1;
                left = 0;
            }
        }
        else if (rd == 1)
        {
            if (ind[i][j] > 0)
            {
                arr[k] = matrix[i][j];
                k++;
                ind[i--][j] = -1;

                if (i < 0)
                {
                    ++i;
                    ++j;
                    up = 0;
                    right = 1;
                }
            }
            else
            {
                ++i;
                ++j;
                up = 0;
                right = 1;
            }
        }

    }

    return arr;

}

int main()
{
    const int rows = 3;
    const int cols = 4;
    int matrix[rows][cols] = { {1, 2, 3, 4}, {5, 6 , 7, 8}, {9, 10, 11, 12} };
    int size;
    int* result = spiralOrder(matrix, size);

    for (int i = 0; i < rows * cols; ++i)
        cout << result[i]<<"  ";

	return 0;
}