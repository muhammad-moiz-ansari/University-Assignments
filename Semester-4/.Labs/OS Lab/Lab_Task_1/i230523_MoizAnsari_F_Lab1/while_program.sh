# !/bin/bash

# Input
echo "Enter a num: "
read num

while [ $num -ge 1 ]
do
	echo "Iteration: $num"
	num=$((num - 1))
done
echo "Countdown finished!"
