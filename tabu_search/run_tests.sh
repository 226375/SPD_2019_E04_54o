#!/bin/bash
for i in {1..100}
do 
	echo "Test $i"
	bash -c "./ts < Test_data/$i"
	echo -e "\n\n"
done
