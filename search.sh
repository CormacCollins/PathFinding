#!/bin/bash

file=$1
search=$2

if [ -z "$3" ]
then
	./cmake-build-debug/MySFML $file $search " " 
else
	./cmake-build-debug/MySFML $file $search "$3"
fi

