#ifndef PL0_COMPILER_TOKENIZATION_SCANNER_H
#define PL0_COMPILER_TOKENIZATION_SCANNER_H

#include "token_types.h"

#include <inttypes.h>
#include <assert.h>

#define CURRCHAR(s) \
    s->src_code[s->idx]

typedef struct Scanner {
    char *src_code;
    size_t src_size;
    size_t idx;
    uint8_t current_char;
};

Scanner *scanner_init(Scanner *scanner)
{
    scanner->src_code = NULL;
    scanner->src_size = 0;
    scanner->idx = 0;
    scanner->current_char = CURRCHAR(scanner);

    return scanner;
}

void scanner_advance(Scanner *scanner)
{
    assert(scanner->idx + 1 < scanner->src_size);

    scanner->idx += 1;
    scanner->current_char = scanner->src_code[scanner->idx];
}

void scanner_advance_by(Scanner *scanner, size_t pos_from_current_idx)
{
    assert(scanner->idx + pos_from_current_idx < scanner->src_size);

    scanner->idx += pos_from_current_idx;
    scanner->current_char = CURRCHAR(scanner);
}

uint8_t scanner_peek_next(Scanner *scanner)
{
    assert(scanner->idx + 1 < scanner->src_size);

    return scanner->src_code[scanner->idx + 1];
}

uint8_t scanner_peek_next_by(Scanner *scanner, size_t pos_from_current_idx)
{
    assert(scanner->idx + pos_from_current_idx < scanner->src_size);

    return scanner->src_code[scanner->idx + pos_from_current_idx];
}

uint8_t scanner_peek_prev(Scanner *scanner)
{
    assert(scanner->idx - 1 > 0);

    return scanner->src_code[scanner->idx - 1];
}

uint8_t scanner_peek_prev_by(Scanner *scanner, size_t pos_from_current_idx)
{
    assert(scanner->idx - pos_from_current_idx > 0);

    return scanner->src_code[scanner->idx -= pos_from_current_idx];
}

void scanner_return_to_prev(Scanner *scanner)
{
    assert(scanner->idx - 1 > 0);

    scanner->idx -= 1;
    scanner->current_char = CURRCHAR(scanner);
}

void scanner_return_by(Scanner *scanner, size_t pos_from_current_idx)
{
    assert(scanner->idx - pos_from_current_idx > 0);

    scanner->idx -= pos_from_current_idx;
    scanner->current_char = CURRCHAR(scanner);
}

void scanner_reset(Scanner *scanner)
{
    scanner->idx = 0;
    scanner->current_char = CURRCHAR(scanner);
}

#endif // PL0_COMPILER_TOKENIZATION_SCANNER_H