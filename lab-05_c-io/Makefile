CXXFLAGS = -Wall -Werror -Wextra
OBJECTS = obj/main.o obj/clist.o obj/point_list.o
INCLUDE = include/clist.h include/point_list.h
lab-05_c-io: obj $(OBJECTS)
	gcc -o $@ $(OBJECTS)
$(OBJECTS): obj/%.o: src/%.c $(INCLUDE)
	gcc -I include -c $< -o $@
obj:
	mkdir -p obj
clean:
	rm -r obj
	rm -f lab-05_c-io
