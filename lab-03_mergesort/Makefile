OBJECTS = obj/main.o obj/mergesort.o
INCLUDE = include/mergesort.h
lab-03_mergesort: obj $(OBJECTS)
	gcc -o $@ $(OBJECTS)
$(OBJECTS): obj/%.o: src/%.c $(INCLUDE)
	gcc -I include -c $< -o $@
obj:
	mkdir -p obj
clean:
	rm -r obj
	rm -f lab-03_mergesort
