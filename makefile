libreriaEstatica: lib/hash_ps3.a lib/csapp.a

lib/hash_ps3.a: obj/tablahash.o include/tablahash.h
	mkdir -p lib
	ar rcs lib/hash_ps3.a obj/tablahash.o

obj/tablahash.o: src/tablahash.c include/tablahash.h
	mkdir -p obj
	gcc -O2 -c -I./include src/tablahash.c -o $@

lib/csapp.a: obj/csapp.o include/csapp.h
	mkdir -p lib
	ar rcs lib/csapp.a obj/csapp.o

obj/csapp.o: src/csapp.c include/csapp.h
	mkdir -p obj
	gcc -O2 -c -I./include src/csapp.c -o $@



broker: lib/hash_ps3.a lib/csapp.a obj/broker.o
	mkdir -p obj
	gcc -O2 obj/broker.o lib/hash_ps3.a -pthread -o broker

obj/broker.o: src/broker.c
	mkdir -p obj
	gcc -O2 -c $^ -o $@ -I./include

publisher: lib/csapp.a obj/publisher.o
	gcc -O2 obj/publisher.o -o $@

obj/publisher.o: src/publisher.c
	mkdir -p obj
	gcc -O2 -c $^ -o $@ -I./include
