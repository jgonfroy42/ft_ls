#!/bin/bash

export LC_ALL=C

> result.log

compare ()
{
	if  cmp -s <(ls $1 2>&1 ) <(./ft_ls $1 -1 2>&1)
	then	
		printf "./ft_ls $1: ✅\n" | tee -a result.log
	else
  		printf "./ft_ls $1: ❌\n" | tee -a result.log
		read -p "Display difference between ls $1 and ./ft_ls $1 ? (y) " display < /dev/tty
		if [[ $display == "y" ]]; then
			diff <(ls $1 2>&1 ) <(./ft_ls $1 2>&1 -1) | tee -a result.log
		fi
	fi

}

for (( ; ; ))
do
	read -p  "Enter a file or arguments: " args

	if [ -f  "$args" ] ; then
		while IFS= read -r line
		do
			compare "$line"
		done < $args
		echo -e	| tee -a result.log

	else
		compare "$args"
		echo -e	| tee -a result.log
	fi
done

#add leaks verification ?
