/*
Name : Moiz ansari
Roll no : 23i=0523
*/

#include <iostream>

using namespace std;

int main()
{
	int ch=1, bill=0, payment, cash, cash_c=0, change;
	cout<<"Vending Machine Menu: \n";
	cout<<"1. Snack A - $1.50\n";
	cout<<"2. Snack B - $2.00\n";
	cout<<"3. Snack C - $1.00\n";
	cout<<"4. Snack D - $1.25\n\n";
	
	while(ch!=-1)
	cout<<"Enter product choice(Select the product choice untill you press -1): ";
	cin>>ch;
	
	switch(ch)
	{
		case 1:
			bill+=1.50;
			break;
		
		case 2:
			bill+=2.00;
			break;
		
		case 3:
			bill+=1.00;
			break;
		
		case 4:
			bill+=1.25;
			break;
			
		default:
			cout<<"Invalid choice.\nChoose only 1,2,3 or 4\n"; 
	}
	
	cout<<"Payment Methods: \n";
	cout<<"1. Cash\n";
	cout<<"2. Card\n\n";
	
	cout<<"Choose payment method: \n";
	cin>>payment;
	
	switch(payment)
	{
		case 1:
			cout<<"Enter the Amount in dollars: ";
			cin>>cash;
			
			if(cash>bill)
			  cash_c=1;
			if(cash=bill)
			  cash_c=0;
			  
			switch(cash)
			{
				case 1:
					change=cash-bill;
					cout<<"Change= "<<change<<endl;
					break;
				case 0:
					cout<<"Change= 0.00\n";
					break;
				default:
					cout<<"Insufficient balance.\n";
			}
			break;
			
			case 2:
				cout<<"Card Payment Successful.\n";
				break;
				
			default:
				cout<<"Invalid choice.\nEnter only 1 or 2\n";
	}
	
	
	return 0;
}











