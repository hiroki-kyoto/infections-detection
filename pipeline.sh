#! /bin/bash
# PIPE LINE TO SOLVE SORTING PROBLEM
# [pipeline.sh]
# $1 is input $2 is output

# 1.create index data
if [ ! -a "$1" ]
then
	echo "File $1 NOT EXISTS!"
	echo "Failed to run this program!"
	return 1
fi

if [ -a "$2" ]
then
	echo "File [$2] Already Exists!"
	echo "Skip Indexing building process."
else
	./build_index.app $1 $2
	if [ $? -eq 0 ]
	then
		echo 'Index constructed for' $1
		echo 'Weight vector data stored in' $2
		echo 'Indexing done.'
	else
		echo 'Failed to build index for' $1
		return 1
	fi
fi

# TEST FOR A
if [ -a "TRN_IN.dt" ]
then
	./perceptron.app TRN_IN.dt  $2
	echo "RESULT IS : "
	if [ -a "TRN_OUT.dt" ]
	then
		more "TRN_OUT.dt"
	else
		echo "TRN_OUT.dt not found!"
		echo "Last Program didnt create OUTPUT!"
		echo "failure"
		return 1
	fi
else
	echo "TRN_IN.dt is not found!"
	echo "Test running failed!"
	return 1
fi

