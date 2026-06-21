# !/bin/bash

# File paths
file=$(printf "$HOME" && printf "/Assignment1/q5csv.csv")

# Create and erase file
touch "$file"
> "$file"

printf "\n\n ----------- Daily Expense Tracker -----------\n\n\n"

# Inputs
printf "Enter your monthly income: "
read income
printf "Enter your budget: "
read budget
printf "Enter month(1-12): "
read month
if [ $month -gt 12 ]; then
	month=12				# Default if wrong input
fi
printf "Enter year(20--): "
read year
if [[ $year -lt 0 || $year -gt 99 ]]; then
	year=25				# Default if wrong input
fi
year=$((2000 + $year))

edate="-$month-$year"
savings=$income
loan=0
spent=0
declare -A expenses
filestr="CATEGORY,AMOUNT,DATE"

op=0

while true		# Main loop
do
	echo $'\n'"Choose an option you are entering:"
	echo "1. Update Budget"
	echo "2. Enter Expense"
	echo "3. Enter any Extra Income"
	echo "4. Exit"
	while true
	do
		read -p "Choose: " op
		if [[ $op -ge 1 && $op -le 4 ]]; then
			break
		else
			echo "Invalid Input...Enter only 1-4"
		fi
	done
	
	case $op in 
	1)
		read -p "Enter new budget: " budget
		echo "Budget updated!"
	;;
	2)
		read -p "Enter category: " cat
		read -p "Enter amount(PKR): " amount
		read -p "Enter date(Only day [1-31]): " date
		if [ $date -lt 0 ]; then
			date=31				# Default if wrong input
		fi
		date="$date$edate"
		spent+=$amount
		savings=$(($savings - $amount))
		
		if [ $savings -ge 0 ]; then
			printf "\nRs. $savings Left\n"
		else
			printf "\nRs. 0 Left\n"
		fi
		if [ $spent -gt $budget ]; then
			echo "ALERT! Budget crossed!"
		fi
		filestr+=$(printf "\n$cat,$amount,$date")
		expenses[$cat]=$((${expenses[$cat]:-0} + $amount))
	;;
	3)
		read -p "Enter extra income: " amount
		income=$(($income + $amount))
		savings=$(($savings + $amount))
	;;
	4)
		echo "Exiting..."
		if [ $savings -lt 0 ]; then
			loan=$((- $savings))
			savings=0
		fi
		echo -n "$filestr" > "$file"
		break
	;;
	esac
done

printf "\n\nExpenses Summary ($month-$year):\n"
for cat in ${!expenses[@]}
do
	printf "$cat: ${expenses[$cat]}\n"
done

printf "\nSpending Summary ($month-$year):\n"
echo "Total income: $income"
echo "Savings: $savings"
echo "Loan: $loan"

printf "\nExpenses Trend ($month-$year):"

# Displaying Data as Graph
gnuplot << EOF
set datafile separator ","
set terminal dumb
plot "/home/moiz129/Assignment1/q5csv.csv" using 2:xtic(1) with lines title ""
exit
EOF
