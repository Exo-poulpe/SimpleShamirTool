CC = gcc 
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Wwrite-strings -Walloc-zero -Wparentheses -Wlarger-than=10000 -Wmissing-declarations -Wmissing-include-dirs -Wmissing-prototypes -fsanitize=address 
CFLAGS += -g -pedantic -fsanitize=address -fsanitize=leak -fsanitize=undefined
LDFLAGS = -lm
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
OBJECTS_TEST = $(patsubst %.c, %.o, $(wildcard tests/*.c))
OBJECTS_MUNIT = $(patsubst %.c, %.o, $(filter-out example.c , tests/munit/*.c))
OBJECTS_SRC := $(patsubst %.c, %.o, $(filter-out main.c, $(wildcard *.c)))


############# COMMAND HELP #############

# $(wildcard *.o) // Find all .o files
# $(SOURCES:.c=.o) // Compile with implicit compilation rules all .c

# $(patsubst %.c, %.o, $(wildcard *.o)) // Find all .c and compil with rules to .o
# pat(tern) subst(itution)

# $^ = all element
# $< = first element
# $@ = name of rules

########################################


PROG = Exe
TEST = test

all: $(PROG) $(TEST)

$(PROG): $(OBJECTS)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)

$(TEST): $(OBJECTS_SRC) $(OBJECTS_TEST) $(OBJECTS_MUNIT)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)
	@./$(TEST)


main.o : main.c  # Specifie rules main.o
tree.o : tree.h



# PHONY for function with no file generated
.PHONY: clean

clean :
	rm -f *.o $(PROG) $(TEST)

rebuild : clean $(PROG) $(TEST)