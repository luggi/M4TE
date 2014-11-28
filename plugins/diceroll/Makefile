diceroll.so: diceroll.o
	g++ -shared -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++11 -I../../src -fPIC -c diceroll.cpp

clean:
	rm -f libdiceroll.so *.o
