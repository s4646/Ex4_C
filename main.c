#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"

void PrintGraph(pnode *head);
void BuildGraph(pnode *head, char **buffptr);
void DeleteGraph(pnode *head);
void DeleteNode(pnode* head, char** buffptr);

int main()
{
    char buff[1000] = {'\0'};
    fgets(buff, 1000, stdin);
    char *c = buff;
    Node *list = NULL;
    do
    {
        if (*c == 'A')
        {
            BuildGraph(&list, &c);
            if (*c != '\n' && *c != '\0')
            {
                c += 2;
            }
        }
        else if (*c == 'B')
        {
            InsertNode(&list, &c);
            if (*c != '\n' && *c != '\0')
            {
                c += 2;
            }
        }
        else if(*c=='D')
        {
            DeleteNode(&list, &c);
            if(*c !='\n' && *c!='\0')
            {
                c += 2;
            }
        }
        // else if (*c == 'S')
        // {
        //     char src = atoi((c + 1));
        //     char dest = atoi((c + 3));
        //     ShortestPath(list, src, dest);
        //     c = c + 6;
        // }
        else
        {
            if (*(c + 1) == ' ')
            {
                c += 2;
            }
            else
            {
                c++;
            }
        }

    } while (*c != EOF && *c != '\0' && *c != '\n');

    // ShortestPath(list, 2, 0);
    PrintGraph(&list);
    DeleteGraph(&list);

    return 0;
}
