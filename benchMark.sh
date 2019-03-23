rm *.out *.o *.txt
for size in 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
#-rm *.out *.o
g++ -O0 -D N=$size main.cpp

echo $size
./a.out > /dev/null
done

