#!/bin/bash

scp /var/lib/gitlab-runner/builds/vyb5Cjrv/0/students/DO6_CICD.ID_356283/raylhigh_student.21_school.ru/DO6_CICD-1/src/cat/s21_cat raylhigh@10.10.0.2:/usr/local/bin/
scp /var/lib/gitlab-runner/builds/vyb5Cjrv/0/students/DO6_CICD.ID_356283/raylhigh_student.21_school.ru/DO6_CICD-1/src/grep/s21_grep raylhigh@10.10.0.2:/usr/local/bin/
ssh raylhigh@10.10.0.2 ls /usr/local/bin/

exit 0