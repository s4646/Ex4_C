#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"

void PrintGraph(pnode *head);
void BuildGraph(pnode *head, char **buffptr);
void DeleteGraph(pnode *head);

int main()
{
    // char buff[1000] = {'\0'};
    // fgets(buff, 1000, stdin);
    char buff[1000] = "A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 n 3 T 3 2 1 3 S 2 0";
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
        if (*c == 'B')
        {
            InsertNode(&list, &c);
            if (*c != '\n' && *c != '\0')
            {
                c += 2;
            }
        }
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

    ShortestPath(list->next->next, 1, 3);
    PrintGraph(&list);
    DeleteGraph(&list);

    return 0;
}