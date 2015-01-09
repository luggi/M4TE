diceroll.so: diceroll.o
	g++ -shared -o $@ $^
	cp $@ ../../src/plugins/

%.o: %.cpp
	g++ -Wall -Werror -std=c++11 -I../../src -fPIC -c $^

clean:
	rm -f diceroll.so *.o
