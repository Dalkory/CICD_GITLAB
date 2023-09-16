#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM 999999
#define STR_BUFFER 1000
struct flags {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int empty_line;
};

void get_flags(int argc, char* argv[], struct flags* flag, char* arg);
void e_arg(char* optarg, int* e_count, char* arg, struct flags*);
void f_arg(char* optarg, int* e_count, char* ef_arg, struct flags*);
void open_files(int argc, char* argv[], char* arg, struct flags flag);
void regmagic(char* argv[], char* arg, FILE* fp, struct flags flag,
              int files_count);

int main(int argc, char* argv[]) {
  struct flags flag = {0};

  if (argc > 1) {
    char arg[NUM] = {0};
    get_flags(argc, argv, &flag, arg);
    if (!flag.e && !flag.f) {
      if (!*argv[optind]) argv[optind] = ".";
      strcat(arg, argv[optind]);
      optind += 1;
    }
    open_files(argc, argv, arg, flag);
  }
  return 0;
}

void get_flags(int argc, char* argv[], struct flags* flag, char* arg) {
  int ch = 0;
  char* string = "e:ivclnhsf:o";
  int e_count = 0;

  while ((ch = getopt_long(argc, argv, string, NULL, NULL)) != -1) {
    switch (ch) {
      case 'e':
        flag->e = 1;
        e_arg(optarg, &e_count, arg, flag);
        break;
      case 'i':
        flag->i = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      case 'c':
        flag->c = 1;
        break;
      case 'l':
        flag->l = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 'h':
        flag->h = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 'f':
        flag->f = 1;
        f_arg(optarg, &e_count, arg, flag);
        break;
      case 'o':
        flag->o = 1;
        break;
      case '?':
        break;
      default:
        break;
    }
  }
  if (flag->empty_line) flag->o = 0;
}

void e_arg(char* optarg, int* e_count, char* arg, struct flags* flag) {
  if (*e_count) {
    char* ch = "|";
    strcat(arg, ch);
  }
  if (!*optarg) {
    optarg = ".";
    flag->empty_line++;
  }
  strcat(arg, optarg);
  *e_count += 1;
}

void f_arg(char* optarg, int* e_count, char* arg, struct flags* flag) {
  FILE* fp_f = NULL;
  int empty_counter = flag->empty_line;

  if ((fp_f = fopen(optarg, "r")) == NULL) {
    printf("grep: %s: No such file or directory\n", optarg);
  } else {
    while (!feof(fp_f)) {
      if (*e_count) {
        char* ch = "|";
        strcat(arg, ch);
      }

      size_t len = strlen(arg);
      size_t new_len = 0;

      fgets(arg + len, STR_BUFFER, fp_f);
      char* nch = strrchr(arg, '\n');
      if (nch) *nch = '\0';
      new_len = strlen(arg);
      if (new_len == len) {
        flag->empty_line++;
        char* all = ".";
        strcat(arg, all);
      }
      *e_count += 1;
    }
    fclose(fp_f);
    if (arg[strlen(arg) - 1] == '.') {
      if ((flag->empty_line - empty_counter) == 1)
        flag->empty_line = empty_counter;
      arg[strlen(arg) - 1] = '\0';
      arg[strlen(arg) - 1] = '\0';
    }
  }
}

void open_files(int argc, char* argv[], char* arg, struct flags flag) {
  FILE* fp = NULL;
  int files_count = argc - optind;

  for (; optind < argc; optind++) {
    if ((fp = fopen(argv[optind], "r")) == NULL) {
      if (!flag.s) {
        printf("grep: %s: No such file or directory\n", argv[optind]);
      }
    } else {
      regmagic(argv, arg, fp, flag, files_count);
      fclose(fp);
    }
  }
}

void regmagic(char* argv[], char* arg, FILE* fp, struct flags flag,
              int files_count) {
  regex_t reg;
  regmatch_t pmatch[1] = {0};
  size_t nmatch = 1;

  int res = 1;
  char str[STR_BUFFER];
  size_t total_lines = 1;
  int match_lines = 0;
  int i_opt = 0;

  if (flag.i) i_opt = REG_ICASE;
  res = regcomp(&reg, arg, REG_EXTENDED | i_opt);
  while (!feof(fp)) {
    if (fgets(str, STR_BUFFER, fp)) {
      res = regexec(&reg, str, nmatch, pmatch, 0);
      if (flag.v) res = res ? 0 : 1;
      if (!res) {
        if (!flag.c && !flag.l) {
          int new_line_o_counter = 1;
          if (files_count > 1 && !flag.h) {
            printf("%s:", argv[optind]);
          }
          if (flag.n) {
            printf("%zu:", total_lines);
          }
          if (flag.o && !flag.v) {
            new_line_o_counter = 0;
            char* ptr = str;
            while ((!res) && pmatch[0].rm_eo != pmatch[0].rm_so) {
              printf("%.*s\n", (int)(pmatch[0].rm_eo - pmatch[0].rm_so),
                     ptr + pmatch[0].rm_so);
              ptr += pmatch[0].rm_eo;
              res = regexec(&reg, ptr, nmatch, pmatch, REG_NOTBOL);
            }
          }
          if (!flag.o || flag.v) {
            printf("%s", str);
          }
          if ((str[strlen(str) - 1]) != '\n' && new_line_o_counter) {
            printf("\n");
          }
        }
        match_lines++;
      }
      total_lines++;
    }
  }
  if (flag.c) {
    if (files_count > 1 && !flag.h) {
      printf("%s:", argv[optind]);
    }
    if (flag.l && match_lines) {
      printf("1\n");
    } else {
      printf("%d\n", match_lines);
    }
  }
  if (flag.l && match_lines) printf("%s\n", argv[optind]);
  regfree(&reg);
}
