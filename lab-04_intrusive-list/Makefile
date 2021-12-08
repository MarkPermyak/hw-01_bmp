OBJECTS = obj/main.o obj/clist.o
INCLUDE = include/clist.h
example: obj $(OBJECTS)
	gcc -o $@ $(OBJECTS)
$(OBJECTS): obj/%.o: src/%.c $(INCLUDE)
	gcc -I include -c $< -o $@
obj:
	mkdir -p obj
clean:
	rm -r obj
	rm -f example
