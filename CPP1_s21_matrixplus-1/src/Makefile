CFLAG = --std=c++17 -Wall -Wextra -Werror -lstdc++ -lm 
SOURCES_ALL = $(wildcard ./*.cpp) $(wildcard ./helpers/*.cpp)
OBJ_LIBRARY := $(patsubst %.cpp, %.o, $(SOURCES_ALL))
TEST_FLAGS = -lgtest

all: s21_matrix_oop.a test

%.o: %.cpp 
	gcc $(CFLAG) -c $< -o $@

s21_matrix_oop.a: $(OBJ_LIBRARY)
	ar rc s21_matrix_oop.a $(OBJ_LIBRARY)
	ranlib s21_matrix_oop.a 
	rm *.o

test: s21_matrix_oop.a 
	gcc tests/matrix_test.cpp s21_matrix_oop.a $(TEST_FLAGS) $(CFLAG) -o test.out
	./test.out

check_style:
	clang-format -n -style=google *.cpp
	clang-format -n -style=google tests/*.cpp
	clang-format -n -style=google helpers/*.cpp
	clang-format -n -style=google *.h

style:
	clang-format -i -style=google *.cpp
	clang-format -i -style=google tests/*.cpp
	clang-format -i -style=google helpers/*.cpp
	clang-format -i -style=google *.h

leaks: clean s21_matrix_oop.a
	gcc tests/matrix_test.cpp s21_matrix_oop.a $(TEST_FLAGS) $(CFLAG) -o test.out
	CK_FORK=no valgrind --leak-check=full --tool=memcheck --trace-children=yes --track-origins=yes ./test.out

clean:
	rm -f *.o *.a *.gcno *.gcda *.info *.out *.gcov
	rm -f ./*/*.o
	rm -f ./*.o
	rm -rf ./report
