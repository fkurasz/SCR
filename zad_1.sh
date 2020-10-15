#!bin/sh
LC_ALL=C
dzien=$(date +%w) #+%w zamienia dzien tyg na liczbe np. czwartek to 4

if [ $dzien -eq 6 -o $dzien -eq 7 ]; then  #jesli dzien to 6 lub 7

    echo "Weekend"
else

    echo "Dzien roboczy"
fi
