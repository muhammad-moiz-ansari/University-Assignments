#include <iostream>
using namespace std;
void fillMatrix(int arr[][6], int row, int col);
void display(int arr[][6], int row, int col);
void display(int arr[][2], int row, int col);
void filter(int image[][6], int r1, int c1, int filter[][2], int r2, int c2);
bool checker(int image, int filter);
int main()
{
  const int img_row = 6;
  const int img_col = 6;
  const int filter_row = 2;
  const int filter_col = 2;
  int img_matrix[img_row][img_col] = {};
  int filter_matrix[filter_row][filter_col] = {1,1,1,1}; 
  cout<<"This program is for image filter";
  fillMatrix(img_matrix, img_row, img_col);    //func to fill the image matrix with the given values
  cout<<"\nThe original image matrix is\n";
  display(img_matrix, img_row, img_col);       //func to display the matrix 
  cout<<"The filter matrix as given is\n";
  display(filter_matrix, filter_row, filter_col);
  filter(img_matrix, img_row, img_col, filter_matrix, filter_row, filter_col);
  cout<<"\nThe image matrix after filter is\n";
  display(img_matrix, img_row, img_col);

  return 0;    
}
void fillMatrix(int arr[][6], int row, int col)
{
  for(int i=0; i<col; ++i)
  {
    for(int j=0; j<row; ++j)
    {
      if( i==2 || i==5 )
      {
        arr[j][i] = 0;
      }
      else 
      {
        arr[j][i] = 1;
      }
    }
  }
}
void display(int arr[][6], int row, int col)
{
  for(int i=0; i<row; ++i)
  {
    for(int j=0; j<col; ++j)
    {
      cout<<arr[i][j]<<" ";
    }
    cout<<endl;
  }
}
void display(int arr[][2], int row, int col)
{
  for(int i=0; i<row; ++i)
  {
    for(int j=0; j<col; ++j)
    {
      cout<<arr[i][j]<<" ";
    }
    cout<<endl;
  }
}
void filter(int image[][6], int r1, int c1, int filter[][2], int r2, int c2)
{
  bool element_match;
  for(int i=0; i< (r1); ++i)
  {
    element_match = true;
    for(int j=0; j< (c1); ++j)
    {
      for(int k=0; k<r2; ++k)
      {
        for(int x=0; x<c2; ++x)
        {
          element_match = checker(image[i+k][j+x], filter[k][x]);       
          if(!element_match)
            break;
        }
        if(!element_match)
          break;
      }
      if(element_match)
      {
        image[i][j] = 1;
      }
      else
      {
        image[i][j] = 0;
      }
    }
  }
}
bool checker(int image, int filter)
{
  if( image == filter)
    return true;
  else
    return false;
}