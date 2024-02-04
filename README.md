# 520-Assignments
This repository organizes homework for **EEP 520- Software Engineering for Embedded Applications**.

Introduction
---

- **Programming Language:** C/C++

- **Build Environment**
  - UNIX environment
  - bash shell
  - git
  - gnu C and C++ compiler
  - make build tool
  - GTest

Get Started
---
- **Docker**

Use pre-build images for this course:
```
docker pull klavins/ecep520:cppenv
```
Then run the container
```bash
docker run -v /path/to/EEP520_code_on_your_local_machine:/source -it klavins/ecep520:cppenv bash
```
to get a `bash` prompt that allows you to run commands within the "container environment".

You will initially be placed to the `/source` directory onto which the `-v` option to docker will have mounted the `/path/to/EE P590` directory in your host environment. This directory and its children are the only host directories available within the container environment.

- **Compile and Run**

Use gcc/g++ commands in `cppenv` bash shell.

> Compiling Tests and Linking Libraries:
```bash
cd fractions
g++ -c fraction.c -std=c++17
g++ -c unit_tests.c -std=c++17
g++ -c main.c -std=c++17
g++ -o test *.o fraction.h -lgtest -lpthread
```

Or use [make](https://www.gnu.org/software/make/). Create a Makefile for test and do

```bash
make
```

This will make two new directories, `bin` and `build`. The former will have the executable, test, in it. The latter will have all the `*.o` files. Then it builds and links everything.

You will normally just use the course Makefile and edit a few lines to tell make what files are part of your source code. We have made changes to the Makefile, by the way. You no longer need to add your source and header files, because we have changed the `HEADERS` and `SOURCES` definitions to:

```make
HEADERS     := $(wildcard *.h)
SOURCES     := $(wildcard *.c)
```
After compiling, we can run the test. To run the tests in `unit_tests.c`, simply do
```bash
./bin/test
```

Assignments
---

| HW | Topic | Solutions | Weeks | Date |
| :----: | :----: | :----: | :----: | :----: |
| 1 | Linux Commands / C Introduction | [hw1](https://github.com/OvertheBrain/520-Assignments/tree/main/hw_1) | Week1~2 | 2024.1.19 |
| 2 | Pointer and Memory / C Programming | [hw2](https://github.com/OvertheBrain/520-Assignments/tree/main/hw_2) | Week3 |2024.1.26 |
| 3 | Advanced Data Type | [hw3](https://github.com/OvertheBrain/520-Assignments/tree/main/hw_3/arrays) | Week4 | 2024.1.31 |
| 4 | C++ Programming: Class, Operator and Template | [hw4](https://github.com/OvertheBrain/520-Assignments/tree/main/hw_4) | Week4~5 | 2024.2.03 |
