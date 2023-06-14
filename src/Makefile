CC=g++
FLAGS =-Wall -Wextra -Werror  -std=c++17
FLAGS_GCOV =-fprofile-arcs --coverage

OS=$(shell uname)
ifeq ($(OS), Linux)
  LIBS=-lcheck -lsubunit -lpthread -lrt -lm -g 
else
  LIBS=-lcheck 
endif

all: pognal

pognal:
	$(CC) $(FLAGS) Token.cc && ./a.out

run: install
	build/Calculator.app/Contents/MacOS/Calculator

tests:
	checkmk clean_mode=1 SmartCalc_v1.0_test.check > SmartCalc_v1.0_test.c
	$(CC) $(FLAGS_GCOV) SmartCalc_v1.0_test.c SmartCalc_v1.0.c $(LIBS)
	./a.out

gcov_report: tests
	gcovr --html-details coverage.html
	open coverage.html

style:
	cp ../assets/.clang-format .
	clang-format -i *.c
	clang-format -n *.c
	rm .clang-format

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
	rm -rf build* ../.vscode a.out
