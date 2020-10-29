#!bin/sh
x=1	
	cat | echo "Wiadomość $x" > potok
	x=$(($x+1))
	sleep 1

	cat | echo "Wiadomość $x" > potok
	x=$(($x+1))
	sleep 1
