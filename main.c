#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <openssl/rand.h>

#define COMMANDS "coin compare dice discount help lower passphrase upper"
#define PROGRAM_NAME "trisutils"
#define ASCII_NUM_START 48

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

    if (strcmp(command, "passphrase") == 0)
    {
        /*  Thanks,
            cppreference dot com
            for providing the base of this code under CC-license.
        */
        /*  for now fine, should be stored somewhere better
            I think /usr/local/share/trisutils/eff_large_wordlist.txt is appropriate?
            Now that I think about it would need root/superuser rights,... maybe better to store it in home folder
        */
        const char *file_name = "eff_large_wordlist.txt";
        FILE* fp = fopen(file_name, "r");

        if (!fp)
        {
            perror("File opening failed.");
            return EXIT_FAILURE;
        }

        rewind(fp);
        int c, count, count_word, current_int, found_match, random_int;
        c = count = count_word = current_int = found_match = random_int = 0;
        char number_str[5];
        char number_str_random[5];
        char word_buffer[128]; /* this is my scuffed approach for now but I want to create a variable that scales see text below */

        for (int i = 0; i < 5; i++)
        {
            random_int = (int)random_uint(5) + 1;
            number_str_random[i] = ASCII_NUM_START + random_int;
        }

        int generated_int = atoi(number_str_random);
            
        while ((c = fgetc(fp)) != EOF)
        {
            /*
                note to self for later:

                File is structered like this:
                11111   word

                0. generate 5 random numbers
                1. take 5 numbers from EFF File put in a variable until whitespace
                2. check whether 5 numbers are equal to generated int from step 0
                2.1. if not, repeat step 1
                2.2. else, print each char to terminal

                DONE:
                    finding one singular word based on 5 generated nums
                TODO:
                    instead of printing to the terminal store the word in a variable, this way it is possible to strcpy it to the result variable each time (using strlen)
                        1. re-create the word variable each time
                        2. copy this word variable to a result variable that gets bigger each time
                    implement a way so that multiple words can be generated
                    implement a divisor variable that sits between words default would be a whitespace " "
            */
            
            if(!found_match && isdigit(c) && !isblank(c) && !isalpha(c) && c != '\n')
            {
                number_str[count] = c;
                count++;
            } else if (!found_match && isblank(c))
            {
                current_int = atoi(number_str);

                if (generated_int == current_int)
                    found_match = 1;

                count = 0;
                for (int i = 0; i < strlen(number_str); i++)
                    number_str[i] = ' ';
            }

            if (found_match && !isblank(c) && !isdigit(c) && isalpha(c))
            {
                /* word being build */
                printf("%c",c);
                word_buffer[count_word] = c;
                count_word++;
            }

            if (c == '\n' && found_match)
            {
                /* somehow put the word in a var and result string see above text for more info */
                printf("\n");
                break;
            }
        }
        
        if (ferror(fp))
        {
            puts("I/O error when reading.");
            return EXIT_FAILURE;
        } else if (feof(fp))
        {
            puts("End of file reached successfully.");
            return EXIT_SUCCESS;
        }
        
        fclose(fp);
        return EXIT_SUCCESS;
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
