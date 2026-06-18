#include <iostream>
using namespace std;
int numPathsHome(int street, int avenue);
int main()
{
  const int street = 5;
  const int avenue = 5;
  int arr[street][avenue] = {};
  arr[3][2] = {1};
  cout<<"This program will output the number of paths that can be taken by Watson the robot";
  cout<<"\nThe starting position of Watson the robot in the rectangular grid is specified by the number 1\n";
  for(int i=0; i<street; ++i)
  {
    for(int j=0; j<avenue; ++j)
    {
      cout<<arr[i][j]<<" ";
    }
    cout<<endl;
  }
  cout<<"The number of possible paths for Watson the robot to take to origin are: ";
  cout<<numPathsHome(3, 2);

  return 0;
}
int numPathsHome(int street, int avenue)
{
  if( street == 4 && avenue == 0)
  {
    return 1;
  }
  else if( street == 4)
  {
    return numPathsHome(street, avenue-1);
  }
  else if( avenue == 0)
  {
    return numPathsHome( street+1, avenue);
  }
  else if( street<4 && avenue>0)
  {
    return numPathsHome(street, avenue-1) + numPathsHome(street+1, avenue);
  }
  else if( street<4 )
  {
    return numPathsHome(street+1, avenue);
  }
  else if( avenue>0 )
  {
    return numPathsHome(street, avenue-1);
  }
  return 0;
}