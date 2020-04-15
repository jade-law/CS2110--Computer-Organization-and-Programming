CC = gcc
CHECK_LIBS = $(shell pkg-config --cflags --libs check)
CFILES = tests.c list.c suites/list_suite.c 
HFILES = list.h suites/test_utils.h
OFILES = suites/test_utils.o tests.o list.o suites/list_suite.o 

CFLAGS = -std=c99 -pedantic -Wall -Werror -Wextra -g \
         -Wstrict-prototypes -Wold-style-definition

.PHONY: default run-tests run-gdb run-valgrind clean ta-clean

default: run-tests

%.o: %.c $(HFILES)
	$(CC) $(CFLAGS) -c $< -o $@

list.o: list.c $(HFILES)
	$(CC) $(CFLAGS) -include suites/fakemalloc.h -c $< -o $@

-include sneakyboi.mak

hw9: 
	$(CC) main.c list.c $(CFLAGS) -o hw9

tests: $(OFILES)
	$(CC) $(CFLAGS) $^ -o $@ $(CHECK_LIBS)

run-tests: tests
	./tests $(TEST)

run-gdb: tests
	CK_FORK=no gdb --args ./tests $(TEST)

# To prevent leak false postives, tell check not to fork.
# See: http://check.sourceforge.net/doc/check_html/check_4.html#Finding-Memory-Leaks
run-valgrind: tests
	CK_FORK=no valgrind --quiet --leak-check=full --error-exitcode=1 --show-leak-kinds=all --errors-for-leak-kinds=all ./tests $(TEST)

clean:
	rm -rf tests hw9 $(filter-out suites/test_utils.o,$(OFILES)) *check*
