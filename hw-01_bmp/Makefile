CXXFLAGS = -Wall -Werror -Wextra
OBJECTS = obj/main.o obj/bmp.o 
INCLUDE = include/bmp.h
hw-01_bmp: obj $(OBJECTS)
	gcc -o $@ $(OBJECTS)
$(OBJECTS): obj/%.o: src/%.c $(INCLUDE)
	gcc -I include -c $< -o $@
obj:
	mkdir -p obj
clean:
	rm -r obj
	rm -f hw-01_bmp
