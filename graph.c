#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "graph.h"

Node *GetNode(pnode *head, int num)
{
	pnode *temp = head;
	while (*temp != NULL && (*temp)->node_num != num)
	{
		temp = &((*temp)->next);
	}
	return *temp;
}

int GetNum(char *buff)
{
	char num[6] = {'\0'};
	int i = 0;
	while ((*(buff + 1) != ' ' && *(buff + 1) != '\n') && i < 6)
	{
		num[i] = *(buff++);
		i++;
	}
	num[i] = *buff;
	return atoi(num);
}

int LenOfNum(int num)
{
	if (num == 0)
	{
		return 1;
	}
	int i = 0;
	while (num > 0)
	{
		num = num / 10;
		i++;
	}
	return i;
}

void PrintEdges(pedge head)
{
	pedge temp = head;
	while (temp != NULL)
	{
		printf("Edge's destinstion: %d, weight: %d\n", temp->endpoint->node_num, temp->weight);
		temp = temp->next;
	}
}

void PrintGraph(pnode *head)
{
	pnode *temp = head;
	if (*temp == NULL)
	{
		printf("Empty Graph\n");
		return;
	}

	while ((*temp)->next != NULL)
	{
		printf("Node's ID: %d, next is %d\n", (*temp)->node_num, (*temp)->next->node_num);
		PrintEdges((*temp)->edges);
		temp = &((*temp)->next);
	}
	printf("Node's ID: %d\n", (*temp)->node_num);
	PrintEdges((*temp)->edges);
}

void DeleteGraph(pnode *head)
{
	if (*head == NULL)
		return;

	pnode *ntemp = head;
	pedge *etemp = NULL;
	pnode nprev = NULL;
	pedge eprev = NULL;
	// remove nodes
	while (*ntemp != NULL)
	{

		etemp = &((*ntemp)->edges);
		// remove edges of node
		while (*etemp != NULL)
		{
			eprev = *etemp;
			etemp = &((*etemp)->next);
			free(eprev);
		}
		nprev = *ntemp;
		ntemp = &((*ntemp)->next);
		free(nprev);
	}
}

void BuildGraph(pnode *head, char **buffptr)
{
	char *buff = *buffptr;
	// delete the previous graph if exists
	DeleteGraph(head);

	// create nodes for the new graph
	buff += 2;
	int counter = 0;
	// head = (pnode*)malloc(GetNum(buff)*sizeof(pnode));
	pnode *nptr = head;

	while (counter < GetNum(buff))
	{
		(*nptr) = (pnode)malloc(sizeof(Node));
		if ((*nptr) == NULL)
		{
			printf("malloc failed.");
			exit(0);
		}
		(*nptr)->node_num = counter;
		(*nptr)->edges = NULL;
		(*nptr)->next = NULL;
		(*nptr)->tag = 0;
		(*nptr)->weight = 0;
		nptr = &((*nptr)->next);
		counter++;
	}

	// add edges to the graph
	while (*(buff + LenOfNum(GetNum(buff)) + 1) != 'A' && *(buff + LenOfNum(GetNum(buff)) + 1) != 'B' && *(buff + LenOfNum(GetNum(buff)) + 1) != 'D' && *(buff + LenOfNum(GetNum(buff)) + 1) != 'S' && *(buff + LenOfNum(GetNum(buff)) + 1) != 'T')
	{
		// if reached end of input
		if (*(buff + 1) == '\0' || *(buff + 1) == '\n')
		{
			buff++;
			break;
		}
		buff += LenOfNum(GetNum(buff)) + 1;
		// get node of given ID
		if (*buff == 'n')
		{
			buff += 2;
			nptr = head;
			while ((*nptr)->node_num != GetNum(buff))
			{
				nptr = &((*nptr)->next);
			}
		}

		pedge *eptr = &((*nptr)->edges);

		// add edges to node
		while (*(buff + LenOfNum(GetNum(buff)) + 1) >= '0' && *(buff + LenOfNum(GetNum(buff)) + 1) <= '9')
		{
			*eptr = (pedge)malloc(sizeof(Edge));
			if ((*eptr) == NULL)
			{
				printf("malloc failed.");
				exit(0);
			}
			(*eptr)->next = NULL;

			// add edge's destination
			buff += LenOfNum(GetNum(buff)) + 1;

			(*eptr)->endpoint = GetNode(head, GetNum(buff));

			// add edge's weight
			buff += LenOfNum(GetNum(buff)) + 1;

			(*eptr)->weight = GetNum(buff);
			eptr = &((*eptr)->next);
		}
	}
	*buffptr = buff;
}

