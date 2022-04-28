COMPILER = clang++
FLAGS_DEBUG = --std=c++98 -Wall -Wextra -Werror -fsanitize=address -g3
FLAGS = --std=c++98 -Wall -Wextra -Werror

vector:
	@$(COMPILER) $(FLAGS)	tests/vector_tests.cpp -o vector.out

map:
	@$(COMPILER) $(FLAGS)	tests/map_tests.cpp -o map.out

stack:
	@$(COMPILER) $(FLAGS)	tests/stack_tests.cpp -o stack.out

set:
	@$(COMPILER) $(FLAGS)	tests/set_tests.cpp -o set.out
clean:
	rm -f vector.out map.out stack.out set.out

.PHONY: clean vector map stack set
