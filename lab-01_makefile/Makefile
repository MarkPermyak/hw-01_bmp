lab-01_makefile: obj main algorithm util io
	gcc -o lab-01_makefile obj/main.o obj/algorithm.o obj/util.o obj/io.o
obj: 
	mkdir -p obj
io: src/io.c include/head.h
	gcc -c -o obj/io.o src/io.c -I include
algorithm: src/algorithm.c include/head.h
	gcc -c -o obj/algorithm.o src/algorithm.c -I include 
util: src/util.c include/head.h
	gcc -c -o obj/util.o src/util.c -I include 
main: src/main.c include/head.h
	gcc -c -o obj/main.o src/main.c -I include 
clean: 
	rm -r obj