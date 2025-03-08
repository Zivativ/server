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
    char data[512];
    bool success;
} Data;





#endif