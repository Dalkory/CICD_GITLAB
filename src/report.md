# Basic CI/CD

Разработка простого **CI/CD** для проекта *SimpleBashUtils*. Сборка, тестирование, развертывание.

## Contents
1. [Настройка gitlab-runner](#part-1-настройка-gitlab-runner)  
2. [Сборка](#part-2-сборка)  
3. [Тест кодстайла](#part-3-тест-кодстайла)   
4. [Интеграционные тесты](#part-4-интеграционные-тесты)  
5. [Этап деплоя](#part-5-этап-деплоя)  
6. [Дополнительно. Уведомления](#part-6-дополнительно-уведомления)

### Part 1. Настройка **gitlab-runner**

##### Скачать и установить на виртуальную машину **gitlab-runner**

![Alt text](src/screen/image.png)

##### Запустить **gitlab-runner** и зарегистрировать его для использования в текущем проекте (*DO6_CICD*)

![Alt text](src/screen/image-1.png)

переустаналиваем gitlab-runner с использованием команд :

- `sudo curl -L --output /usr/local/bin/gitlab-runner "https://gitlab-runner-downloads.s3.amazonaws.com/latest/binaries/gitlab-runner-linux-amd64"`

- `sudo chmod +x /usr/local/bin/gitlab-runner`

- `sudo useradd --comment 'GitLab Runner' --create-home gitlab-runner --shell /bin/bash`

- `sudo gitlab-runner install --user=gitlab-runner --working-directory=/home/gitlab-runner`

- `sudo gitlab-runner start`

- `sudo systemctl enable --now gitlab-runner`

### Part 2. Сборка

##### В файле _gitlab-ci.yml_ добавить этап запуска сборки через мейк файл из проекта _C2_

![Alt text](src/screen/image-3.png)

##### Файлы, полученные после сборки (артефакты), сохранять в произвольную директорию со сроком хранения 30 дней.

![Alt text](src/screen/image-4.png)

### Part 3. Тест кодстайла

#### Написать этап для **CI**, который запускает скрипт кодстайла (*clang-format*):

![Alt text](src/screen/image-7.png)

##### В пайплайне отобразить вывод утилиты *clang-format*

![Alt text](src/screen/image-2.png)

### Part 4. Интеграционные тесты

#### Написать этап для **CI**, который запускает ваши интеграционные тесты из того же проекта:

![Alt text](src/screen/image-8.png)

##### В пайплайне отобразить вывод, что интеграционные тесты успешно прошли / провалились

![Alt text](src/screen/image-6.png)

### Part 5. Этап деплоя

#### Написать этап для **CD**, который "разворачивает" проект на другой виртуальной машине:

![bash](src/screen/image-10.png)

##### Написать bash-скрипт, который при помощи **ssh** и **scp** копирует файлы, полученные после сборки (артефакты), в директорию */usr/local/bin* второй виртуальной машины

![Alt text](src/screen/image-11.png)

#### Деплой прошёл успешно, файлы появились в нужной папке на второй машине:  

![Alt text](src/screen/image-16.png)

### Part 6. Дополнительно. Уведомления

#### Напишем @botfather, чтобы создать бота и получить его токен:
![Alt text](src/screen/image-12.png)

#### Добавим по вызову скрипта `notify.sh` после каждой стадии:
![Alt text](src/screen/image-14.png)

#### Содержимое скрипта `notify.sh`:  
![Alt text](src/screen/image-13.png)

#### Пушим, проверяем работу:  
![Alt text](src/screen/image-15.png)

