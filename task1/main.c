#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define	ERROR_UNKNOWN  EXIT_FAILURE
#define	ERROR_FILEOPEN EXIT_FAILURE + 1
#define	ERROR_IOERROR  EXIT_FAILURE + 2
#define	ERROR_INTERNAL EXIT_FAILURE + 3

const char * InternalErrorMsg = NULL;

/*
    Purpose:
        Adds to the values of line_counter, word_counter, and char_counter based on the text read from stream.

    Result:
        Returns EXIT_SUCCESS on successful completion. Otherwise, returns an error code.

    Notes:
        - if the return value is not EXIT_SUCCESS, the values of line_counter, word_counter, and char_counter are undefined.
        - if the return value is ERROR_INTERNAL, see InternalErrorMsg for a description of the error.
*/
int fwc_impl(FILE* stream, int* line_counter, int* word_counter, int* char_counter)
{
    bool in_word = false;

    int ch;
    while ((ch = fgetc(stream)) != EOF)
    {
        ++(*char_counter);

        if (ch == '\n')
        {
            ++(*line_counter);
        }

        if (!isspace(ch))
        {
            in_word = true;
            continue;
        }

        if (in_word)
        {
            ++(*word_counter);
            in_word = false;
        }
    }

    if (in_word)
        ++(*word_counter);

    if (feof(stream))
        return EXIT_SUCCESS;

    if (ferror(stream))
        return ERROR_IOERROR;

    InternalErrorMsg = "fgetc returned EOF, but feof and ferror are not true.";
    return ERROR_INTERNAL;
}

int main(int argc, char **argv)
{
    int line_count = 0;
    int word_count = 0;
    int char_count = 0;
    int result;

    FILE *fin = (argc > 1) ? fopen(argv[1], "r") : stdin;
    if (!fin) {
        result = ERROR_FILEOPEN;
    }
    else
    {
        result = fwc_impl(fin, &line_count, &word_count, &char_count);
        fclose(fin);
    }

    switch (result)
    {
    case EXIT_SUCCESS:
        printf("%d\n%d\n%d\n", line_count, word_count, char_count);
        break;
    case ERROR_FILEOPEN:
        perror("Can't open file");
        break;
    case ERROR_IOERROR:
        perror("I/O error when reading");
        break;
    case ERROR_INTERNAL:
        printf("Internal error: %s\n", InternalErrorMsg);
        break;
    default:
        printf("Unknown error\n");
    }

    return result;
}
