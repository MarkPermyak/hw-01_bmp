OBJECTS = obj/io.o obj/algorithm.o obj/util.o obj/main.o

lab-01_makefile: make_obj $(OBJECTS)
	gcc -o lab-01_makefile $(OBJECTS)
make_obj: 
	mkdir -p obj
obj/io.o: src/io.c  include/head.h
	gcc -c -o obj/io.o src/io.c -I ./include
obj/algorithm.o: src/algorithm.c  include/head.h
	gcc -c -o obj/algorithm.o src/algorithm.c -I ./include 
obj/util.o: src/util.c include/head.h
	gcc -c -o obj/util.o src/util.c -I ./include
obj/main.o: src/main.c include/head.h
	gcc -c -o obj/main.o src/main.c -I ./include
clean: 
	rm -r obj
