package service;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import model.*;


public class BankSystem {
	//Bank Owner Details
	private String ownerName, ownerEmail;
	private String ownerPhone_no;
	
	private List<Customer> customers = new ArrayList<>();
	private Customer activeCustomer;
	private Account activeAccount;
	private float interestRate;
	
	private Scanner sc;
	
	public BankSystem()
	{
		sc = new Scanner(System.in);
		
		System.out.print("Enter bank owner name: ");
		ownerName = sc.nextLine();
		System.out.print("Enter bank owner email: ");
		ownerEmail = sc.next();
        while(!validateEmail(ownerEmail))
        {
            System.out.print("Invalid format! enter bank owner email again: ");
            ownerEmail = sc.next();
        }
		System.out.print("Enter bank owner phone no (Format: 0xxxxxxxxxx): ");
		ownerPhone_no = sc.next();
        while(!validatePhoneNo(ownerPhone_no))
        {
            System.out.print("Invalid format! enter bank owner phone no again(Format: 0xxxxxxxxxx): ");
            ownerPhone_no = sc.next();
        }
        ownerPhone_no = ownerPhone_no.substring(0, 4) + "-" + ownerPhone_no.substring(4);
		
		activeCustomer = null;
		activeAccount = null;
		interestRate = 5.0f;	// Default interest rate
	}
	
	////////////////////////
	//                    //
	//  Getters & Setters //
	//                    //
	////////////////////////
	
	public String getOwnerName() {
		return ownerName;
	}
	
	
	public void setOwnerName(String ownerName) {
		this.ownerName = ownerName;
	}
	
	
	public String getOwnerEmail() {
		return ownerEmail;
	}
	
	
	public void setOwnerEmail(String ownerEmail) {
		this.ownerEmail = ownerEmail;
	}
	
	
	public String getOwnerPhone_no() {
		return ownerPhone_no;
	}
	
	
	public void setOwnerPhone_no(String ownerPhone_no) {
		this.ownerPhone_no = ownerPhone_no;
	}
	
	
	public List<Customer> getCustomers() {
		return customers;
	}
	
	
	public void setCustomers(List<Customer> customers) {
		this.customers = customers;
	}
	
	
	public Customer getActiveCustomer() {
		return activeCustomer;
	}
	
	
	public void setActiveCustomer(Customer activeCustomer) {
		this.activeCustomer = activeCustomer;
	}
	
	
	public float getInterestRate() {
		return interestRate;
	}
	
	
	public void setInterestRate(float interestRate) {
		this.interestRate = interestRate;
	}
	
	public Account getActiveAccount() {
		return activeAccount;
	}


	public void setActiveAccount(Account activeAccount) {
		this.activeAccount = activeAccount;
	}


	///////////////////
	//               //
	//   Functions   //
	//               //
	///////////////////

    // Validate phone number
    private boolean validatePhoneNo(String phoneNo)
    {
        if (phoneNo.charAt(0) != '0')
            return false;
        return phoneNo.matches("^[0-9]{11}$");
    }

    // Validate email
    private boolean validateEmail(String email)
    {
        String regex = "^[A-Za-z0-9_.-]+@[A-Za-z.]+\\.[A-Za-z]{2,20}$";
        return email.matches(regex);
    }

    // Choosing account type for menus
	public int chooseAccountType()
	{
		int choose = 0;
		System.out.print("Choose account type:\n"
						 + "1. Checking account\n"
						 + "2. Saving account\n"
						 + "Choose: ");
		while(true)
		{
			choose = sc.nextInt();
			if(choose == 1 || choose == 2)
				break;
			else
				System.out.print("Invalid input!...Choose again(1 or 2): ");
		}
		return choose;
	}
	
	//Find a customer by his account number and return
	public Customer findCustomer(int acc_no)
	{
		if(customers.isEmpty())
		{
			System.out.println("No customers found!");
			return null;
		}
		Customer cus = null;
		for (Customer c : customers) {
		    if (c.getAccount_no() == acc_no) {
		        cus = c;
		        break;
		    }
		}
		return cus;
	}
	
	//Adds customer to list
	public void addCustomer()
	{
		String name;
		String address;
		String phone_no;
		sc.nextLine();
		System.out.print("Enter customer name: ");
		name = sc.nextLine();
		System.out.print("Enter address: ");
		address = sc.nextLine();
		System.out.print("Enter phone no (Format: 0xxxxxxxxxx): ");
		phone_no = sc.next();
        while(!validatePhoneNo(phone_no))
        {
            System.out.print("Invalid format! enter phone no again(Format: 0xxxxxxxxxx): ");
            phone_no = sc.next();
        }
        phone_no = phone_no.substring(0, 4) + "-" + phone_no.substring(4);

        customers.add(new Customer(name, address, phone_no));
		System.out.println("The account number is " + customers.get(customers.size() - 1).getAccount_no());
	}
	
