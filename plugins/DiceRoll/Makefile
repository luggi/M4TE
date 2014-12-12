DiceRoll.so: DiceRoll.o
	g++ -shared -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++11 -I../../src -fPIC -c DiceRoll.cpp

clean:
	rm -f DiceRoll.so *.o
