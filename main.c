#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <openssl/rand.h>

#define COMMANDS "coin compare dice discount help lower upper"
#define PROGRAM_NAME "trisutils"

void print_help()
{
    printf("Available commands: %s\n", COMMANDS);
    printf("Usage: %s [-options] COMMAND\n", PROGRAM_NAME);
}

/*
    Thanks, George Koehler
    https://stackoverflow.com/a/31282121 */
/* Random integer in [0, limit) */
unsigned int random_uint(unsigned int limit) {
    union {
        unsigned int i;
        unsigned char c[sizeof(unsigned int)];
    } u;

    do {
        if (!RAND_bytes(u.c, sizeof(u.c))) {
            fprintf(stderr, "Can't get random bytes!\n");
            exit(1);
        }
    } while (u.i < (-limit % limit)); /* u.i < (2**size % limit) */
    return u.i % limit;
}

int main(int argc, const char *argv[])
{
    if (argc <= 1)
    {
        print_help();
        return EXIT_FAILURE;
    }
    
    const char *command = argv[1];

    if (strcmp(command, "coin") == 0)
    {
        int rand_num = (int)(random_uint(2));
        const char *heads_or_tails[2] = {"heads", "tails"};
        printf("%s\n", heads_or_tails[rand_num]);
    }

    if (strcmp(command, "compare") == 0)
    {
        if(argc < 4 || argc > 5)
        {
            printf("Usage: %s compare [-i|--case-ignore] text1 text2\n", PROGRAM_NAME);
            return EXIT_FAILURE;
        }

        char *s1, *s2;
        s1 = (char*)argv[2];
        s2 = (char*)argv[3];

        if (argc == 5 &&(strcmp(argv[2], "-i") == 0 || strcmp(argv[2], "--case-ignore") == 0))
        {
            s1 = (char*)argv[3];
            s2 = (char*)argv[4];

            for (int i = 0; i < strlen(s1); i++)
            {
                s1[i] = tolower(s1[i]);
            }

            for (int i = 0; i < strlen(s2); i++)
            {
                s2[i] = tolower(s2[i]);
            }
        }
        
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

        if (argc == 3)
        {
            die_faces = atoi(argv[2]);
            if (die_faces == 0)
                return EXIT_FAILURE;

        } else if (argc > 3)
        {
            printf("Usage: %s dice [optional_size]\n", PROGRAM_NAME);
            return EXIT_FAILURE;
        }
        
        rand_num = (int)(random_uint(die_faces) + 1);
        printf("%d\n", rand_num);
    }

    if (strcmp(command, "discount") == 0)
    {
        if (argc < 4 || argc > 4)
        {
            printf("Usage: %s discount original_price discount_in_percentage\n", PROGRAM_NAME);
            return EXIT_FAILURE;
        }
        
        double original_price, discounted_price, discount_percent;
        original_price = atof(argv[2]);
        discount_percent = atof(argv[3]);
        discounted_price = original_price - ((discount_percent / 100) * original_price);
        printf("%.2f\n", discounted_price);
    }
    
    if (strcmp(command, "help") == 0)
    {
        print_help();
    }

    if (strcmp(command, "lower") == 0)
    {
        if (argc < 3 || argc > 3)
        {
            printf("Usage: %s lower text\n", PROGRAM_NAME);
            return EXIT_FAILURE;
        }

        char *user_input = (char*) argv[2];
        for (int i = 0; i < strlen(user_input); i++)
        {
            user_input[i] = tolower(user_input[i]);
        }
        printf("\n%s\n", user_input);
    }

    if (strcmp(command, "upper") == 0)
    {
        if (argc < 3 || argc > 3)
        {
            printf("Usage: %s upper text\n", PROGRAM_NAME);
            return EXIT_FAILURE;
        }

        char *user_input = (char*) argv[2];
        for (int i = 0; i < strlen(user_input); i++)
        {
            user_input[i] = toupper(user_input[i]);
        }
        printf("\n%s\n", user_input);
    }

    return EXIT_SUCCESS;
}
