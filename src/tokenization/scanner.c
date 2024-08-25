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

uint32_t resolve_token(uint8_t c, Scanner *scanner)
{
    switch (c) {
        case 'v': {
            scanner_advance(scanner);
            if (CURRCHAR(scanner) == 'a') {
                scanner_advance(scanner);
                if (CURRCHAR(scanner) == 'r') {
                    return TOKEN_VAR;
                }
            }
        }

        case ',': {
            return TOKEN_COMMA;
        }

        case ';': {
            return TOKEN_SEMICOLON;
        }

        // TODO: make a functionality for matching multi-character tokens, since
        // this is horendous
        case 'b': {
            scanner_advance(scanner);
            if (CURRCHAR(scanner) == 'e') {
                scanner_advance(scanner);
                if (CURRCHAR(scanner) == 'g') {
                    scanner_advance(scanner);
                    if (CURRCHAR(scanner) == 'i') {
                        scanner_advance(scanner);
                        if (CURRCHAR(scanner) == 'n') {
                            return TOKEN_BEGIN;
                        }
                    }
                }
            }
        }

        case ':': {
            scanner_advance(scanner);
			if (CURRCHAR(scanner) == '=') {
				return TOKEN_ASSIGNMENT;
			}
        }

		case 'w': {
			scanner_advance(scanner);
			if (CURRCHAR(scanner) == 'h') {
				scanner_advance(scanner);
				if (CURRCHAR(scanner) == 'i') {
					scanner_advance(scanner);
					if (CURRCHAR(scanner) == 'l') {
						scanner_advance(scanner);
						if (CURRCHAR(scanner) == 'e') {
							return TOKEN_WHILE;
						}
					}
				}
			}
		}

		case 'd': {
            scanner_advance(scanner);
            if (CURRCHAR(scanner) == 'o') {
                return TOKEN_DO;
            }
		}

        case '<': {
            return TOKEN_LESSTHAN;
        }

        case '>': {
            return TOKEN_GREATERTHAN;
        }

        case '*': {
            return TOKEN_STAR;
        }

        case '/': {
            return TOKEN_FSLASH;
        }

        case '+': {
            return TOKEN_PLUS;
        }

        case '-': {
            return TOKEN_MINUS;
        }

        case '=': {
            return TOKEN_EQUAL;
        }

        case 'e': {
            scanner_advance(scanner);
            if (CURRCHAR(scanner) == 'n') {
                scanner_advance(scanner);
                if (CURRCHAR(scanner) == 'd') {
                    return TOKEN_END;
                }
            }
        }

        case '.': {
            return TOKEN_DOT;
        }

        case '(': {
            return TOKEN_LPAREN;
        }

        case ')': {
            return TOKEN_RPAREN;
        }

        case 'i': {
            scanner_advance(scanner);
            if (CURRCHAR(scanner) == 'f') {
                return TOKEN_IF;
            }
        }

        case 't': {
            scanner_advance(scanner);
            if (CURRCHAR(scanner) == 'h') {
                scanner_advance(scanner);
                if (CURRCHAR(scanner) == 'e') {
                    scanner_advance(scanner);
                    if (CURRCHAR(scanner) == 'n') {
                        return TOKEN_THEN;
                    }
                }
            }
        }

        case 'o': {
            scanner_advance(scanner);
            if (CURRCHAR(scanner) == 'd') {
                scanner_advance(scanner);
                if (CURRCHAR(scanner) == 'd') {
                    return TOKEN_ODD;
                }
            }
        }

        // TODO: when the case fails to match in one of the middle if statements for example,
        // the next case will receive the nth character from the processed one, which
        // skips characters. FIX: either only peek forward, or return back n number of
        // characters, after each non-matched if condition
        case 'p': {
            scanner_advance(scanner);
            if (CURRCHAR(scanner) == 'r') {
                scanner_advance(scanner);
                if (CURRCHAR(scanner) == 'o') {
                    scanner_advance(scanner);
                    if (CURRCHAR(scanner) == 'c') {
                        scanner_advance(scanner);
                        if (CURRCHAR(scanner) == 'e') {
                            scanner_advance(scanner);
                            if (CURRCHAR(scanner) == 'd') {
                                scanner_advance(scanner);
                                if (CURRCHAR(scanner) == 'u') {
                                    scanner_advance(scanner);
                                    if (CURRCHAR(scanner) == 'r') {
                                        scanner_advance(scanner);
                                        if (CURRCHAR(scanner) == 'e') {
                                            return TOKEN_PROCEDURE;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        default: {
            // TODO: check if can be ident, otherwise unknown
            return TOKEN_UNKNOWN;
        }
    }
}

uint32_t *scanner_tokenize_source(Scanner *scanner)
{
    uint32_t *tokens = (uint32_t *)malloc(scanner->src_size * sizeof(uint32_t));

    while (scanner->idx != (scanner->src_size - 1)) {
        tokens[scanner->idx] = resolve_token(scanner->current_char, scanner);
    }

    return tokens;
}
