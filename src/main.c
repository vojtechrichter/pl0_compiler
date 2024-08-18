#include <stdio.h>

static inline void separate_stdout_from_build_info()
{
    printf("\n\t<---------------------------------------------------------->\n\n");
}

int main()
{
    separate_stdout_from_build_info();

    printf("\tHello from PL/0 Compiler!\n");

    return 0;
}