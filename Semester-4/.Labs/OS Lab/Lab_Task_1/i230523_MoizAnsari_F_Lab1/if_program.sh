# !/bin/bash

# Input
echo "Enter a number: "
read num

if [ $num -eq 0 ]; then
	echo "Entered number is zero"
elif [ $num -gt 0 ]; then
	echo "Entered number is positive"
else
	echo "Entered number is negative"
fi
