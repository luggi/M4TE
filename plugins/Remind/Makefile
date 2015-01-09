Remind.so: Remind.o
	g++ -shared -o $@ $^
	cp $@ ../../plugins/

%.o: %.cpp
	g++ -Wall -Werror -std=c++11 -I../../src -fPIC -c $^

clean:
	rm -f Remind.so *.o
