/* Name: Muhammad Moiz Ansari
 * Roll No: 23i-0523
 * Section: F
 */
package Main;
import java.util.Scanner;

import service.BankSystem;
import model.*;

public class Main 
{
	protected static Scanner sc = new Scanner(System.in);
	
	Main()
	{
		sc = new Scanner(System.in);
	}
	
	public static void main(String[] args) 
	{
		BankSystem hbl = new BankSystem();
		
		int menuChoice = 0, actionChoice;
		while(menuChoice >= 0)
		{
			if(menuChoice == 40)	// If logged in
			{
				actionChoice = accountMenu();
				menuChoice = handleAccountMenu(actionChoice, hbl);
			}
			else
			{
				menuChoice = mainMenu();
				menuChoice = handleMainMenu(menuChoice, hbl);
			}
			
		}
		System.out.println("Exiting program...");
	}

	public static int mainMenu()
	{
		int choice = 0;
		System.out.print("\n------ Main Menu ------\n"
						 + "1. Add customer\n"
						 + "2. Open account\n"
						 + "3. Close account\n"
						 + "4. Login \n"
						 + "5. Set interest rate\n"
						 + "6. Display all accounts details\n"
						 + "7. Display all accounts deductions\n"
						 + "8. Exit\n"
						 + "Choose: ");
		while(true)
		{
			choice = sc.nextInt();
			sc.nextLine();
			if(choice >= 1 && choice <= 8)
				break;
			else
				System.out.print("Invalid input!...Choose again(1-8): ");
		}
		return choice;
	}
	
	public static int handleMainMenu(int choice, BankSystem bank)
	{
		switch(choice)
		{
		case 1:
			bank.addCustomer();
			break;
		case 2:
			bank.openAccount();
			break;
		case 3:
			bank.closeAccount();
			break;
		case 4:
			if(bank.login())
			{
				System.out.println("Account logged in successfully!");
				return 40;
			}
			break;
		case 5:
			bank.updateInterestRate();
			break;
		case 6:
			bank.displayAccountDetails();
			break;
		case 7:
			bank.displayDeductionDetails();
			break;
		default:
			return -1;
		}
		return choice;
	}
	
	public static int accountMenu()
	{
		int choice = 0;
		System.out.print("\n------ Account Menu ------\n"
						 + "1. Make deposit\n"
						 + "2. Make withdrawal\n"
						 + "3. Check balance\n"
						 + "4. Print statement\n"
						 + "5. Transfer money\n"
						 + "6. Calculate zakat\n"
						 + "7. Deduct zakat\n"
						 + "8. Logout\n"
						 + "Choose: ");
		while(true)
		{
			choice = sc.nextInt();
			if(choice >= 1 && choice <= 8)
				break;
			else
				System.out.print("Invalid input!...Choose again(1-8): ");
		}
		return choice;
	}
	
	public static int handleAccountMenu(int choice, BankSystem bank)
	{
		float amount;
		switch(choice)
		{
		case 1:
			System.out.print("Enter the amount to deposit: ");
			amount = sc.nextFloat();
			bank.getActiveAccount().makeDeposit(amount);
			break;
		case 2:
			System.out.print("Enter the amount to withdraw: ");
			amount = sc.nextFloat();
			bank.getActiveAccount().makeWithdrawal(amount);
			break;
		case 3:
			bank.getActiveAccount().checkBalance(bank.getActiveCustomer(), bank.getActiveAccount());
			break;
		case 4:
			bank.getActiveCustomer().printStatement(bank.getActiveAccount());
			break;
		case 5:
			int acc_no, accChoice = 0;
			Customer cus = null;
			Account acc = null;
			
			System.out.print("Enter the amount to transfer: ");
			amount = sc.nextFloat();
			System.out.print("Enter the account number of target account: ");
			acc_no = sc.nextInt();
			
			cus = bank.findCustomer(acc_no);
			if(cus != null)
			{
				accChoice = bank.chooseAccountType();
				if(accChoice == 1)
					acc = cus.getChecking_acc();
				else
					acc = cus.getSaving_acc();

                if(acc == bank.getActiveAccount())
                    System.out.println("Can not transfer to your own account!");
                else
				    bank.getActiveAccount().transferAmount(acc, amount);
			}
			else
			{
				System.out.println("Customer account id does not exists!");
			}
			
			break;
		case 6:
			if(bank.getActiveAccount() instanceof SavingAccount)
			{
				System.out.println("Zakat of this account is Rs. " + ((SavingAccount)bank.getActiveAccount()).calculateZakat());
			}
			else
			{
				System.out.println("Zakat can be calculated only for Saving accounts!");
			}
			break;
		case 7:
			if(bank.getActiveAccount() instanceof SavingAccount)
			{
				((SavingAccount)bank.getActiveAccount()).deductZakat();
			}
			else
			{
				System.out.println("Zakat can be calculated only for Saving accounts!");
			}
			break;
		default:
			bank.logout();
			return 0;
		}
		return 40;
	}
}