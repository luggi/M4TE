insult.so: insult.o
	g++ -shared -o $@ $^
	cp insult.so ../../plugins/

%.o: %.cpp
	g++ -Wall -Werror -std=c++11 -I../../src -fPIC -c insult.cpp

clean:
	rm -f libinsult.so *.o
