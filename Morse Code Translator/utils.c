#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void process_error(char *msg) 
{
    printf("%s %s\n", STR_ERROR, msg);
    exit(0);
}