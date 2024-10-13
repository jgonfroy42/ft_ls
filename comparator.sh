#!/bin/bash

> diff.log

# Set the color variable
green='\033[0;32m'
red='\033[0;31m'
# Clear the color after that
clear='\033[0m'

declare -i wc_result=0

for (( ; ; ))
do
	echo -e
	read -p  "Enter arguments of ls to test: " args
#	diff <(ls $args) <(./ft_ls $args| tr '\t' '\n') >> diff.log
#	if [ $(wc -c < diff.log) -eq $wc_result ]; then
	if cmp -s <(ls $args) <(./ft_ls $args| tr '\t' '\n'); then
		printf "./ft_ls $args: ✅\n"
	else
  		printf "./ft_ls $args: ❌\n"
		read -p "Display 'diff ls $args ./ft_ls $args' ? (y/n) " display
		if [[ $display == "y" ]]; then
			less diff.log
	fi
fi	
done


##TO DO : seulement afficher x ou v et faire des fichiers de log qui résume toutes les commandes testées à la fin (avec erreur ou non)
##est-ce qu'on garde en mémoire toutes les diff ? Est-ce qu'on affiche que les erreurs ? Deux fichiers de log : testés et error ?

