CFLAGS=-g -c -Wall -Wextra -Werror -std=c++17 -pedantic
FLAGS=-Wall -Wextra -Werror -std=c++17 -pedantic
GTEST=-lgtest -lgtest_main -pthread
ASAN=#-fsanitize=address
COVER=-fprofile-arcs -ftest-coverage


all: test

clean:
	rm -f test1
	rm -f test2
	rm -f test3
	rm -f test4
	rm -f test5
	rm -f test6
	rm -f test7
	rm -f test8
	rm -f *.a *.o
	rm -f *.info *.gcda *.gcno *.gcov
	rm -rf coverage

test: clean
	g++ $(FLAGS) $(ASAN) $(GTEST) $(COVER) ./tests/multiset_test.cc -o test1
	g++ $(FLAGS) $(ASAN) $(GTEST) $(COVER) ./tests/set_test.cc -o test2
	g++ $(FLAGS) $(ASAN) $(GTEST) $(COVER) ./tests/vector_test.cc -o test3
	g++ $(FLAGS) $(ASAN) $(GTEST) $(COVER) ./tests/array_test.cc -o test4
	g++ $(FLAGS) $(ASAN) $(GTEST) $(COVER) ./tests/queue_test.cc -o test5
	g++ $(FLAGS) $(ASAN) $(GTEST) $(COVER) ./tests/stack_test.cc -o test6
	g++ $(FLAGS) $(ASAN) $(GTEST) $(COVER) ./tests/map_test.cc -o test7
	g++ $(FLAGS) $(ASAN) $(GTEST) $(COVER) ./tests/list_test.cc -o test8

	./test1
	./test2
	./test3
	./test4
	./test5
	./test6
	./test7
	./test8

gcov_report:
	geninfo . -b . -o ./coverage.info --no-external
	genhtml coverage.info -o ./coverage
	open coverage/index.html

lint:
	clang-format -n *.h

leaks:
	leaks -atExit -- ./test1
	leaks -atExit -- ./test2
	leaks -atExit -- ./test3
	leaks -atExit -- ./test4
	leaks -atExit -- ./test5
	leaks -atExit -- ./test6
	leaks -atExit -- ./test7
	leaks -atExit -- ./test8
