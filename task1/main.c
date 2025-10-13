#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

int main(int argc, char **argv)
{
    int result = 1;

    FILE *fin = (argc > 1) ? fopen(argv[1], "r") : stdin;
    if (!fin) {
        perror("Can't open file");
        return 2;
    }

    int line_counter = 0;
    int word_counter = 0;
    int char_counter = 0;

    bool in_word = false;
    for (int ch = fgetc(fin) ; (ch != EOF) ; ch = fgetc(fin))
    {
        ++char_counter;

        if (ch == '\n') // end line
            ++line_counter;

        if (isspace(ch) && in_word) // space char
        {
            ++word_counter;
            in_word = false;
            continue;
        }

        in_word = true;
    }

    if (in_word)
        ++word_counter;

    if (ferror(fin))
    {
        perror("I/O error when reading");
        return 3;
    }
    else if (feof(fin))
    {
        result = EXIT_SUCCESS;
    }

    fclose(fin);

    printf("%d\n%d\n%d\n", line_counter, word_counter, char_counter);

    return result;
}