void InsertNode(pnode *head, char **buffptr)
{
	char *buff = *buffptr;

	pnode *nptr = head;
	// if node does not exist, go to end of the list
	while (*nptr != NULL)
	{
		// if node already exist, remove its out edges
		if ((*nptr)->node_num == GetNum(buff + 2))
		{
			pedge *etemp = &((*nptr)->edges);
			pedge eprev = NULL;

			while (*etemp != NULL)
			{
				eprev = *etemp;
				etemp = &((*etemp)->next);
				free(eprev);
			}
			(*nptr)->edges = NULL;
			break;
		}
		nptr = &((*nptr)->next);
	}

	// add node to the list
	// if at the end of the list, malloc a new node
	if (*nptr == NULL)
	{
		*nptr = (pnode)malloc(sizeof(Node));
		if ((*nptr) == NULL)
		{
			printf("malloc failed.");
			exit(0);
		}
		buff += 2;
		(*nptr)->node_num = GetNum(buff);
		(*nptr)->next = NULL;
	}
	// else, modify existing node
	else
	{
		buff += 2;
		(*nptr)->node_num = GetNum(buff);
	}

	// add edges to node
	while (*(buff + LenOfNum(GetNum(buff)) + 1) != 'A' && *(buff + LenOfNum(GetNum(buff)) + 1) != 'B' && *(buff + LenOfNum(GetNum(buff)) + 1) != 'D' && *(buff + LenOfNum(GetNum(buff)) + 1) != 'S' && *(buff + LenOfNum(GetNum(buff)) + 1) != 'T')
	{
		if (*(buff + LenOfNum(GetNum(buff)) + 1) == '\n' || *(buff + LenOfNum(GetNum(buff)) + 1) == '\0')
		{
			break;
		}
		pedge *eptr = &((*nptr)->edges);

		while (*(buff + LenOfNum(GetNum(buff)) + 1) >= '0' && *(buff + LenOfNum(GetNum(buff)) + 1) <= '9')
		{
			*eptr = (pedge)malloc(sizeof(Edge));
			if ((*eptr) == NULL)
			{
				printf("malloc failed.");
				exit(0);
			}
			(*eptr)->next = NULL;

			// add edge's destination
			buff += LenOfNum(GetNum(buff)) + 1;

			(*eptr)->endpoint = GetNode(head, GetNum(buff));

			// add edge's weight
			buff += LenOfNum(GetNum(buff)) + 1;

			(*eptr)->weight = GetNum(buff);
			eptr = &((*eptr)->next);

			// if reached end of input
			if (*(buff + LenOfNum(GetNum(buff))) == '\0' || *(buff + LenOfNum(GetNum(buff))) == '\n')
			{
				buff++;
				*buffptr = buff;
				return;
			}
		}
	}
	*buffptr = buff;
}

