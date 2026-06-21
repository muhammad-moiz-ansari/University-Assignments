# !/bin/bash

#################### Identify the top 10 largest files ####################

# Storing all files info in a variable
# -> Size and file path
prevcount=21
filetemp=$(find ~ -type f -exec du -h {} + | sort -rh | head -n $prevcount)

# Ignoring the first 5 big files to avoid to delete my original files
count=$(($prevcount - 10))
files=""
while read -r tempv		# Reads a single line into the variable
do
	 if [ $count -le 0 ]; then
	 	files+="$tempv"$'\n'
	 fi
	 count=$((count-1))
done <<< "$filetemp"	# Inputs the variable into the loop without spawning subshell


echo "$prevcount Files:"$'\n'"$filetemp"$'\n'
echo "Ignoring the original large files..."$'\n'

# Displaying Top 10 Largest Files
echo "Top 10 Largest Files:"
count=1
echo "$files" | while read -r size file
do
	if [ $count -le 10 ]; then
		echo "File $count: $file"$'\t'"(Size = $size)"
	fi
	((++count))
done

# Taking user input:
echo $'\n'"Do you want to delete these files?"
while true
do
	echo "1. Yes"
	echo "2. No"
	read choice
	if [[ $choice -ne 1 && $choice -ne 2 ]]; then
		echo "Invaid input...Enter only 1 or 2"
	else
		break
	fi
done

count=1
if [ $choice = 1 ]; then
	echo "Deleting Top 10 Largest Files..."$'\n'
	echo "$files" | while read -r size file
	do
		echo "Deleting file [$file]"
		######rm "$file"				# UNCOMMENT it to actually delete files
		((++count))
		if [ $count -gt 10 ]; then
			break
		fi
	done
#else
#	echo "No delete  :("
fi


#################### Delete Duplicate Files ####################

# Getting all file paths in variable Files
numoffiles=100
files=$(find ~ -type f | sort | head -n $numoffiles)

echo $'\n'"----- $numoffiles Files (Paths) -----"$'\n'
echo "$files"
echo $'\n\n'

filenames=""

