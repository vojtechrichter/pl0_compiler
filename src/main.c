#include "logger.h"
#include "tokenization/scanner.h"

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
    printf("\tHello from PL/0 Compiler!\n\n");

    Scanner s = {0};
    Scanner *scanner = scanner_init(argv[1], &s);

    uint32_t *tokens = scanner_tokenize_source(scanner);
    /*
    for (int i = 0; i < scanner->src_size; i++) {
        printf("%d\n", tokens[i]);
    }
    */

    free(scanner->src_code);
    free(tokens);

    return 0;
}
