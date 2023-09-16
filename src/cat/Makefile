CFLAGS:=-Wall -Werror -Wextra -std=c11

CAT:=s21_cat

all: $(CAT)

$(CAT): s21_cat.c
	gcc $(CFLAGS) s21_cat.c -o $(CAT)

test: $(CAT)
	cd ./tests && bash run_tests.sh

style:
	clang-format --Werror -n *.c

clean:
	rm $(CAT)

rebuild: clean all
