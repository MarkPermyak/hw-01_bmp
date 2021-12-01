OBJECTS = obj/str.o obj/test_str.o obj/test.o
INCLUDE = include/str.h include/test_str.h
lab-02: obj $(OBJECTS)
	gcc -o $@ $(OBJECTS)
$(OBJECTS): obj/%.o: src/%.c $(INCLUDE)
	gcc -I include -c $< -o $@
obj:
	mkdir -p obj
clean:
	rm -r obj
	rm -f lab-02
