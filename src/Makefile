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


all: pognal

pognal:
	$(CC) $(FLAGS) -g Token.cc && ./a.out

run: install
	build/Calculator.app/Contents/MacOS/Calculator

gcov_report: test

	lcov --no-external --capture --directory  . --output-file coverage.info
	genhtml -o  report coverage.info
	open ./report/index.html

style:
	cp ../assets/.clang-format .
	clang-format -i *.c
	clang-format -n *.c
	rm .clang-format

test: clean
	$(CC) $(FLAGS) Token.cc calculator_tests.cc $(LIBS) && ./a.out


install: uninstall
	mkdir -p build
	cd build; cmake ../; make
	mkdir -p ~/Applications ; cp -r build/output/amd64/third_party/SmartCalc.app ~/Applications/Calculator.app
	
uninstall: clean
	rm -rf build
	rm -rf ~/Applications/Calculator.app

dist:
	cd .. && tar -czvf SmartCalc_v1.0.tar src

dvi:
	open dvi.html

clean:
	rm -rf build* ../.vscode a.out *.gcno *.gcda *.info coverage_report Token.dSYM Token report
