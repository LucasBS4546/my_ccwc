#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

#define BLOCK_SIZE 512
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s [FILE_NAME]\n", argv[0]);
        return 1;
    }

    // read args
    const char *filename = argv[argc-1];
    int count_bytes = 0; // -c
    int count_lines = 0; // -l
    int count_words = 0; // -w
    int count_chars = 0; // -m
    for (int i = 1; i < argc - 1; i++)
    {
             if (strcmp(argv[i], "-c") == 0) count_bytes = 1;
        else if (strcmp(argv[i], "-l") == 0) count_lines = 1;
        else if (strcmp(argv[i], "-w") == 0) count_words = 1;
        else if (strcmp(argv[i], "-m") == 0) count_chars = 1;
           else {
                printf("Error: Unrecognized argument %s\n", argv[i]);
                return 1;
            }
    }

    // default if none are given: -c -l -w
    if (!count_bytes && !count_lines && !count_words && !count_chars)
        count_bytes = count_lines = count_words = 1;

    // check if file does not exists or cannot be accessed
    if (access(filename, F_OK) != 0){
        printf("Error: No access to file %s. Either create the file or grant access to run command.\n", argv[argc - 1]);
        return 1;
    }

    // output
    if (count_bytes)
    {
        FILE *file = fopen(filename, "rb");
        if (file == NULL)
        {
            printf("Error: Could not open file\n");
            return 1;
        }

        printf(""); // TODO
        fclose(file);
    }
    if (count_lines | count_words | count_chars)
    {
        FILE *file = fopen(filename, "r");
        if (file == NULL)
        {
            printf("Error: Could not open file\n");
            return 1;
        }

        if (count_lines)
        {
            printf(""); // TODO
        }
        if (count_words) 
        {
            printf(""); // TODO
        }
        if (count_chars)
        {
            printf(""); // TODO
        }
        fclose(file);
    }

    printf("%s\n", argv[argc - 1]);

    return 0;
}