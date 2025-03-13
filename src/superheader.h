#ifndef SUPERHEADER_H_ICNLUDED
#define SUPERHEADER_H_ICNLUDED





#include "exfiles/netlib.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "exfiles/tinycthread/tinycthread.h"



typedef struct _Data {
    int version;
    bool success;
    int type;
    char data[512];
} Data;

#define fail(message, ...) printf("[-] " message, ##__VA_ARGS__)
#define pass(message, ...) printf("[+] " message, ##__VA_ARGS__)
#define info(message, ...) printf("[!] " message, ##__VA_ARGS__)



#endif