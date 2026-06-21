package model;
import java.util.Date;

import tools.CalendarTools;

public class CheckingAccount extends Account {
	private int transactionCount;
	private int currentMonth;

	public CheckingAccount(int acc_no, float initial_balance) 
	{
		super(acc_no, initial_balance);
		setWithdrawal_limit(5000);
		transactionCount = 0;
		currentMonth = CalendarTools.getMonth();
	}
	public CheckingAccount(int acc_no) 
	{
		super(acc_no, 0);
		setWithdrawal_limit(5000);
		currentMonth = CalendarTools.getMonth();
	}
	
	///////////////////
	//               //
	//   Functions   //
	//               //
	///////////////////
	
	// Checks free transaction limit
	public void checkFreeTransction()
	{
		if(currentMonth != CalendarTools.getMonth())
		{
			transactionCount = 0;	// Reset free transaction count
			currentMonth = CalendarTools.getMonth();
		}
		transactionCount++;
		if(transactionCount > 2)
		{
			setBalance(getBalance() - 10);
			getTransactions().add(new Transaction("Tax", 10, new Date(), getBalance()));
		}
	}
	
	@Override
	public void makeDeposit(float amount)
	{
		checkFreeTransction();
		super.makeDeposit(amount);
	}
	
	@Override
	public void makeWithdrawal(float amount)
	{
		checkFreeTransction();
		super.makeWithdrawal(amount);
	}
	
	// Update withdrawal limit
	@Override
	public void updateWithdrawalLimit()
	{
		setWithdrawal_limit(5000);
	}
}
