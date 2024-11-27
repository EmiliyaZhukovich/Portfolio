CC = gcc
FLAGS = -Wall -Werror -Wextra

door_struct: clean Quest_1
list_test: clean Quest_2
stack_test: clean Quest_3

Quest_1: dmanager_module.o
	$(CC) $(FLAGS) $^ -o ../build/$@
Quest_2: list_test.o list.o
	$(CC) $(FLAGS) $^ -o ../build/$@
Quest_3: stack_test.o stack.o
	$(CC) $(FLAGS) $^ -o ../build/$@

dmanager_module.o: dmanager_module.c door_struct.h
	$(CC) $(FLAGS) -c $< -o $@
list.o: list.c list.h
	$(CC) $(FLAGS) -c $< -o $@
list_test.o: list_test.c list.h
	$(CC) $(FLAGS) -c $< -o $@
stack.o: stack.c stack.h
	$(CC) $(FLAGS) -c $< -o $@
stack_test.o: stack_test.c stack.h
	$(CC) $(FLAGS) -c $< -o $@
clean: 
	rm -rf *.o ../build/*

rebuild: clean Quest_1 Quest_2 Quest_3

