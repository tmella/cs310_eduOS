

int main(int argc, const char *argv[]) {
    int i = 0;
    while(1) {
        i++;
        if(i == 2147483646) {
            i = 0;
        }
    }
}