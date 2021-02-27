#!/bin/bash
function fun { 
	for f in $1/*
	do 
		if [[ -d $f ]] 
		then 
			fun $f
		else 
			echo "fixing "$f
			perl -p -i -e 's/    /\t/g' $f
		fi
	done
}

fun $1