void DeleteNode(pnode *head, char **buffptr)
{
	char *buff = *buffptr;
	buff += 2;
	pnode *nptr = head;
	pedge *eptr = NULL;
	pedge eprev = NULL;
	int index = GetNum(buff);

	// remove relevant edges in each node
	while (*nptr != NULL)
	{
		if ((*nptr)->node_num == index)
		{
			eptr = &((*nptr)->edges);
			while (*eptr != NULL)
			{
				eprev = *eptr;
				eptr = &((*eptr)->next);
				free(eprev);
			}
			nptr = &((*nptr)->next);
			continue;
		}
		eptr = &((*nptr)->edges);
		// remove edges of node
		while (*eptr != NULL)
		{
			// if relevant edge is head of the list
			if ((*eptr)->endpoint == ((*nptr)->edges)->endpoint && (*eptr)->endpoint->node_num == index)
			{
				eprev = *eptr;
				(*nptr)->edges = (*nptr)->edges->next;
				free(eprev);
				continue;
			}
			// if relevant edge is found
			if ((*eptr)->endpoint->node_num == index)
			{
				pedge temp = *eptr;
				eprev->next = (*eptr)->next;
				free(temp);
				eptr = &(eprev->next);
				continue;
			}
			eprev = *eptr;
			eptr = &((*eptr)->next);
		}
		nptr = &((*nptr)->next);
	}

	// remove node
	nptr = head;
	pnode prev = NULL;
	while ((*nptr) != NULL)
	{
		if ((*nptr)->node_num == index)
		{
			break;
		}
		prev = *nptr;
		nptr = &((*nptr)->next);
	}
	// if node is head, start list at the next node
	if ((*head)->node_num == index)
	{
		if ((*head)->next == NULL)
		{
			free(*head);
			*head = NULL;
		}
		else
		{
			pnode temp = *nptr;
			*head = (*head)->next;
			free(temp);
		}
	}
	else
	{
		pnode temp = (*nptr)->next;
		free(*nptr);
		prev->next = temp;
	}
	*buffptr = buff;
}

// an add for the dlikstra
void d_add(node_list list_tail, pnode node)
{
	l_node *newNode = (l_node *)malloc(sizeof(l_node));
	if (newNode == NULL)
	{
		printf("malloc failed.");
		exit(0);
	}

	if (newNode == NULL)
	{
		printf("Couldnt allocate memory, shutting down!");
		exit(1);
	}

	newNode->next = NULL;
	newNode->value = node;
	list_tail->next = newNode;
}

node_list d_gethead(node_list list_head)
{
	if (list_head == NULL)
	{
		return NULL;
	}
	else
	{
		node_list ret = list_head;
		return ret;
	}
}

pnode get_node(pnode list, int id)
{
	pnode temp = list;
	while (temp != NULL && temp->node_num != id)
	{
		temp = temp->next;
	}

	return temp;
}

double ShortestPath(pnode head, int src, int dest)
{
	// init weights and tags
	pnode temp = head;
	while (temp != NULL)
	{
		temp->tag = 0;
		temp->weight = INT_MAX;
		temp = temp->next;
	}

	// create a list for the nodes
	pnode srcNode = get_node(head, src);
	srcNode->weight = 0;

	node_list list_head = (node_list)malloc(sizeof(l_node));
	if (list_head == NULL)
	{
		printf("malloc failed.");
		exit(0);
	}
	list_head->next = NULL;
	list_head->value = srcNode;
	node_list list_tail = list_head;

	// main loop
	while (list_head != NULL && list_tail != NULL)
	{
		node_list node = d_gethead(list_head);
		pnode currentNode = node->value;

		pedge temp_edge = currentNode->edges;
		while (temp_edge != NULL)
		{
			// get node to which we arrived
			pnode nextNode = temp_edge->endpoint;

			// add node to queue
			if (nextNode->tag == 0)
			{
				d_add(list_tail, nextNode);
				list_tail = list_tail->next;
				nextNode->tag = 1;
			}

			// get edges weight
			double weight = temp_edge->weight;

			// add weight to the node
			double newWeight = currentNode->weight + weight;
			if (newWeight < nextNode->weight)
			{
				nextNode->weight = newWeight;
			}

			temp_edge = temp_edge->next;
		}

		node_list next_head = list_head->next;
		free(list_head); // not sure this is perfect
		list_head = next_head;
	}
	pnode destNode = get_node(head, dest);
	return destNode->weight;
}

