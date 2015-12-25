if [ -a "TRN_IN.dt" ]
then
if [ -a "IDX_TEST_A.dx" ]
	then
		./perceptron.app TRN_IN.dt IDX_TEST_A.dx
	else
		echo "IDX_TEST_A.dx not found!"
	fi
else
	echo "TRN_IN.dt not found!"
fi

