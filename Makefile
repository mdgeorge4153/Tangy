CPPFLAGS=-g
LDFLAGS=-g

gtans: gtans.o algebra.o
	g++ -g -o gtans gtans.o algebra.o

gtans.o: gtans.cc algebra.h algebra.hcc
	g++ -c -g -o gtans.o gtans.cc

algebra.o: algebra.cc algebra.h algebra.hcc
	g++ -c -g -o algebra.o algebra.cc

clean:
	rm -f *.o gtans

