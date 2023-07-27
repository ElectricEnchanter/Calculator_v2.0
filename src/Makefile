CC=g++
FLAGS=-std=gnu++17 -Wall -Wextra -Werror

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
ifeq ($(OS), Darwin)
	@../build/SmartCalc_v2.app/Contents/MacOS/SmartCalc_v2
endif

gcov_report: test
	lcov --no-external --capture --directory  . --output-file coverage.info
	genhtml -o  report coverage.info
	open ./report/index.html

style:
	clang-format -n back/*.cc back/*.h
	clang-format -n front/*.cpp front/*.h

test: clean
	$(CC) $(FLAGS) ./back/Token.cc ./back/Calculator.cc calculator_tests.cc $(LIBS) && ./a.out

leaks: test
	$(CHECK_LEAKS) ./a.out

install: uninstall
	@mkdir -p ../build
	@qmake6 -o ../build/Makefile ./front/SmartCalc_v2.pro
	@make -C ../build 

ifneq ($(OS), Linux)
	@mkdir -p ~/Applications ; cp -r ./../build/SmartCalc_v2.app ~/Applications/SmartCalc_v2.app
endif

uninstall: clean
	@rm -rf ~/Applications/SmartCalc_v2.app

dist:
	@cd .. && tar -czvf SmartCalc_v2.0.tar src

dvi:
	@open dvi.html

clean:
	@rm -rf ../build ../.vscode a.out *.gcno *.gcda *.info coverage_report Token.dSYM Token report