pnode helperGraph(pnode list, int cities[], int size)
{
	pnode graph = NULL;
	int size_of_node = size * 4;
	char *buffer;
	char *temp = {'\0'};
	int i, j, k = 0;

	// allocate memory for the list of node representations
	buffer = (char *)calloc(sizeof(char), 4 + size * (size_of_node) + 2);
	if ((buffer) == NULL)
	{
		printf("malloc failed.");
		exit(0);
	}

	temp = (char *)calloc(sizeof(char), 5);
	if ((temp) == NULL)
	{
		printf("malloc failed.");
		exit(0);
	}
	sprintf(temp, "A %d ", size);
	strcat(buffer, temp);

	// add more info to the text
	for (i = 0; i < size; ++i)
	{
		// get node by the index
		sprintf(temp, "n %d ", i);
		strcat(buffer, temp);

		// go over all other nodes
		for (j = 0; j < size; ++j)
		{
			if (i != j)
			{
				// add edges to the graph
				int dist = (int)ShortestPath(list, cities[i], cities[j]);

				if (dist > 0)
				{
					sprintf(temp, "%d %d ", j, dist);
					strcat(buffer, temp);
				}
			}
		}
	}

	BuildGraph(&graph, &buffer);

	// change the node id to the original node id
	pnode graph_pt = graph;

	while (graph_pt != NULL)
	{
		graph_pt->node_num = cities[k];
		graph_pt = graph_pt->next;
		k++;
	}

	return graph;
}

void reset_tags(pnode head)
{
	pnode ptr = head;

	while (ptr != NULL)
	{
		ptr->tag = 0;
		ptr = ptr->next;
	}
}

pedge get_min_edge(pnode node)
{
	node->tag = 1;
	pedge temp = node->edges;
	pedge min_edge = NULL;

	while (temp != NULL)
	{
		if (min_edge == NULL && temp->endpoint->tag == 0)
		{
			min_edge = temp;
		}
		else if (min_edge != NULL && min_edge->weight > temp->weight && temp->endpoint->tag == 0)
		{
			min_edge = temp;
		}
		temp = temp->next;
	}

	if (min_edge == NULL || min_edge->endpoint->tag == 0)
	{
		return min_edge;
	}
	else
	{
		return NULL;
	}
}

int get_path_weight(pnode node)
{
	// start from given node
	pnode start = node;
	int total_weight = 0;

	// get minimum edge
	pedge min_edge = get_min_edge(start);

	while (min_edge != NULL)
	{
		total_weight += min_edge->weight;
		start = min_edge->endpoint;
		min_edge = get_min_edge(start);
	}

	if (total_weight == 0)
	{
		total_weight = INT_MAX;
	}

	return total_weight;
}

int check_path(pnode head)
{
	pnode ptr = head;

	while (ptr != NULL)
	{
		if (ptr->tag == 0)
		{
			return -1;
		}
		ptr = ptr->next;
	}

	return 1;
}

int TSP(pnode head, int *cities, int size)
{
	// get distance using a greedy method on the modified graph
	pnode graph = helperGraph(head, cities, size);

	// create pointer to run on the graph nodes
	pnode node_ptr = graph;

	// min path weight]
	int total_weight = INT_MAX;

	// go over all nodes and get path weight
	while (node_ptr != NULL)
	{
		reset_tags(graph);
		int weight = get_path_weight(node_ptr);

		if (weight < total_weight && check_path(graph) == 1)
		{
			total_weight = weight;
		}

		node_ptr = node_ptr->next;
	}

	if (total_weight == INT_MAX)
	{
		return -1;
	}

	return total_weight;
}

int *handle_tsp_input(char *input, int size)
{
	int i, j;
	char *buffer = input;
	int *result;

	// allocate memory for the list of numbers
	result = (int *)malloc(size);

	// add the numbers to the result memory
	for (i = 0; i < size; ++i)
	{
		result[i] = GetNum(buffer);
		j = LenOfNum(result[i]) + 1;
		buffer += j;
	}

	return result;
}
