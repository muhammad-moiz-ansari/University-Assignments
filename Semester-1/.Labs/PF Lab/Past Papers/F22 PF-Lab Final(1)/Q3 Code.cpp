#include <iostream>
using namespace std;
void sorter(int *arr, int size);
void swap(int *bigger, int *smaller);
int *dupElement(int *arr, int size);
int main()
{
  const int size = 6;
  int num_arr[size]={}, *num_ptr;
  cout<<"This program will input an array of integers and display the duplicated elements";
  cout<<"\nEnter the elements of the array:\n";
  for(int i=0; i<size; ++i)  //loop for input
  {
    cin>>num_arr[i];
  }
  cout<<"\nThe original array is: ";
  for(int i=0; i<size; ++i)  //loop for display
  {
    cout<<num_arr[i]<<" ";
  }
  cout<<"\nThe sorted array is:\n";
  sorter(num_arr, size);
  for(int i=0; i<size; ++i)
  {
    cout<<num_arr[i]<<" ";
  }
  cout<<"\nThe duplicated elements are:\n";
  num_ptr = dupElement( num_arr, size);
  for(int i=1; i<=*num_ptr; ++i)
  {
    cout<<*(num_ptr + i)<<" ";
  }
  delete [] num_ptr;
  num_ptr = NULL;
  return 0;
}
int *dupElement(int *arr, int size)
{
  sorter(arr, size);
  int *dup_ptr = new int[ size/2 + 1 ];
  bool present;
  int counter = 0;
  for(int i=0; i<size; ++i)
  {
    present = false;
    for(int j=(i+1); j<size; ++j)
    {
      if( *(arr+i) == *(arr+j) )
      {
        for(int k=1; k < (size/2 + 1); ++k)
        {
          if( *(arr+i) == *(dup_ptr+k) )
          {
            present = true;
          }
        }
        if(!present)
        {
          ++counter;
          *(dup_ptr) = counter;
          *(dup_ptr + counter) = *(arr+i);
        }
      }
    }
  }
  return dup_ptr;
}
void sorter(int *arr, int size)
{
  int minIndex, minElement;
  for(int i=0; i<(size-1); ++i)
  {
    minIndex = i, minElement = *(arr+i);
    for(int j=(i+1); j<size; ++j)
    {
      if( *(arr+j) < minElement)
      {
        minIndex = j;
        minElement = *(arr+j);
      }
    }
    swap( (arr+i), (arr+minIndex) ); 
  } 
}
void swap(int *bigger, int *smaller)
{
  int temp = *bigger;
  *bigger = *smaller;
  *smaller = temp;
}