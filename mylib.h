#ifndef MYLIB_H
#define MYLIB_H

#include <cstdio>
#include <cstdlib>

#include <unistd.h>
#include <sys/param.h>
#include <fcntl.h>
#include <dlfcn.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "debugCtrl.h"

// special code for redirct
FILE* output_file = NULL;
#undef OUTPUT_FILE 
#define OUTPUT_FILE output_file
#define ACTUAL_FILE_NAME "debug.out"
// special code for redirct

#include <openssl/ssl.h>

#define GLIBC_SO "libc.so.6"
#define OPENSSL_SO "libssl.so.1.0.0"

#ifndef F_GETPATH
#define F_GETPATH   (1024 + 7)
#endif

#endif
