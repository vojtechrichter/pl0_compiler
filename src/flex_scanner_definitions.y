%{
#include <stdio.h>
int number_of_lines = 0, number_of_chars = 0;
%}

%%

\n number_of_lines += 1; number_of_chars += 1;
. number_of_chars += 1;

%%

int yywrap(){
    return 1;
}
int main(){
    yylex();
    printf("Number of lines: %d", number_of_lines);
    printf("Number of chars: %d", number_of_chars);

    return 0;
}