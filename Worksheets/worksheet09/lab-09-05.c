#include <stdio.h>
#include <string.h>

//remove spaces
void removeAllSpaces(char *input)
{
    int j = 0;
        
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (input[i] != ' ')
        {
            input[j++] = input[i];
        }
    }
    input[j] = '\0';
}
//seperate words
void printWordsSeparately(char *input)
{
    if (strcmp(input, "q") == 0) return;
    
    int len = strlen(input);
    
    int commaSeen = 0;
    for (int i = 0; i < len; i++)
    {
        if (input[i] == ',') 
        {
            commaSeen = 1;
            break;
        }
    }
    
    if (!commaSeen)
    {
        printf("Error: No comma in string.\n\n");
        return;
    }
    
    // Divide the string by a comma token
    char *word = strtok(input, ",");
    
    removeAllSpaces(word);
    printf("First word: %s\n", word);
    
    word = strtok(NULL, ",");
    removeAllSpaces(word);
    printf("Second word: %s\n", word);
    
    printf("\n");
}

int main()
{
    const int length = 50;
    char input[length];
    
    while (strcmp(input, "q") != 0)
    {
        printf("Enter input string:\n");
        
        // Read a line
        fgets(input, length, stdin);
        
        char *ptr = strchr(input, '\n');
        if (ptr) *ptr  = '\0';
        
        printWordsSeparately(input);
    }
    
    return 0;
}
