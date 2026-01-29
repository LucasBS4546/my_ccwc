#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <wchar.h>


int main(int argc, char *argv[])
{
    setlocale(LC_CTYPE, "");
    if (argc < 2)
    {
        printf("Usage: %s [FILE_NAME]\n", argv[0]);
        return 1;
    }
    
    // read args
    const char *filename = argv[argc-1];
    int count_bytes_enabled = 0; // -c
    int count_lines_enabled = 0; // -l
    int count_words_enabled = 0; // -w
    int count_chars_enabled = 0; // -m
    for (int i = 1; i < argc - 1; i++)
    {
        if (strcmp(argv[i], "-c") == 0) count_bytes_enabled = 1;
        else if (strcmp(argv[i], "-l") == 0) count_lines_enabled = 1;
        else if (strcmp(argv[i], "-w") == 0) count_words_enabled = 1;
        else if (strcmp(argv[i], "-m") == 0) count_chars_enabled = 1;
        else {
            printf("Error: Unrecognized argument %s\n", argv[i]);
            return 1;
        }
    }
    // default args if none are given: -c -l -w
    if (!count_bytes_enabled && !count_lines_enabled && !count_words_enabled && !count_chars_enabled)
    count_bytes_enabled = count_lines_enabled = count_words_enabled = 1;
    
    // opens file
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: Could not open file\n");
        return 1;
    }

    // starts counters
    int bytes = 0, lines = 0, words = 0, chars = 0;

    // reads file for bytes, lines and words counters
    if (count_bytes_enabled || count_lines_enabled || count_words_enabled)
    {
        int character, found_word_separator = 1;
        while((character = fgetc(file)) != EOF)
        {
            if (count_bytes_enabled) bytes++;
    
            if (count_lines_enabled && character == '\n') lines++;
    
            if (count_words_enabled)
            {
                int is_word_separator = isspace((unsigned char) character);
                if (found_word_separator && !is_word_separator)
                {
                    words++;
                    found_word_separator = 0;
                }
                else if (is_word_separator)
                {
                    found_word_separator = 1;
                }
            }
        }
        if (count_chars_enabled) rewind(file); // necessary for reopening of file in chars counting loop, if necessary
    }

    // reads file for chars counter (uses loop with encoding)
    if (count_chars_enabled)
    {
        wint_t wc;
        while ((wc = fgetwc(file)) != WEOF)
        {
            chars++;
        }
    }

    // output
    fclose(file);
    if (count_lines_enabled) printf("%d ", lines);
    if (count_words_enabled) printf("%d ", words);
    if (count_bytes_enabled) printf("%d ", bytes);
    if (count_chars_enabled) printf("%d ", chars);
    printf("%s\n", argv[argc - 1]);

    return 0;
}