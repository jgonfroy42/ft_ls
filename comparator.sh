#!/bin/bash

> result.log

for (( ; ; ))
do
	read -p  "Enter arguments of ls to test: " args
	if  cmp -s <(ls $args 2>&1 ) <(./ft_ls $args 2>&1 | tr '\t' '\n')
	then	
		printf "./ft_ls $args: ✅\n" | tee -a result.log
	else
  		printf "./ft_ls $args: ❌\n" | tee -a result.log
		read -p "Display difference between ls $args and ./ft_ls $args ? (y) " display
		if [[ $display == "y" ]]; then
			diff <(ls $args 2>&1 ) <(./ft_ls $args 2>&1 | tr '\t' '\n') | tee -a result.log
		fi
	fi
	echo -e	| tee -a result.log
done


##TO DO : seulement afficher x ou v et faire des fichiers de log qui résume toutes les commandes testées à la fin (avec erreur ou non)
##est-ce qu'on garde en mémoire toutes les diff ? Est-ce qu'on affiche que les erreurs ? Deux fichiers de log : testés et error ?

