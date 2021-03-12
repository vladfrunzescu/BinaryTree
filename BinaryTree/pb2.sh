#!/bin/bash

if test $# -eq 0; then
	echo "Nu s-a dat niciun parametru"
	exit 1
fi

for dir in $@; do
	if ! test -d $dir; then
		echo "Unul dintre argumente nu este director, incercati din nou!"
       		exit 1
	fi
done

cat extern.txt | while read ext; do
	nr=0
	for dir in $@; do
		find $dir -type f | while read file; do
			if grep -q "^.\+$ext$" $file;then
				nr=$((nr+1))
				
			fi	
		done
	done
	echo "Sunt $nr fisiere cu extensia $ext in directoarele date"
done
