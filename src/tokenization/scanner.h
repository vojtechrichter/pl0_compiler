#ifndef PL0_COMPILER_TOKENIZATION_SCANNER_H
#define PL0_COMPILER_TOKENIZATION_SCANNER_H

#include "token_types.h"
#include "../logger.h"

#include <inttypes.h>
#include <assert.h>
#include <stddef.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define CURRCHAR(s) \
    s->src_code[s->idx]

typedef struct Scanner Scanner;
struct Scanner
{
    char *src_code;
    size_t src_size;
    size_t idx;
    uint8_t current_char;
};

Scanner *scanner_init(const char *file_path, Scanner *scanner);
void scanner_advance(Scanner *scanner);
void scanner_advance_by(Scanner *scanner, size_t pos_from_current_idx);
uint8_t scanner_peek_next(Scanner *scanner);
uint8_t scanner_peek_next_by(Scanner *scanner, size_t pos_from_current_idx);
uint8_t scanner_peek_prev(Scanner *scanner);
uint8_t scanner_peek_prev_by(Scanner *scanner, size_t pos_from_current_idx);
void scanner_return_to_prev(Scanner *scanner);
void scanner_return_by(Scanner *scanner, size_t pos_from_current_idx);
void scanner_reset(Scanner *scanner);
char **scanner_tokenize_source(Scanner *scanner);

#endif // PL0_COMPILER_TOKENIZATION_SCANNER_H
