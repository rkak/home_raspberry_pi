all : test

test : test.o
	gcc -o $@ $+

test.o : test.s
	as -o $@ $<

clean:
	rm -rf test *.o
