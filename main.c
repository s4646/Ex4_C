#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"

// void PrintGraph(pnode *head);
// void BuildGraph(pnode *head, char **buffptr);
// void DeleteGraph(pnode *head);
// void DeleteNode(pnode *head, char **buffptr);

int main()
{
	static char buff[10000000] = {'\0'};
	fgets(buff, 10000000, stdin);
	// char *buff = "A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 n 3 T 3 2 1 3 S 2 0";
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
		else if (*c == 'D')
		{
			DeleteNode(&list, &c);
			if (*c != '\n' && *c != '\0')
			{
				c += 2;
			}
		}
		else if (*c == 'S')
		{
			char src = atoi((c + 1));
			char dest = atoi((c + 3));
			double dist = ShortestPath(list, src, dest);
			printf("dist from %d to %d is: %.3f\n", src, dest, dist);
			c += 2;
			c = c + LenOfNum(GetNum(buff))+1;
			c = c + LenOfNum(GetNum(buff))+1;
		}
		else if (*c == 'T')
		{
			c += 2;
			int size = GetNum(c);
			c += LenOfNum(size) + 1;
			int *parameters = handle_tsp_input(c, size);
			int tsp_result = TSP(list, size, parameters);
			printf("TSP: %d\n", tsp_result);
			// free(parameters);
			c += 2;
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

	PrintGraph(&list);
	DeleteGraph(&list);

	return 0;
}
