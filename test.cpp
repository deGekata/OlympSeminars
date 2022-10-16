#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

uint32_t strHashCode(char* str) {
    if (str == NULL) return 0;
    uint32_t hash = 123456;
    while (*str) {
        hash = ((hash << 5) + hash) ^ *(str++);
    }

    return hash;
}

int add(char** table, int index, char* number) {
    if (table[index][0] != 0)
        return 1;
    
    int n = strlen(number);

    for(size_t i = 0; i < n; ++i)
    {
        table[index][i] = number[i];
    }

    return 0;
}

int del(char** table, int index)
{
    if (table[index][0] == 0)
        return 1;

    for(size_t i = 0; i < 50; ++i)
        table[index][i] = 0;
    
    return 0;
}

int edit(char** table, int index, char* new_number)
{
    if(table[index][0] == 0)
        return 1;
    
    int n = strlen(new_number);

    for(size_t i = 0; i < 50; ++i)
        table[index][i] = 0;
    for(size_t i = 0; i < n; ++i)
        table[index][i] = new_number[i];
    
    return 0;
}

 int print(char** table, uint32_t index, char* name)
 {
     if (table[index][0] == 0)
        return 1;
    
    printf("%s ", name);

    for(size_t i = 0; i < 50; ++i)
    {
        if (table[index][i] == 0)
            break;
        printf("%c", table[index][i]);
    }
    printf("\n");
    return 0;
 }

int main()
{
    int n;
    scanf("%d", &n);

    const int table_size = 300007;
    const int max_strlen = 4098;
    char** table = (char**) malloc(table_size * sizeof(char*));
    // if (table == NULL)
    //     return 1;

    for(size_t i = 0; i < table_size; ++i)
    {
        table[i] = (char*) calloc(max_strlen, sizeof(char));
        // if (table[i] == NULL)
        //     return 1;
    }
       

    while(n--)
    {
        char* type = (char*) malloc(10 * sizeof(char));
        // if (type == NULL)
        //     return 1;
        
        scanf("%s", type);
        if (type[0] == 'A')
        {
            char* name = (char*) malloc(max_strlen * sizeof(char));
            char* number = (char*) malloc(max_strlen * sizeof(char));
            // if (name == NULL || number == NULL)
            //     return 1;

            scanf("%s %s", name, number);
            if (add(table, strHashCode(name) % table_size, number))
                printf("ERROR\n");

            free(name);
            free(number);
        }
        if (type[0] == 'D')
        {
            char* name = (char*) malloc(max_strlen * sizeof(char));
            // if (name == NULL)
            //     return 1;

            scanf("%s", name);
            if (del(table, strHashCode(name) % table_size))
                printf("ERROR\n");
            free(name);
        }
        if (type[0] == 'E')
        {
            char* name = (char*) malloc(max_strlen * sizeof(char));
            char* number = (char*) malloc(max_strlen * sizeof(char));
            // if (name == NULL || number == NULL)
            //     return 1;

            scanf("%s %s", name, number);
            if (edit(table, strHashCode(name) % table_size, number))
                printf("ERROR\n");
            free(name);
            free(number);
        }
        if (type[0] == 'P')
        {
            char* name = (char*) malloc(max_strlen * sizeof(char));
            // if (name == NULL)
            //     return 1;

            scanf("%s", name);
            if (print(table, strHashCode(name) % table_size, name))
                printf("ERROR\n");
            free(name);
        }
    }

    for(size_t i = 0; i < table_size; ++i)
        free(table[i]);
    free(table);

    return 0;
}