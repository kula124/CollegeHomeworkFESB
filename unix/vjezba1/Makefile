primjer1:source.o
	gcc -Wall source.o -o primjer1
source.o:source.c
	gcc -Wall -c  source.c -o source.o
primjer2:source2.o funkcije.o
	gcc -Wall source2.o funkcije.o -o primjer2
funkcije.o:funkcije.c
	gcc -Wall -c funkcije.c -o funkcije.o
source2.o:source2.c
	gcc -Wall -c source2.c -o source2.o
clean:
	rm *.o primjer1 primjer2

