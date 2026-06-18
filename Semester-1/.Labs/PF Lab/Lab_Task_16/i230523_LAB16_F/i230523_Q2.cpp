#include <iostream>
#include <fstream>
using namespace std;

int main()
{
 	cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 	cout<<"Roll No : 23i-0523"<<endl<<endl;
	

    string text = "The rose is red.\nA girl is playing there.\nThere is a playground.\nAn aeroplane is in the sky.\nNumbers are not allowed in the password.";

    fstream file1, file2;
    
    file1.open("story.txt");
    if(!file1)
    {
        cout << "File not created.\n";
    }
    else
    {
        file1 << text;    //Inputting
        file1.close();
    }
    
    //Reading:
    file1.open("story.txt");
    file2.open("output.txt");
    if(!file1 && !file2)
    {
        cout << "File not created.\n";
    }
    else
    {
        char ch;
        cout << "File created successfully and copied.\n";
        while(file1.get(ch))
        {
            file2 << ch;
        }
        
    }

    return 0;
}