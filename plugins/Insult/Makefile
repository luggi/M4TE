Insult.so: Insult.o
	g++ -shared -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++11 -I../../src -fPIC -c Insult.cpp

clean:
	rm -f Insult.so *.o
