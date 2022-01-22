

int main(int argc, const char *argv[]) {
  // This should cause an error
   asm volatile("hlt");
    while(1);
}
