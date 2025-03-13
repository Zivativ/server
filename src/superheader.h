#ifndef SUPERHEADER_H_ICNLUDED
#define SUPERHEADER_H_ICNLUDED





#include "exfiles/netlib.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdbool.h>




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