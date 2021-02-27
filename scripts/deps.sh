#!/bin/bash
source=`echo $1 | tr : " "`
cc=`echo $2 | tr : " "`
cflags=`echo $3 | tr : " "`

for file in $source
do
	object=`echo $file | grep -oE "[a-zA-Z]*\.[cp]+" | grep -oE "^[a-zA-Z]*"`;
	object=`echo $object.o`;
	if [[ ! -f $object || $file -nt $object ]]
	then
		echo -e "\t\t\tMaking "$object
		$cc $cflags $file -o $object
	fi
done
