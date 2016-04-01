#include <stdio.h>

#ifndef DEBUG_CTRL_H
#define DEBUG_CTRL_H

#define DEBUG 1
#define INFO  2
#define WARN  3
#define ERROR 4

#define OUTPUT_FILE stderr

#define NONE "\033[m"
#define RED "\033[0;32;31m"
#define LIGHT_RED "\033[1;31m"
#define GREEN "\033[0;32;32m"
#define LIGHT_GREEN "\033[1;32m"
#define BLUE "\033[0;32;34m"
#define LIGHT_BLUE "\033[1;34m"
#define DARY_GRAY "\033[1;30m"
#define CYAN "\033[0;36m"
#define LIGHT_CYAN "\033[1;36m"
#define PURPLE "\033[0;35m"
#define LIGHT_PURPLE "\033[1;35m"
#define BROWN "\033[0;33m"
#define YELLOW "\033[1;33m"
#define LIGHT_GRAY "\033[0;37m"
#define WHITE "\033[1;37m"

#define dprintf(inputLV,format,...)			    \
        do { if((inputLV)>=0) {		            \
                if(inputLV==DEBUG)              \
                    fprintf(OUTPUT_FILE,LIGHT_GREEN);\
                if(inputLV==INFO)              \
                    fprintf(OUTPUT_FILE,LIGHT_BLUE);\
                if(inputLV==WARN)              \
                    fprintf(OUTPUT_FILE,YELLOW);\
                if(inputLV==ERROR)              \
                    fprintf(OUTPUT_FILE,LIGHT_RED);\
                fprintf(OUTPUT_FILE,"[%5s] %10s:%3d %s() # " format NONE ,#inputLV,__FILE__,__LINE__,__func__,##__VA_ARGS__); 	\
            if(inputLV>=ERROR)exit(1);          \
        } } while(0)

#endif
