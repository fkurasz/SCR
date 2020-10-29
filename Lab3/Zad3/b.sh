#!bin/sh

while [ 1 ]
do
	(exec 1<>potok; echo "Wiadomosc"; sed 's/e/o/g'; <&1 >&2)  
  	foo
	sleep 1
done
