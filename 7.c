#include <stdio.h>
#include <sys/mman.h>

void honest_func_1(){
    printf ("It's over, Anakin! I have the high ground!\n");
    return;
}
void honest_func_2(){
    printf ("You underestimate my power!\n");
    return;
}
int hacker_func(){
    mprotect (&honest_func_1 - (unsigned long long ) &honest_func_1%0x1000, 0x1000, PROT_READ | PROT_WRITE | PROT_EXEC);
    *((char*)&honest_func_1) = 0xeb;
    *((char*)(&honest_func_1 + 1)) = &honest_func_2 - &honest_func_1 - 2;
    return 0;
}

int main()
{
    honest_func_1();
    honest_func_2();
    hacker_func();
    honest_func_1();

    return 0;
}
