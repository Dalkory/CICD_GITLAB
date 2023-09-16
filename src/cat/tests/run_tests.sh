#!/bin/bash

GREEN='\e[32m'
NC='\e[0m'
RED='\e[31m'
EXE="../s21_cat.c"

printf "${GREEN}-----RUNNING TESTS-----${NC}\n"

failed=0
i=1

# TEST 1
cat test.txt > a
gcc $EXE && ./a.out test.txt > b
result=$(diff a b)

if [[ $result -eq 0 ]]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
    ((failed++))
fi

((i++))

# TEST 2
cat -b test1.txt > a
gcc $EXE && ./a.out -b test1.txt > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
    ((failed++))
fi

((i++))

# # TEST 3
# cat -n test2.txt test.txt > a
# gcc $EXE && ./a.out -n test2.txt test.txt > b
# result=$(diff a b)

# if [ $? -eq 0 ]; then
#     printf " TEST #$i ${GREEN}PASSED${NC}\n"
# else
#     printf " TEST #$i ${RED}FAILED${NC}\n"
#     printf "$result"
#     ((failed++))
# fi

# ((i++))

# TEST 4
cat -s test3.txt > a
gcc $EXE && ./a.out -s test3.txt > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
    ((failed++))
fi

((i++))

# TEST 5
cat -t test.txt > a
gcc $EXE && ./a.out -t test.txt > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
    ((failed++))
fi

((i++))

# TEST 6
cat -e test.txt > a
gcc $EXE && ./a.out -e test.txt > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
    ((failed++))
fi

((i++))

# TEST 7
FILE=weirdo.txt
FLAGS=
cat $FILE > a
gcc $EXE && ./a.out $FILE > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
    ((failed++))
fi

((i++))

# TEST 8
FILE=weirdo.txt
FLAGS=-b
cat $FLAGS $FILE > a
gcc $EXE && ./a.out $FLAGS $FILE > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
    ((failed++))
fi

((i++))

# TEST 9
FILE=weirdo.txt
FLAGS=-n
cat $FLAGS $FILE > a
gcc $EXE && ./a.out $FLAGS $FILE > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
    ((failed++))
fi

((i++))

# TEST 10
FILE=weirdo.txt
FLAGS=-s
cat $FLAGS $FILE > a
gcc $EXE && ./a.out $FLAGS $FILE > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
    ((failed++))
fi




((i++))

# TEST 11
FILE=test6.txt
FLAGS=-b
cat $FLAGS $FILE > a
gcc $EXE && ./a.out $FLAGS $FILE > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
    ((failed++))
fi


((i++))

# TEST 12
FILE=test6.txt
FLAGS=-e
cat $FLAGS $FILE > a
gcc $EXE && ./a.out $FLAGS $FILE > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
    ((failed++))
fi


((i++))

# TEST 13
FILE=test6.txt
FLAGS=-n
cat $FLAGS $FILE > a
gcc $EXE && ./a.out $FLAGS $FILE > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
    ((failed++))
fi


((i++))

# TEST 14
FILE=test6.txt
FLAGS=-s
cat $FLAGS $FILE > a
gcc $EXE && ./a.out $FLAGS $FILE > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
    ((failed++))
fi


((i++))

# TEST 15
FILE=test6.txt
FLAGS=-t
cat $FLAGS $FILE > a
gcc $EXE && ./a.out $FLAGS $FILE > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
    ((failed++))
fi


((i++))

# TEST 16
FILE=test6.txt
FLAGS=-v
cat $FLAGS $FILE > a
gcc $EXE && ./a.out $FLAGS $FILE > b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
    ((failed++))
fi


printf " ${GREEN}-----DONE[$((i - failed))/$((i))]-----${NC}\n"

rm a.out a b


if ((failed > 0)); then
    exit 1
fi
