# !/bin/bash

# Creating file
file=$(printf "$HOME" && printf "/Assignment1/q3log.txt")
touch "$file"
> "$file"

echo "Active Windows:"
#echo "$(xdotool search --onlyvisible --name "" getwindowname %@ )"
echo "$(xdotool getactivewindow getwindowname 2>/dev/null)"

# Calculating time spent per application:
declare -A apptime
prevwindow="$(xdotool getactivewindow getwindowname 2>/dev/null)"
if [[ "${prevwindow:0:35}" == "moiz129@moiz129-virtual-machine: ~/" ]]; then
	prevwindow="Ubuntu Terminal"
fi

starttime=$(date +%s)
endtime=$(date +%s)
loopendtime=$(($starttime + 120))	# 120 sec loop timer
blocktimer=10	# Seconds (For time to block app)

npapps=("YouTube - Google Chrome" "Spotify - Web Player: Music for everyone - Google Chrome" "Instagram - Google Chrome")


while [[ $(date +%s) -lt $loopendtime ]]
do
	currwindow="$(xdotool getactivewindow getwindowname 2>/dev/null)"
	if [[ "${currwindow:0:35}" == "moiz129@moiz129-virtual-machine: ~/" ]]; then
		currwindow="Ubuntu Terminal"
	fi
	if [[ -n "$currwindow" && "$prevwindow" != "$currwindow" ]]; then
	#if [[ $(date +%s) -ge $(($endtime + 5)) ]]; then		# Updates info every 5 seconds
		endtime=$(date +%s)
		etime=$(($endtime - $starttime))	#Elapsed time
		apptime["$prevwindow"]=$((${apptime["$prevwindow"]:-0} + $etime))
		
		starttime=$endtime
		prevwindow=$currwindow
		
		> "$file"
		echo $'\n'"App Usage Time:" >> "$file"
		for app in "${!apptime[@]}"
		do
			echo "$app: ${apptime[$app]} seconds" >> "$file"
		done
		cat "$file"
	fi
	sleep 2
	
	
	# Alerting Non-Productive App (Supposing Google)
	for app in "${!apptime[@]}"
	do
		for i in "${!npapps[@]}"
		do
			npapp="${npapps[$i]}"
			if [[ "$app" == "$npapp" && ${apptime[$app]} -gt $blocktimer ]]; then
				printf "\n$app has been used more than $blocktimer seconds\n"
				ask="n"
				read -n 1 -p "Do you want to block the app?(Y/N) " ask
				printf "\n"
				if [[ "$ask" == "Y" || "$ask" == "y" ]]; then
					xdotool search --onlyvisible --name "$npapp" windowkill
					echo "$npapp Closed Successfully!"$'\n'
					apptime[$app]=0		# App Timer Reset
					#npapps[$i]=""		# App will not be checked again
				else
					npapps[$i]=""
				fi
			fi
		done
	done
	
done

printf "\n\n--App Tracker Exited--\n"
