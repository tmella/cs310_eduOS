

int main(int argc, const char *argv[]) {
    printf_c(0x02,"\nThis is a my user program!!\n");

    int *val = malloc(sizeof(int)*7);
    for(int i = 0; i<5; i++) {
        *val = i;
        val++;
    }
    for(int i = 5; i>0; i--) {
        printf("\nint value at i=%d is %d", i, *val);
        val--;
    }
}


