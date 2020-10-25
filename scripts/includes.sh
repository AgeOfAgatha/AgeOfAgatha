#!/bin/bash
function get_includes {
	prefix=`echo $1 | grep -oE '([a-zA-Z\.]*/)*'`
	for include in `grep '#include \"[a-zA-Z/\.]*\.h\"' $1 | grep -o '[a-zA-Z/\.]*\.h'`
	do
		simplify_path $prefix$include
	done
}

function recursive_include {
	source=$1
	includes=`echo $2 | tr : " "`

	new=`get_includes $source`
	for include in $new
	do
		include=`simplify_path $include`
		if [[ `echo $includes | grep -o $include` == "" ]]
		then
			includes="$includes $include"
			includes=`echo $includes | tr " " :`
			includes=`recursive_include $include $includes`
			includes=`echo $includes | tr : " "`
		fi
	done
	echo $includes
}

function simplify_path {
	path=`echo $1 | sed s:[a-zA-Z]*[a-zA-Z]/../::g`
	echo $path
}

function object_file {
	file=`echo $1 | grep -oE "[a-zA-Z]*\.[cp]+" | grep -oE "^[a-zA-Z]*"`
	file=`echo $file.o`
	echo $file
}

function check_update {
	source=$1
	cc=$2
	cflags=`echo $3 | tr : " "`
	object=`object_file $source`
	includes=`recursive_include $source $source`

	for file in $includes
	do
		if [[ ! -f $object || $file -nt $object ]]
		then
			echo -e "\t\t\tMaking "$object
			$cc $cflags $source -o $object
			break
		fi
	done
}

function recursive_update {
	includes=`recursive_include $1 $1`

	for file in $includes
	do
		source=`echo $file | grep -oE "^(../)*[a-zA-Z/]*[a-zA-Z]+"`
		source=`echo $source.cpp`
		if [[ -f $source ]]
		then
			check_update $source $2 $3
		fi
	done
}

recursive_update $1 $2 $3
