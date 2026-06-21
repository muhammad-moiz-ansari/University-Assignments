package model;
import java.lang.String;
//import java.util

public class Customer {
	private String name, address;
	private String phone_no;
	private int account_no;
	private static int accountNo_counter = 1;
	private Account saving_acc;
	private Account checking_acc;
	
	public Customer(String name, String address, String phone_no)
	{
		this.name = name;
		this.address = address;
		this.phone_no = phone_no;
		this.account_no = accountNo_counter++;
		
		this.saving_acc = null;
		this.checking_acc = null;
	}
	
	///////////////
	//           //
	//  Getters  //
	//           //
	///////////////

	public String getName() {
	    return name;
	}

	public String getAddress() {
	    return address;
	}

	public String getPhone_no() {
	    return phone_no;
	}

	public int getAccount_no() {
	    return account_no;
	}

	public Account getSaving_acc() {
	    return saving_acc;
	}

	public Account getChecking_acc() {
	    return checking_acc;
	}
	

	///////////////
	//           //
	//  Setters  //
	//           //
	///////////////

	public void setName(String n) {
	    name = n;
	}

	public void setAddress(String a) {
	    address = a;
	}

	public void setPhone_no(String p) {
	    phone_no = p;
	}

	public void setAccount_no(int acc_no) {
	    account_no = acc_no;
	}

	public void setSaving_acc(Account s_acc) {
	    saving_acc = s_acc;
	}

	public void setChecking_acc(Account c_acc) {
	    checking_acc = c_acc;
	}

	
	///////////////////
	//               //
	//   Functions   //
	//               //
	///////////////////

	// Printing statement (All customer details and transaction history)
	public void printStatement(Account ac)
	{
		System.out.printf("Customer Details:\n"
						+ " - Name: %s\n"
						+ " - Phone No: %s\n"
						+ " - Address: %s\n"
						+ " - Account No: %d\n"
						+ "\nTransaction History:\n", name, phone_no, address, account_no);
		for(Transaction t : ac.getTransactions())
		{
			System.out.printf(" - Type: %s\n"
							+ " - Amount: Rs. %.2f\n"
							+ " - Date of Transaction: %s\n"
							+ " - Remaining Balance: Rs. %.2f\n\n", t.getType(), t.getAmount(), t.getDate(), t.getNewBalance());
		}
	}
	
}
