#include "logger.h"

static inline void separate_stdout_from_build_info()
{
    printf("\n\t<---------------------------------------------------------->\n\n");
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        log_warning("Please provide source files you wish to compile.\n"); 
        exit(1);
    }

    printf("source file: %s\n", argv[1]);

    separate_stdout_from_build_info();

    printf("\tHello from PL/0 Compiler!\n");

    return 0;
}
