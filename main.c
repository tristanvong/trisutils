#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define COMMANDS "coin dice compare help"
#define PROGRAM_NAME "trisutils"

void print_help()
{
    printf("Available commands: %s\n", COMMANDS);
    printf("Usage: %s [COMMAND]\n", PROGRAM_NAME);
}

int main(int argc, const char *argv[])
{
    if (argc <= 1)
    {
        print_help();
        return EXIT_FAILURE;
    }
    
    const char *command = argv[1];
    srand(time(NULL));

    if (strcmp(command, "coin") == 0)
    {
        int rand_num = rand() % 2;
        const char *heads_or_tails[2] = {"heads", "tails"};
        printf("%s\n", heads_or_tails[rand_num]);
    }

    if (strcmp(command, "compare") == 0)
    {
        if(argc < 4 || argc > 4)
        {
            printf("Usage: %s compare [text1] [text2]\n", PROGRAM_NAME);
            return EXIT_FAILURE;
        }

        const char *s1, *s2 = "";
        s1 = argv[2];
        s2 = argv[3];
        if (strcmp(s1, s2) == 0)
        {
            printf("true\n");
        } else
        {
            printf("false\n");
        }
    }

    if (strcmp(command, "dice") == 0)
    {
        int rand_num, die_faces;
        die_faces = 6;
        if (argc == 2)
        {
            rand_num = (rand() % die_faces) + 1;
            printf("%d\n", rand_num);
        } else if (argc == 3)
        {
            die_faces = atoi(argv[2]);
            rand_num = (rand() % die_faces) + 1;
            printf("%d\n", rand_num);
        } else if (argc > 3)
        {
            printf("Usage: %s dice [optional size]\n", PROGRAM_NAME);
            return EXIT_FAILURE;
        }
    }

    if (strcmp(command, "help") == 0)
    {
        print_help();
    }

    return EXIT_SUCCESS;
}
