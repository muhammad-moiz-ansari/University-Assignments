# !/bin/bash

# Initializing paths
copypath=$(printf "$HOME" && printf "/Assignment1/Copyfiles/")
dummy=$(printf "$copypath" && printf "dummy.txt")
log=$(printf "$HOME" && printf "/Assignment1/" && printf "q2log.txt")

# Log file
touch "$log"
str=""
$str > "$log"

if [ -e "$dummy" ]; then	# Dummy file
	rm "$dummy"
fi
# Making copyfiles array
copyfiles=$(find ${copypath:0:$((${#copypath}-1))} -type f | sort)
mapfile -t copyarr <<< "$copyfiles"
		
# File names collection
files=$(find ~/Assignment1/Q2files -type f | sort)
mapfile -t filearr <<< "$files"

choice=1
### Take User Input ###
while [ $choice -ne 5 ]		# Main Loop
do
	echo $'\n'"Which operation would you like to perform? "
	echo "1. Invert File Permissions"$'\n'"2. Find String"$'\n'"3. Copy File Content"$'\n'"4. Update Modified Date"$'\n'"5. Exit"

	while true
	do
		echo -n "Choose: "
		read choice
		if [[ $choice -ge 1 && $choice -le 5 ]]; then
			break
		else
			echo "Invalid input...Enter only 1-5!"
		fi
	done
	
	if [ $choice -eq 5 ]; then
		break
	fi
	
	# LOG
	logstr+=$(printf "\n\nOption 0%s selected at %s\n" "$choice" "$(date "+%d-%m-%Y %H:%M:%S")")

	# File name input
	isfile=0
	index=0
	if [[ $choice -eq 1 || $choice -eq 2 || $choice -eq 4 ]]; then
		printf $'\n'"Enter File Name: "
		read filename
		
		for file in ${filearr[@]}	# Looking for that file
		do
			if [[ "$(basename "$file")" == "$filename" ]]; then
				isfile=1
				break
			fi
			((++index))
		done
	fi

	
	if [[ $choice -eq 1 || $choice -eq 2 || $choice -eq 4 ]]; then
		if [ $isfile -eq 1 ]; then
			######## Invert File Permissions ########
			if [ $choice -eq 1 ]; then
				# LOG
				logstr+=$(printf "\nFile name: $filename")
				
				# Print permissions
				str=$(printf $'\n'"Permissions of $filename: " && stat --format="%A  %y" "${filearr[$index]}")
				logstr+="$str"
				echo -n "$str"
				
				# Modifying permissions
				if [ -r "${filearr[$index]}" ]; then
					chmod -r "${filearr[$index]}"
				else
					chmod +r "${filearr[$index]}"
				fi
				
				if [ -w "${filearr[$index]}" ]; then
					chmod a-w "${filearr[$index]}"
				else
					chmod a+w "${filearr[$index]}"
				fi
				
				if [ -x "${filearr[$index]}" ]; then
					chmod -x "${filearr[$index]}"
				else
					chmod +x "${filearr[$index]}"
				fi
				str=$(echo $'\n'"Permissions changed!")
				logstr+="$str"
				echo -n "$str"
				
				# Printing updated permissions
				str=$(echo -n $'\n'"Updated Permissions of $filename: " && stat --format="%A  %y" "${filearr[$index]}")
				logstr+="$str"
				echo "$str"
				
			######## Find String ########
			elif [ $choice -eq 2 ]; then
				# LOG
				logstr+=$(printf "\nFile name: $filename")
				
				echo -n "Enter the string: "
				read str
				logstr+=$(printf "\nString: $str")
				
				chmod 777 "${filearr[$index]}"
				echo $'\n'"String found in following lines:"
				grep -n "$str" "${filearr[$index]}"
				logstr+=$(printf "\nString found in following lines:"$'\n' && grep -n "$str" "${filearr[$index]}")
				
			######## Update Modified Date ########
			else 	# choice = 4
				# LOG
				logstr+=$(printf "\nFile name: $filename"$'\n')
				
				chmod 777 "${filearr[$index]}"
				stat --format="Current Modified Date: %y" "${filearr[$index]}"
				logstr+=$(printf "\n" && stat --format="Current Modified Date: %y" "${filearr[$index]}")
				curr=$(date +%s)
				mod=$(stat --format="%Y" "${filearr[$index]}")
				if [ $(($curr - $mod)) -gt 86400 ]; then
					touch -m "${filearr[$index]}"
					str="Modified Time updated!"
				else
					str="Modified Time not updated!"
				fi
				echo "$str"
				logstr+=$(printf "\n$str")
				
				stat --format="Modified Date: %y" "${filearr[$index]}"
			fi
		else
			echo "File not found!"
		fi
	fi

	######## Copy File Content ########
	if [ $choice -eq 3 ]; then
		touch "$dummy"
		
		#LOG
		logstr+=$(printf "\nFiles at even location: ")
		str=""
		
		n=5
		for ((i=0; i<${#copyarr[@]}; ++i))
		do
			if [ $(($(($i+1))%2)) -eq 0 ]; then
				head -$n "${copyarr[$i]}" >> "$dummy"
				str+=""$(basename "${copyarr[$i]}")", "
			fi
		done
		str="${str:0:$((${#str}-2))}"
		logstr+=$(echo -n "$str" && echo " "$'\n')
		logstr+=$(printf "\nFiles at odd location: ")
		str=""
		
		for ((i=0; i<${#copyarr[@]}; ++i))
		do
			if [ $(($(($i+1))%2)) -ne 0 ]; then
				tail -$n "${copyarr[$i]}" >> "$dummy"
				str+=""$(basename "${copyarr[$i]}")", "
			fi
		done
		str="${str:0:$((${#str}-2))}"
		logstr+=$(echo "$str" && echo "Dummy.txt is created and $n lines if each file copied in it.")
		
		echo "Dummy File:"
		cat "$dummy"
	fi

done



logstr+=$(printf "\n\nOption exit \nScript terminated at  "  && date "+%d-%m-%Y  %H:%M:%S")
echo "$logstr" >> "$log"

cat "$log"



