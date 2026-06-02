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

    return 0;
}
