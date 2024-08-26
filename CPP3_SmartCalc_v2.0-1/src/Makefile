CC=g++
CFLAGS=-Wall -Werror -Wextra --std=c++17 
GCOV=-fprofile-arcs -ftest-coverage
GTEST=-lgtest -pthread
NAME=s21_calc
APP=view
DIST=Distribut_SmartCalc

all: build

install: build
	mv build/$(APP) /home/sonikxx/my_app/

uninstall:
	rm -rf /home/sonikxx/my_app/$(APP)

clean:
	rm -rf *.a *.gcda *.gcno *.o *.info *_test report build $(DIST).tgz doc.aux doc.log doc.dvi doc.toc

tests: clean
	$(CC) tests/test.cpp model/model.cpp $(CFLAGS) $(GTEST) -o $(NAME)_test
	./$(NAME)_test

dvi: 
	open doc.md

dist: 
	rm -rf $(DIST)/
	mkdir $(DIST)/
	cp -r Makefile main.cpp view controller model $(DIST)
	tar cf $(DIST).tgz $(DIST)/ 
	rm -rf $(DIST)/

build: clean
	rm -rf build
	mkdir build
	cd ./build/ && qmake6  ../view/ && make 

gcov_report:
	$(CC) tests/test.cpp model/model.cpp $(CFLAGS) $(GCOV) $(GTEST) -o $(NAME)_test
	./$(NAME)_test
	lcov  -t "$(NAME)_test" -o $(NAME)_test.info --no-external -c -d .  
	genhtml -o report $(NAME)_test.info
	open report/index.html
	rm -rf *.gcda *.gcno

leaks: tests
	CK_FORK=no valgrind --tool=memcheck --leak-check=yes -s ./$(NAME)_test

style:
	clang-format -i -style=google *.cpp
	clang-format -i -style=google tests/*.cpp
	clang-format -i -style=google controller/*.cpp controller/*.h
	clang-format -i -style=google model/*.cpp model/*.h
	clang-format -i -style=google view/*.cpp view/*.h