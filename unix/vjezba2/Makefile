primjer1:primjer1.o
	gcc primjer1.o -o primjer1
primjer1.o:primjer1.c
	gcc -c primjer1.c -o primjer1.o
primjer2:primjer2.o
	gcc primjer2.o -o primjer2
primjer2.o:primjer2.c
	gcc -c primjer2.c -o primjer2.o

primjer3:primjer3.o funkcije3.o
	gcc primjer3.o funkcije3.o -o primjer3
primjer3.o:primjer3.c
	gcc -c primjer3.c -o primjer3.o
funkcije3.o:funkcije3.c funkcije3.h
	gcc -c funkcije3.c -o funkcije3.o

clean:
	rm *.o primjer1 primjer2 primjer3
