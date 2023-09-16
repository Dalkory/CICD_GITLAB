CFLAGS:=-Wall -Werror -Wextra -std=c11

GREP:=s21_grep

all: $(GREP)

$(GREP): s21_grep.c
	gcc $(CFLAGS) s21_grep.c -o $(GREP)

test: $(GREP)
	bash tests/run_tests.sh

style:
	clang-format -Werror -n *.c

leaks:
	leaks --atExit -- ./s21_grep -e int s21_grep.c -benst test_file/all_flag_tests/*

clean:
	rm $(GREP)

rebuild: clean all
