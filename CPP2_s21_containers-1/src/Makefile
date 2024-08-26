CC=g++
CFLAGS=-Wall -Werror -Wextra --std=c++17 
GCOV=-fprofile-arcs -ftest-coverage
GTEST=-lgtest -pthread
NAME=s21_containers
TESTS_FOLDER=tests

all: test

clean:
	rm -rf *.a *.gcda *.gcno *.o *.info *_test report
	 
test: clean
	$(CC) $(TESTS_FOLDER)/*.cpp $(CFLAGS) $(GTEST) -o $(NAME)_test
	./$(NAME)_test

gcov_report:
	$(CC) $(TESTS_FOLDER)/*.cpp $(CFLAGS) $(GCOV) $(GTEST) -o $(NAME)_test
	./$(NAME)_test
	lcov  -t "$(NAME)_test" -o $(NAME)_test.info --no-external -c -d .  
	genhtml -o report $(NAME)_test.info
	open report/index.html
	rm -rf *.gcda *.gcno

valgrind: all
	CK_FORK=no valgrind --tool=memcheck --leak-check=yes -s ./$(NAME)_test

list_test:
	$(CC) $(TESTS_FOLDER)/main.cpp $(TESTS_FOLDER)/s21_list_test.cpp  $(CFLAGS) $(GCOV) $(GTEST) -o s21_list_test
	./s21_list_test
list_vg: list_test
	CK_FORK=no valgrind --tool=memcheck --leak-check=yes -s ./s21_list_test

queue_test:
	$(CC) $(TESTS_FOLDER)/main.cpp $(TESTS_FOLDER)/s21_queue_test.cpp  $(CFLAGS) $(GCOV) $(GTEST) -o s21_queue_test
	./s21_queue_test
queue_vg: queue_test
	CK_FORK=no valgrind --tool=memcheck --leak-check=yes -s ./s21_queue_test

vector_test:
	$(CC) $(TESTS_FOLDER)/main.cpp $(TESTS_FOLDER)/s21_vector_test.cpp  $(CFLAGS) $(GCOV) $(GTEST) -o s21_vector_test
	./s21_vector_test
vector_vg: vector_test
	CK_FORK=no valgrind --tool=memcheck --leak-check=yes -s ./s21_vector_test

stack_test:
	$(CC) $(TESTS_FOLDER)/main.cpp $(TESTS_FOLDER)/s21_stack_test.cpp  $(CFLAGS) $(GCOV) $(GTEST) -o s21_stack_test
	./s21_stack_test
stack_vg: stack_test
	CK_FORK=no valgrind --tool=memcheck --leak-check=yes -s ./s21_stack_test

set_test:
	$(CC) $(TESTS_FOLDER)/main.cpp $(TESTS_FOLDER)/s21_set_test.cpp  $(CFLAGS) $(GCOV) $(GTEST) -o s21_set_test
	./s21_set_test
set_vg: set_test
	CK_FORK=no valgrind --tool=memcheck --leak-check=yes -s ./s21_set_test

map_test:
	$(CC) $(TESTS_FOLDER)/main.cpp $(TESTS_FOLDER)/s21_map_test.cpp  $(CFLAGS) $(GCOV) $(GTEST) -o s21_map_test
	./s21_map_test
map_vg: map_test
	CK_FORK=no valgrind --tool=memcheck --leak-check=yes -s ./s21_map_test

check_style:
	clang-format -n -style=google ./*.tpp
	clang-format -n -style=google ./*.h
	clang-format -n -style=google ./*/*.cpp
	clang-format -n -style=google ./*/*.tpp
	clang-format -n -style=google ./*/*.h

style:
	clang-format -i -style=google ./*.tpp
	clang-format -i -style=google ./*.h
	clang-format -i -style=google ./*/*.cpp
	clang-format -i -style=google ./*/*.tpp
	clang-format -i -style=google ./*/*.h

