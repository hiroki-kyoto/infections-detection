#! /bin/bash
# PIPE LINE TO SOLVE SORTING PROBLEM
# [pipeline.sh]
# $1 is input $2 is output

# 1.create index data
#./build_index.app $1 $2
./build_index.app $1 $2
if [ $? -eq 0 ]
then
	echo 'Index constructed for $1'
	echo 'Weight vector data stored in $2'
	echo 'Indexing done.'
else
	echo 'Failed to build index for $1'
fi
