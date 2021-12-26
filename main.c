#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"


void PrintGraph(pnode *head);
void BuildGraph(pnode *head, char** buffptr);
void DeleteGraph(pnode* head);

int main()
{
    static char buff[1000] = {'\0'};
    fgets(buff, 1000, stdin);
    char* c = buff;
    Node* list = NULL;
    do
    {
        if(*c=='A')
        {
            BuildGraph(&list, &c);
            if(*c !='\n' && *c!='\0')
            {
                c += 2;
            }
        }

    } while (*c!=EOF && *c!='\0' && *c!='\n');
    
    PrintGraph(&list);

    return 0;
}