	// Makes account for customer
	public void openAccount()
	{
		int acc_no;
		System.out.print("Enter account number: ");
		acc_no = sc.nextInt();
				
		//Find customer with account id
		Customer cus = findCustomer(acc_no);
		
		if(cus != null)
		{
			//Choose account type
			int choose = chooseAccountType();
			
			//Checking account
			if(choose == 1 && cus.getChecking_acc() != null)
			{
				System.out.println("Checking account already exists!");
			}
			else if(choose == 1)
			{
				float balance;
				System.out.print("Enter initial balance: ");
				balance = sc.nextFloat();
				cus.setChecking_acc(new CheckingAccount(acc_no, balance));
			}
			
			//Saving account
			if(choose == 2 && cus.getSaving_acc() != null)
			{
				System.out.println("Saving account already exists!");
			}
			else if(choose == 2)
			{
				float balance;
				System.out.print("Enter initial balance: ");
				balance = sc.nextFloat();
				cus.setSaving_acc(new SavingAccount(acc_no, balance, interestRate));
			}
		}
		else
		{
			System.out.println("Customer with account number " + acc_no + " not found!");
		}
	}
	
	//Deletes account
	public void closeAccount()
	{
		int acc_no;
		System.out.print("Enter account number: ");
		acc_no = sc.nextInt();
				
		//Find customer with account id
		Customer cus = findCustomer(acc_no);
		
		if(cus != null)
		{
			//Choose account type
			int choose = chooseAccountType();
			
			//Checking account
			if(choose == 1 && cus.getChecking_acc() == null)
			{
				System.out.println("Checking account does not exists!");
			}
			else if(choose == 1)
			{
				cus.setChecking_acc(null);
			}
			
			//Saving account
			if(choose == 2 && cus.getSaving_acc() == null)
			{
				System.out.println("Saving account does not exists!");
			}
			else if(choose == 2)
			{
				cus.setSaving_acc(null);
			}
		}
		else
		{
			System.out.println("Customer with account number " + acc_no + " not found!");
		}
	}
	
	//Login to an account
	public boolean login()
	{
		int acc_no;
		System.out.print("Enter account number: ");
		acc_no = sc.nextInt();
				
		//Find customer with account id
		Customer cus = findCustomer(acc_no);
		
		if(cus != null)
		{
			//Choose account type
			int choose = chooseAccountType();
			
			//Checking account
			if(choose == 1 && cus.getChecking_acc() == null)
			{
				System.out.println("Checking account does not exists!");
				return false;
			}
			else if(choose == 1)
			{
				setActiveAccount(cus.getChecking_acc());
			}
			
			//Saving account
			if(choose == 2 && cus.getSaving_acc() == null)
			{
				System.out.println("Saving account does not exists!");
				return false;
			}
			else if(choose == 2)
			{
				setActiveAccount(cus.getSaving_acc());
			}
			activeCustomer = cus;
			return true;
		}
		else
		{
			System.out.println("Customer with account number " + acc_no + " not found!");
			return false;
		}
	}
	
	//Logout
	public void logout()
	{
		activeAccount = null;
		activeCustomer = null;
		
		System.out.println("Logging out...");
	}
	
	//Sets interest rate
	public void updateInterestRate()
	{
		System.out.print("Enter new interest rate: ");
		while(true)
		{
			interestRate = sc.nextFloat();
			if(interestRate < 0)
				System.out.println("Please enter positive number: ");
			else if(interestRate >= 100)
				System.out.println("Please enter value less than 100: ");
			else
				break;
		}
		Account ac;
		for(Customer c : customers)
		{
			ac = c.getSaving_acc();
			if(ac != null)
			{
				((SavingAccount)ac).setInterestRate(interestRate);
			}
		}
		System.out.println("Interest rate updated!");
	}
	
	//Displays all account details
	public void displayAccountDetails()
	{
		System.out.printf("Bank Owner Details:\n"
				+ " - Name: %s\n"
				+ " - Phone No: %s\n"
				+ " - Email: %s\n\n"
				+ "Bank Account Details:\n", ownerName, ownerPhone_no, ownerEmail);
		Account ac;
		for(Customer c : customers)
		{
			ac = c.getChecking_acc();
			if(ac != null)
			{
				System.out.printf("Account No: %d | Balance: Rs. %.2f | Date Created: %s | Withdrawal Limit: Rs. %.2f%n",
		                  ac.getAccount_no(),
		                  ac.getBalance(),
		                  new SimpleDateFormat("dd-MM-yyyy").format(ac.getDate_created()),
		                  ac.getWithdrawal_limit());
			}
			ac = c.getSaving_acc();
			if(ac != null)
			{
				System.out.printf("Account No: %d | Balance: Rs. %.2f | Date Created: %s | Withdrawal Limit: Rs. %.2f | Interest Rate: %.2f%%n",
						  ac.getAccount_no(),
		                  ac.getBalance(),
		                  new SimpleDateFormat("dd-MM-yyyy").format(ac.getDate_created()),
		                  ac.getWithdrawal_limit(),
						  interestRate);
			}
		}
	}
	
	//Displays all account deductions
	public void displayDeductionDetails()
	{
		Account ac;
		for(Customer c : customers)
		{
			ac = c.getChecking_acc();
			if(ac != null)
			{
				ac.displayAllDeductions();
			}
			ac = c.getSaving_acc();
			if(ac != null)
			{
				ac.displayAllDeductions();
			}
		}
	}
}
