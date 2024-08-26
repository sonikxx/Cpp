all: tests

install: clean
	cd view/ && cmake . && make
	cp -R view/3DViewer_v2 ~/Desktop/

uninstall:
	rm -rf ~/Desktop/3DViewer_v2
	rm -rf ~/Desktop/options.json

tests: clean
	cd test_dir && make && ./test.out

gcov_report: clean
	cd test_dir && make gcov_report && ./gcov_report
	lcov  -t "gcov_report" -o gcov_report.info --no-external -c -d .  
	genhtml -o report gcov_report.info
	open report/index.html
	cd test_dir && rm -rf *.gcda *.gcno

dist: clean
	rm -rf ../Archive/
	mkdir ../Archive/
	cp -r ../src ../Archive/
	tar -C ../ -czvf Archive.tgz Archive/
	mv Archive.tgz ~/Desktop/
	rm -rf ../Archive/

dvi:
	open doxygen/html/index.html

clean:
	cd test_dir && make clean
	rm -rf *.a *.o .clang-format *.out gcov_report* *.info report */*.gcno */*.gcda tests.out.dSYM
	rm -rf view/3DViewer_v2
	rm -rf view/3DViewer_v2_autogen
	rm -rf view/CMakeCache.txt
	rm -rf view/CMakeFiles
	rm -rf view/Makefile
	rm -rf view/cmake_install.cmake
	rm -rf view/.qmake.stash
	rm -rf view/*.o
	rm -rf view/moc_*
	rm -rf view/.qtc_clangd
	rm -rf ~/Desktop/Archive.tgz
	rm -rf tests_sanitiz*
	rm -rf *.gcda
	rm -rf test_dir/gcov_report test_dir/gcov_report.info test_dir/test.o test_dir/report
	# rm -rf ~/Desktop/options.json
