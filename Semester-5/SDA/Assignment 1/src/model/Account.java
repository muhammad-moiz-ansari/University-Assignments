package model;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public abstract class Account {
	private int account_no;
	private float balance;
	private Date date_created;
	private float withdrawal_limit;
	private List<Transaction> transactions = new ArrayList<>();
	
	public Account(int acc_no, float bal)
	{
		account_no = acc_no;
		balance = bal;
		date_created = new Date();
	}
	
	///////////////
	//           //
	//  Getters  //
	//           //
	///////////////

	public int getAccount_no() {
		return account_no;
	}
	
	public float getBalance() {
	    return balance;
	}
	
	public Date getDate_created() {
	    return date_created;
	}
	
	public float getWithdrawal_limit() {
	    return withdrawal_limit;
	}
	
	public List<Transaction> getTransactions() {
		return transactions;
	}
	
	///////////////
	//           //
	//  Setters  //
	//           //
	///////////////

	public void setBalance(float bal) {
	    balance = bal;
	}

	public void setWithdrawal_limit(float limit) {
	    withdrawal_limit = limit;
	}
	
	public void setTransactions(List<Transaction> t) {
		transactions = t;
	}
	
	///////////////////
	//               //
	//   Functions   //
	//               //
	///////////////////
	
	// Update withdrawal limit
	public abstract void updateWithdrawalLimit();
	
	// Depositing (Putting money in)
	public void makeDeposit(float amount)
	{
		balance += amount;
		updateWithdrawalLimit();
		transactions.add(new Transaction("Deposit", amount, new Date(), balance));
	}
	
	// Withdrawal (Taking money out)
	public void makeWithdrawal(float amount)
	{
		if(amount > withdrawal_limit)
		{
			System.out.printf("Withdrawal Failed!\nAmount exceeded withdrawal limit of %f", withdrawal_limit);
			return;
		}
		balance -= amount;
		updateWithdrawalLimit();
		transactions.add(new Transaction("Withdrawal", amount, new Date(), balance));
	}
	
	// Check Balance
	public void checkBalance(Customer c, Account acc)
	{
		if(acc == null)
		{
			System.out.printf("Account doesn't exist for account number %s", c.getAccount_no());
			return;
		}
		System.out.printf("Name: %s\nBalance: %.2f", c.getName(), acc.getBalance());
	}
	
	//Transfer money to other account
	public void transferAmount(Account a2, float amount)
	{
		if(a2 == null)
		{
			System.out.println("Target account doens't exists!");
			return;
		}
		else if(getBalance() < amount)
		{
			System.out.println("Balance insufficient to transfer!");
			return;
		}
		else
		{
			// Withdraw from first account
			balance -= amount;
			updateWithdrawalLimit();
			transactions.add(new Transaction("Transfer (Sent)", amount, new Date(), balance));
			
			// Deposit into target account
			a2.setBalance(a2.getBalance() + amount);
			a2.updateWithdrawalLimit();
			a2.transactions.add(new Transaction("Transfer (Recieved)", amount, new Date(), a2.getBalance()));
		}
	}
	
	//Display account all deductions
	public void displayAllDeductions()
	{
		System.out.println("Account No: " + account_no);
	    System.out.println("Deductions:");
		for(Transaction t : transactions)
		{
			if(t.getType().equals("Zakat") || t.getType().equals("Tax"))
			{
				System.out.printf("Date: %s | Type: %s | Amount: Rs. %.2f | Remaining Balance: Rs. %.2f%n", 
								  t.getDate(), t.getType(), t.getAmount(), t.getNewBalance());
			}
		}
		System.out.print("\n");
	}
}