package model;
import java.util.Date;

public class Transaction {
	private String type;        // Deposit, Withdrawal, Transfer
	private float amount;
	private Date date;
	private float newBalance;
	
	public Transaction(String type, float amount, Date date, float newBalance) 
	{
        this.type = type;
        this.amount = amount;
        this.date = date;
        this.newBalance = newBalance;
    }
	
	///////////////
	//           //
	//  Getters  //
	//           //
	///////////////
	
	public String getType() {
	    return type;
	}

	public float getAmount() {
	    return amount;
	}

	public Date getDate() {
	    return date;
	}

	public float getNewBalance() {
	    return newBalance;
	}
	
	///////////////
	//           //
	//  Setters  //
	//           //
	///////////////
	
	public void setType(String t) {
	    type = t;
	}

	public void setAmount(float a) {
	    amount = a;
	}

	public void setDate(Date d) {
	    date = d;
	}

	public void setnewBalance(float nb) {
	    newBalance = nb;
	}

	///////////////////
	//               //
	//   Functions   //
	//               //
	///////////////////
	
}
