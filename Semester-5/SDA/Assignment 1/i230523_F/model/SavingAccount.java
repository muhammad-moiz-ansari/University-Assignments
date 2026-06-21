package model;

import java.util.Date;
import tools.CalendarTools;

public class SavingAccount extends Account {
	private float interestRate;
	private int currentYear;

	public SavingAccount(int acc_no, float initial_balance, float interestRate) 
	{
		super(acc_no, initial_balance);
		setWithdrawal_limit(initial_balance);
		this.interestRate = interestRate;
		this.currentYear = 0;
		
	}
	public SavingAccount(int acc_no, float initial_balance) 
	{
		super(acc_no, initial_balance);
		setWithdrawal_limit(initial_balance);
		this.interestRate = 5.0f;
		this.currentYear = 0;
	}
	public SavingAccount(int acc_no) 
	{
		super(acc_no, 0);
		setWithdrawal_limit(0);
		this.interestRate = 5.0f;
		this.currentYear = 0;
	}
	
	
	///////////////
	//           //
	//  Getters  //
	//           //
	///////////////
	
	public float getInterestRate() {
		return interestRate;
	}
	
	///////////////
	//           //
	//  Setters  //
	//           //
	///////////////
	
	public void setInterestRate(float ir) {
		interestRate = ir;
	}
	
	///////////////////
	//               //
	//   Functions   //
	//               //
	///////////////////
	
	// Update withdrawal limit
	@Override
	public void updateWithdrawalLimit()
	{
		setWithdrawal_limit(getBalance());
	}
	
	//Calculates zakat
	public float calculateZakat()
	{
		if(getBalance() >= 20000)
		{
			return (getBalance() * (float)2.5) / 100;
		}
		else
		{
			System.out.println("Balance insufficient for zakat!");
			return 0;
		}
	}
	
	public float calculateInterest()
	{
		return (getBalance() * interestRate) / 100;
	}
	
	//Deduct Zakat
	public void deductZakat()
	{
		if(currentYear == CalendarTools.getYear())
		{
			System.out.printf("Zakat has already been paid for the year %d%n", currentYear);
			return;
		}
		else
		{
			currentYear = CalendarTools.getYear();
			float amount = calculateZakat();
			if(amount > 0)
			{
				setBalance(getBalance() - amount);
				getTransactions().add(new Transaction("Zakat", amount, new Date(), getBalance()));
			}
			System.out.printf("A zakat of %f has been paid for the year %d%n", amount, currentYear);
		}
	}
}