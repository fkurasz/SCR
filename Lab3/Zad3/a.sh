#!bin/sh
while[1]
do
	(exec 1<>potok; echo "Wiadomosc"; sed 's/e/o/g; 1q' <&1 >&2)
	sleep 1
done
