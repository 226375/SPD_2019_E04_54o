#!/bin/bash
for i in {1..120}
do 
	echo "Test $i"
	bash -c "./zad2 < Test_data/$i"
	echo -e "\n\n"
done