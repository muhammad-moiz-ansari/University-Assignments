#include <iostream>
#include <fstream>
using namespace std;

int main()
{
 	cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 	cout<<"Roll No : 23i-0523"<<endl<<endl;


    string text = "Time is a great teacher but unfortunately it kills all its pupils. Berlioz";

    fstream file;
    
    file.open("OUT.txt");
    if(!file)
    {
        cout<<"File not created.\n";
    }
    else
    {
        file<<text;
        file.close();
    }
    
    file.open("OUT.txt");
    if(!file)
    {
        cout<<"File not created.\n";
    }
    else
    {
        char ch;
        int count = 0;
        cout<<"File created successfully.\n";
        while(1)
        {
            file >> ch;
            if(file.eof())
                break;
            if((ch>='a' && ch<='z') || (ch>='A' && ch<='Z') || ch=='.')
                ++count;
        }
        cout<<"Count = "<<count<<endl;
    }

    return 0;
}