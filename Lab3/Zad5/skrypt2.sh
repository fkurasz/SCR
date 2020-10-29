#!bin/sh


while [ 1 ]
do
	trap '' INT QUIT FPE ILL
	date +%T
	sleep 1
done
