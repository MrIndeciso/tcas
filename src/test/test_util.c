#include <stdio.h>

#include "test_util.h"

void psuccess(const char *msg) {
    printf("\033[0;32m");
    printf("[OK] %s", msg);
    printf("\033[0m\n");
}

void perror(const char *msg) {
    printf("\033[0;31m");
    printf("[FAIL] %s", msg);
    printf("\033[0m\n");
}
