#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
//establishes commandline argument
int main(int argc, string argv[])
{
//if the commandline does not equal two, program prints guide and quits
    if (argc != 2)
    {
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
//if second input of commandline is not numerical prints guide and quits
    for (int i = 0, j = strlen(argv[1]); i < j; i++)
    {
        if (argv[1][i] < 48 || argv[1][i] > 57)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
//makes string into integer now declared as key
    int key = atoi(argv[1]);
//prompts user for plaintext
    string plaintext = get_string("plaintext: ");
    for (int x = 0, y = strlen(plaintext); x < y; x++)
    {
//checks each char to make sure it is alphabetical/lower case and then proceeds with formula
        if (isalpha(plaintext[x]) && islower(plaintext[x]))
        {
            plaintext[x] -= 97;
            plaintext[x] += key;
            plaintext[x] %= 26;
            plaintext[x] += 97;
        }
//checks each char to make sure it is alphabetical/upper case and then proceeds with formula
        else if (isalpha(plaintext[x]) && isupper(plaintext[x]))
        {
            plaintext[x] -= 65;
            plaintext[x] += key;
            plaintext[x] %= 26;
            plaintext[x] += 65;
        }
    }
//prints resulting ciphertext
    printf("ciphertext: %s\n", plaintext);
}

