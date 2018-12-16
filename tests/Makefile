# build test cases

tt.exe : main.o 
	g++ -Wall -Wextra main.o -o tt.exe

main.o: main.cpp ../tinytest.h
	g++ -Wall -Wextra -c main.cpp

clean :
	rm -f *~ main.o tt.exe
