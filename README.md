## XNum's library hijack control demo

### Introduction

In this homework, my program is able to show the write/read and some important function arguments via a readable way, to run it, you can 

```
$ make test
```

or

```
$ make
$ wget http://your.url
```

### Features

In default, the program prints message on screen and with some colors, but because of the homework's requirement, the messages are redirect to a single file now. `mylib.h:21~26` shows the part controls filename, by define `ACTUAL_FILE_NAME` and redefine `OUTPUT_FILE`, messages stores to that file, but you will see some control code if opened by vim, the recommends way is:

```
cat debug.out
```

Also I did something to make it more readable, by gcc's atttibute trick, c++'s template and c++11's new typedef feature.

I only hijack some important function shows below:

1. fopen64
1. getaddrinfo
1. fread
1. fwrite
1. write
1. read
1. unlink
1. rename
1. SSL_write
1. SSL_read
