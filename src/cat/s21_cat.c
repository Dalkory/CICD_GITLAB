#include <ctype.h>
#include <getopt.h>
#include <stdio.h>

struct flags {
  int b;
  int v;
  int e;
  int n;
  int s;
  int t;
};

void cat_flags(int argc, char* argv[], struct flags* flag);
void open_file(int argc, char* argv[], struct flags flag);
void use_flags(FILE* fptr, struct flags flag);

int main(int argc, char* argv[]) {
  struct flags flag = {0};

  cat_flags(argc, argv, &flag);
  open_file(argc, argv, flag);

  return 0;
}

void cat_flags(int argc, char* argv[], struct flags* flag) {
  struct option long_flags[] = {{"number-nonblank", 0, 0, 'b'},
                                {"number", 0, 0, 'n'},
                                {"squeeze-blank", 0, 0, 's'},
                                {0, 0, 0, 0}};
  int options = 0, long_index = 0;

  while ((options = getopt_long(argc, argv, "benstvET", long_flags,
                                &long_index)) != -1) {
    switch (options) {
      case 'b':
        flag->b = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      case 'e':
        flag->v = 1;
        flag->e = 1;
        break;
      case 'E':
        flag->e = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 't':
        flag->v = 1;
        flag->t = 1;
        break;
      case 'T':
        flag->t = 1;
        break;
      default:
        break;
    }
  }
  if (flag->b == 1) {
    flag->n = 0;
  }
}

void open_file(int argc, char* argv[], struct flags flag) {
  int argv_index = 1;

  while (*argv[argv_index] == '-') {
    argv_index++;
  }

  for (; argv_index < argc; argv_index++) {
    FILE* fptr = NULL;
    if ((fptr = fopen(argv[argv_index], "r")) == NULL) {
      printf("cat: %s: No such file or directory\n", argv[argv_index]);
    } else {
      use_flags(fptr, flag);
      fclose(fptr);
    }
  }
}

void use_flags(FILE* fptr, struct flags flag) {
  char ch = 1;
  int prev_char = 1;
  int lines_count = 1;
  int new_line = 1;

  while ((ch = fgetc(fptr)) != EOF) {
    if (flag.s) {
      if (ch == '\n') {
        prev_char++;
        if (prev_char >= 3) {
          continue;
        }
      } else {
        prev_char = 0;
      }
    }
    if (flag.b) {
      if (new_line) {
        if (ch != '\n') {
          printf("%6d\t", lines_count++);
          new_line = 0;
        }
      }
      if (ch == '\n') {
        new_line = 1;
      }
    }
    if (flag.n) {
      if (new_line) {
        printf("%6d\t", lines_count++);
        new_line = 0;
      }
      if (ch == '\n') {
        new_line = 1;
      }
    }
    if (flag.e) {
      if (ch == '\n') {
        printf("%c", '$');
      }
    }
    if (flag.t) {
      if (ch == '\t') {
        printf("%c", '^');
        ch = 'I';
      }
    }
    if (flag.v) {
      if (!isprint(ch) && ch != 10 && ch != 9) {
        printf("^");
        if (ch == 127)
          ch -= 64;
        else
          ch += 64;
      }
    }
    printf("%c", ch);
  }
}
