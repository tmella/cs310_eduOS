
#include "stdlib.h"
#include "memory.h"

int main(int argc, const char *argv[]) {
    char *t = "Random ust prints this value %d";
    int *val = malloc(sizeof(int)*7);
    *val = 8;
    printf(t, *val);
}
