#!bin/sh

sudo apt install -y mutt
sudo apt update

echo
echo

sciezka=$(pwd)

for mail in $(cat $sciezka/adresy.txt)
do
	echo $sciezka/wiadomosc.txt | mutt -s "Okna PCV" $mail -a $sciezka/spec*.pdf
	echo "Wyslano"
done