# Extracting File Names from whole file paths
while IFS= read -r file
do
	count=0
	index=$((${#file} - 1))

	while [[ ${file:$index:1} != "/" && $index -ge 0 ]]
	do
		index=$(($index-1))
		((++count))
	done
	((++index))tell
	filenames+="${file:$index:$count}"$'\n'
	
done <<< "$files"

echo "----- $numoffiles File Names -----"$'\n'
echo "$filenames"$'\n\n'

# Converting variable string into Arrays
filesarr=()
mapfile -t filesarr <<< "$files"	# Reads each line into an Array element

filenamearr=()
mapfile -t filenamearr <<< "$filenames"
#echo "${#filenamearr[@]} files"

###### Removing Cache & Old Log Files ######
cachesize=7
logsize=9
echo "Deleting Cache & Old Log Files..."
for ((i=0; i<${#filesarr[@]}; ++i))
do
	file="${filesarr[$i]}"
	for ((j=0; j<$((${#file} - $cachesize)); ++j))
	do
		if [[ ${file:$j:$cachesize} == ".cache/" ]]; then
			echo "Deleting file [$file]"		# Write rm "$file" to delete it
			break
		elif [[ ${file:$j:$logsize} == "/var/log/" ]]; then
			echo "Deleting file [$file]"		# Write rm "$file" to delete it
			break
		fi
	done
done

# Removes unneccesary packages
apt autoremove --dry-run
sudo apt autoremove

###### Checking duplication ######

chfiles=$(find /home/moiz129/Assignment1/DupFiles -type f | sort)
chfilenames=""
# Extracting File Names from whole file paths
while IFS= read -r file
do
	count=0
	index=$((${#file} - 1))

	while [[ ${file:$index:1} != "/" && $index -ge 0 ]]
	do
		index=$(($index-1))
		((++count))
	done
	((++index))
	chfilenames+="${file:$index:$count}"$'\n'
	
done <<< "$chfiles"

chfilesarr=()
mapfile -t chfilesarr <<< "$chfiles"	# Reads each line into an Array element
chfilenamearr=()
mapfile -t chfilenamearr <<< "$chfilenames"


# Making duplicate files array
duparr=()
dupind=0

for ((i=0; i<${#chfilenamearr[@]}; ++i))
do
	firsttime=0
	count=0
	echo "$i"
	for ((j=0; j<${#chfilenamearr[@]}; ++j))
	do
		if [[ ${chfilenamearr[$i]} == ${chfilenamearr[$j]} && $i -ne $j && ${chfilenamearr[$j]} != "" ]]; then
			if [ $firsttime -eq 0 ]; then
				firsttime=1
				tempind=$dupind
				((++dupind))
				duparr[$dupind]="${chfilesarr[$i]}"
				((++dupind))
			fi
			duparr[$dupind]="${chfilesarr[$j]}"
			((++dupind))
			((++count))
			chfilenamearr[$j]=""
		fi
	done
	if [ $count -gt 0 ]; then
		duparr[$tempind]=$count
	fi
done

printf "\n$((i-1)) Files checked for duplication:\n"
echo "$chfilenames"

echo $'\n\n'"DUPLICATE FILES:"
for temp in "${duparr[@]}"
do
	echo "$temp"
done

### Take User Input ###
echo $'\n'"Which operation would you like to perform? "
echo "1. Delete Duplicates"$'\n'"2. Hard-Link Duplicates"$'\n'"3. Move Duplicates to seperate folder"
while true
do
	echo -n "Choose: "
	read choice
	if [[ $choice -ge 1 && $choice -le 3 ]]; then
		break
	else
		echo "Invalid input...Enter only 1, 2, or 3!"
	fi
done

##### Delete Duplicates #####
case $choice in 
1)
	echo $'\n'"Deleting Duplicates..."
	for ((i=0; i<${#duparr[@]}; ++i))
	do
		count=${duparr[$i]}
		i=$(($i + 2))
		
		for ((j=0; j<$count; ++j))
		do
			echo "Deleting file [${duparr[$i]}]"
			rm "${duparr[$i]}"
			((++i))
		done
		i=$(($i - 1))
	done
;;
##### Hard-link duplicates #####
2)
	echo $'\n'"Creating Hard-Links..."
	for ((i=0; i<${#duparr[@]}; ++i))
	do
		count=${duparr[$i]}
		((++i))
		opath="${duparr[$i]}"	# original path
		((++i))
		
		echo "Original File: $opath"
		for ((j=0; j<$count; ++j))
		do
			echo "Creating hard-link of file [${duparr[$i]}]"
			rm "${duparr[$i]}"
			ln "$opath" "${duparr[$i]}"
			((++i))
		done
		linknum=$(ls -l "$opath")
		#echo "$linknum"
		linknum=${linknum:11:2}		# Extracts numer of hard links
		printf "No. of hard-links of file [$opath]: $linknum\n\n"
		i=$(($i - 1))
	done
;;
##### Move Duplicates #####
*)
	duppath="/home/moiz129/Assignment1/DUPLICATE_FILES/"
	rm -rf "$duppath"
	mkdir -p "$duppath"
	
	echo $'\n'"Moving Duplicates to a folder..."
	for ((i=0; i<${#duparr[@]}; ++i))
	do
		count=${duparr[$i]}
		i=$(($i + 2))
		
		for ((j=0; j<$count; ++j))
		do
			echo "Moving file [${duparr[$i]}]"
			path="${duparr[$i]:0:$((${#duparr[$i]}-4))}-$((j + 1)).txt"
			mv "${duparr[$i]}" "$path"
			mv "$path" "$duppath"
			((++i))
		done
		i=$(($i - 1))
	done
	
;;
esac

###### Deleteing Recently Accessed Files ######

daysnum=-1
echo $'\n'"Files accessed in the last $((-daysnum)) days:"

lafiles=$(find /home/moiz129/Assignment1/LastAccess -type f -atime $daysnum)	# Finds all files accessed within "daysnum" days
# Use -amin to check last access files within minutes time
echo "$lafiles"$'\n'

read -n 1 -p "Do you want to delete these recently accessed files?(Y/N) " ask
echo $'\n'
if [[ "$ask" == "y" || "$ask" == "Y" ]]; then
	echo "$lafiles" | while read -r file
	do
		echo "Deleting file [$file]"
		rm "$file"
	done
fi
