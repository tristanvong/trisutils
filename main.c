#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, const char *argv[])
{
    if (argc <= 1)
        return 0;
    
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
        //prob add some error messages? but idrc
        if(argc < 4 || argc > 4)
            return 0;

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

    return 0;
}
