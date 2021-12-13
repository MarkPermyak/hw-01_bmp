CXXFLAGS = -Wall -Werror -Wextra
OBJECTS = obj/main.o obj/clist.o
INCLUDE = include/clist.h
lab-04_intrusive-list: obj $(OBJECTS)
	gcc -o $@ $(OBJECTS)
$(OBJECTS): obj/%.o: src/%.c $(INCLUDE)
	gcc -I include -c $< -o $@
obj:
	mkdir -p obj
clean:
	rm -r obj
	rm -f lab-04_intrusive-list
