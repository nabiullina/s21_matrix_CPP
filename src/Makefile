CC = g++
TEST_FLAGS = -lm -lgtest -lpthread
CFLAGS = -Wall -Werror -Wextra -lstdc++

TESTS_SOURCE = Tests/s21_matrix_oop_test.cpp
LIB = s21_matrix_oop.a
FUNCS_SOURCE = s21_matrix_oop.cpp

OS = $(shell uname)

.PHONY: test s21_matrix_oop.a

$(LIB):
	$(CC) $(CFLAGS) $(FUNCS_SOURCE) -c
	ar rcs $(LIB) *.o
	ranlib $(LIB)

test: $(LIB)
	$(CC) $(CFLAGS) $(TESTS_SOURCE) -o test $(TEST_FLAGS) $(FUNCS_SOURCE) -L.
	./test

clean:
	@rm -rf *.a
	@rm -rf *.o
	@rm -rf test
	@rm -rf RESULT.txt

check_style:
	@cp ../materials/linters/.clang-format .
	@echo "======= CHECK GOOGLE CODE STYLE ======="
	clang-format -n *.cpp *.h Tests/*.cpp

check_leaks: clean $(LIB)
ifeq ($(OS), Linux)
	$(CC) $(CFLAGS) -g Tests/*.cpp -o test $(TEST_FLAGS) $(LIB) -L.
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --log-file=RESULT.txt ./test
	cat RESULT.txt
	@rm -rf RESULT.txt
endif