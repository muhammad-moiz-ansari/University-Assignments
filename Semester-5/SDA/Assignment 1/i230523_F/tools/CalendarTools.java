package tools;

import java.util.Calendar;
import java.util.Date;

public class CalendarTools {
	// Returns current month
	public static int getMonth()
	{
		Date date = new Date();
		Calendar cal = Calendar.getInstance();
		cal.setTime(date);
		return cal.get(Calendar.MONTH) + 1;
	}
	
	// Returns current month
	public static int getYear()
	{
		Date date = new Date();
		Calendar cal = Calendar.getInstance();
		cal.setTime(date);
		return cal.get(Calendar.YEAR);
	}
}
