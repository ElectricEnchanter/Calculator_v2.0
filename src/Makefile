CC=g++
FLAGS=-std=gnu++17 -Wall -Wextra -Werror
FLAGS_GCOV =-fprofile-arcs --coverage

OS=$(shell uname)
ifeq ($(OS), Linux)
  LIBS=--coverage -lgtest -lpthread 
  CHECK_LEAKS=valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all --track-origins=yes --log-file=log.txt
else
  LIBS=--coverage -lgtest
  CHECK_LEAKS= leaks -atExit -- 
endif


all: install run

run:
	build/SmartCalc_v2.app/Contents/MacOS/SmartCalc_v2

gcov_report: test
	lcov --no-external --capture --directory  . --output-file coverage.info
	genhtml -o  report coverage.info
	open ./report/index.html

style:
	cp ../assets/.clang-format .
	clang-format -i *.cc
	clang-format -n *.cc
	rm .clang-format

test: clean
	$(CC) $(FLAGS) Token.cc calculator_tests.cc $(LIBS) && ./a.out

leaks: test
	$(CHECK_LEAKS) ./a.out

install: uninstall
	mkdir -p build
	cd build; qmake6 ../calculator/SmartCalc_v2.pro; make > /dev/null 2>&1
	mkdir -p ~/Applications ; cp -r build/SmartCalc_v2.app ~/Applications/SmartCalc_v2.app
	
uninstall: clean
	rm -rf build
	rm -rf ~/Applications/SmartCalc_v2.app

dist:
	cd .. && tar -czvf SmartCalc_v2.0.tar src

dvi:
	open dvi.html

clean:
	rm -rf build* ../.vscode a.out *.gcno *.gcda *.info coverage_report Token.dSYM Token report
