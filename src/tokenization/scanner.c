#include "scanner.h"

size_t get_src_file_size(const char *file_path)
{
    struct stat buffer;
    int status = stat(file_path, &buffer);
    if (status == 0) {
        return(buffer.st_size);
    }

    handle_err("Couldn't get file size of source file %s\n", file_path);
    return((size_t)NULL);
}

void read_src_file(const char *file_path, char *buffer)
{
    size_t file_size = get_src_file_size(file_path);

     int fd = open(file_path, O_RDWR, 0666);
     size_t bytes_read = read(fd, buffer, file_size);
     if (bytes_read == -1) {
         handle_err("Failed to read the source file %s\n", file_path);
     }
}

Scanner *scanner_init(const char *file_path, Scanner *scanner)
{
    read_src_file(file_path, scanner->src_code);
    scanner->src_size = get_src_file_size(file_path);
    scanner->idx = 0;
    scanner->current_char = CURRCHAR(scanner);

    return(scanner);
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

char **scanner_tokenize_source(Scanner *scanner)
{
    return (char **)0;
}
