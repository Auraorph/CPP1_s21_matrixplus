CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11
SRCDIR=string_func/
TSTDIR=tests/
OBJDIR=obj/
SOURCES=$(wildcard $(SRCDIR)*.c)
TEST_SOURCES=$(wildcard $(TSTDIR)*.c) #test files
TEST_RESULT=test
OBJECTS=$(SOURCES:$(SRCDIR)%.c=$(OBJDIR)%.o)
TEST_OBJECTS=$(TEST_SOURCES:.c=.o)
RESULT=s21_string.a

OS := $(shell uname)
ifeq ($(OS),Linux)
	OPEN= xdg-open report/index.html
	CHECK_LIB = -lcheck -lsubunit -lm -lrt -lpthread -D_GNU_SOURSE
endif

ifeq ($(OS),Darwin)
	OPEN= open report/index.html
	CHECK_LIB = -lcheck
endif

all: clean $(RESULT)

test: $(TEST_OBJECTS) $(RESULT)
	$(CC) $(CFLAGS) $^ -o $(TEST_RESULT) $(CHECK_LIB)
	./$(TEST_RESULT)

clang:
	clang-format -style=Google -n *.c *.h $(SRCDIR)*.c $(SRCDIR)*.h $(TSTDIR)*.c $(TSTDIR)*.h

$(RESULT): $(OBJDIR) $(OBJECTS)
	ar -rcs $@ $(OBJECTS)

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) -c $(CFLAGS) $< -o $@

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@
	
gcov_report: $(TEST_SOURCES) $(SOURCES)
	$(CC) $(CFLAGS) --coverage $^ $(CHECK_LIB) -o $@
	chmod +x *
	./$@
	lcov -t "$@" -o $@.info --no-external -c -d .
	genhtml -o report/ $@.info
	$(OPEN)

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -rf $(RESULT) $(OBJECTS) $(TEST_OBJECTS) $(TEST_RESULT) $(OBJDIR) $(RESULTM) gcov_report* *.gc* report/ *.o

.PHONY: test clean all gcov_report $(RESULT)