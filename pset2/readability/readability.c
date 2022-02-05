#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)

{
//request for input from user
    string text = get_string("Read to me: ");
//gets an array of floats which define the contents of the text
    float content[3] = {0, 1, 0};
//loop to count elements of text as they appear
    for (int s = 0, n = strlen(text); s < n; s++)
    {
        if (text[s] >= 'A' && text[s] <= 'z')
        {
            content[0]++;
        }
        if (text[s] == ' ')
        {
            content[1]++;
        }
        if (text[s] == '?' || text[s] == '!' || text[s] == '.')
        {
            content[2]++;
        }
    }
//formula to get average of letter per 100 words
    float L = content[0] / content[1] * 100;
//formula to get average of sentences per 100 words
    float S = content[2] / content[1] * 100;
//Coleman-Liau index
    int index = round(0.0588 * L - 0.296 * S - 15.8);
//indicates grade level
    if (index > 1 && index < 16)
    {
        printf("Grade %i\n", index);
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }

}