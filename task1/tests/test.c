#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"

void replace_new_lines(const char *given_str, char *result_buf) {
    size_t given_str_len = strlen(given_str);
    size_t j = 0;
    for (size_t i = 0; i < given_str_len; ++i, ++j) {
        if (given_str[i] == '\n') {
            result_buf[j] = '\\';
            ++j;
            result_buf[j] = 'n';
        } else {
            result_buf[j] = given_str[i];
        }
    }
}

int test_wc(const char *test_name, const char *command, const char *expected) {
    char actual[96] = {0};
    char line[32];

    FILE *pipe = popen(command, "r");
    if (!pipe) {
        perror("popen");
        return 1;
    }

    size_t idx = 0;
    while (fgets(line, sizeof(line), pipe)) {
        int line_size = strlen(line);
        memcpy(actual + idx, line, line_size);
        idx += line_size;
    }

    if (pclose(pipe) == -1) {
        perror("pclose");
        return 1;
    }

    bool pass = strcmp(actual, expected) == 0;

    if (pass) {
        printf("[" ANSI_COLOR_GREEN "PASS" ANSI_COLOR_RESET "] %-20s\n",
               test_name);
    } else {
        char actual_oneline[96] = {0};
        char expected_oneline[96] = {0};
        replace_new_lines(actual, actual_oneline);
        replace_new_lines(expected, expected_oneline);

        printf("[" ANSI_COLOR_RED "FAIL" ANSI_COLOR_RESET
               "] %-20s | Expected: `%s` \t Actual: `%s`\n",
               test_name, expected_oneline, actual_oneline);
    }

    return !pass;
}

int main(void) {
    int ok = 0;

    ok |= test_wc("Basic pipe", "printf 'Hello,\nworld!\n' | ./my-wc",
                  "2\n2\n14\n");
    ok |= test_wc("File input", "./my-wc tests/the_laughing_heart.txt",
                  "20\n98\n491\n");
    ok |= test_wc("Empty pipe", "printf '' | ./my-wc", "0\n0\n0\n");

    return ok;
}
