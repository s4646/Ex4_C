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
        if((*nptr)==NULL) {printf("malloc failed."); exit(0);}
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
            if((*eptr)==NULL) {printf("malloc failed."); exit(0);}
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
            (*nptr)->edges=NULL;
            break;
        }
        nptr = &((*nptr)->next);
    }

    // add node to the list
    // if at the end of the list, malloc a new node
    if (*nptr == NULL)
    {
        *nptr = (pnode)malloc(sizeof(Node));
        if((*nptr)==NULL) {printf("malloc failed."); exit(0);}
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
    while (*(buff+LenOfNum(GetNum(buff))+1) != 'A' && *(buff+LenOfNum(GetNum(buff))+1) != 'B' && *(buff+LenOfNum(GetNum(buff))+1) != 'D' && *(buff+LenOfNum(GetNum(buff))+1) != 'S' && *(buff+LenOfNum(GetNum(buff))+1) != 'T')
    {
        if(*(buff+LenOfNum(GetNum(buff))+1) == '\n' || *(buff+LenOfNum(GetNum(buff))+1) == '\0')
        {
            break;
        }
        pedge *eptr = &((*nptr)->edges);

        while (*(buff+LenOfNum(GetNum(buff))+1) >= '0' && *(buff+LenOfNum(GetNum(buff))+1) <= '9')
        {
            *eptr = (pedge)malloc(sizeof(Edge));
            if((*eptr)==NULL) {printf("malloc failed."); exit(0);}
            (*eptr)->next = NULL;

            // add edge's destination
            buff += LenOfNum(GetNum(buff))+1;

            (*eptr)->endpoint = GetNode(head, GetNum(buff));

            // add edge's weight
            buff += LenOfNum(GetNum(buff))+1;

            (*eptr)->weight = GetNum(buff);
            eptr = &((*eptr)->next);

            // if reached end of input
            if (*(buff+LenOfNum(GetNum(buff))) == '\0' || *(buff+LenOfNum(GetNum(buff))) == '\n')
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
    if(newNode==NULL) {printf("malloc failed."); exit(0);}

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
    if(list_head==NULL) {printf("malloc failed."); exit(0);}
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

pnode helperGraph(pnode list, int *cities, int size)
{
    pnode graph = NULL;
    int size_of_node = size * 4;
    char *buffer;
    char *temp = {'\0'};
    int i, j;

    // allocate memory for the list of node representations
    buffer = (char *)malloc(4 + size * (size_of_node) + 2);
    if((buffer)==NULL) {printf("malloc failed."); exit(0);}
    // memset(buffer, 0, sizeof(buffer));
    temp = (char *)malloc(5);
    if((temp)==NULL) {printf("malloc failed."); exit(0);}
    sprintf(temp, "A %d ", size);
    strcat(buffer, temp);

    // add more info to the text
    for (i = 0; i < size; ++i)
    {
        // get node by the index
        pnode node = get_node(list, cities[i]);
        sprintf(temp, "n %d ", node->node_num);
        strcat(buffer, temp);

        // go over all other nodes
        for (j = 0; j < size; ++j)
        {
            if (i != j)
            {
                // add edges to the graph
                int dist = (int)ShortestPath(list, i, j);
                sprintf(temp, "%d %d ", j, dist);
                strcat(buffer, temp);
            }
        }
    }

    puts(buffer);
    BuildGraph(&graph, &buffer);
    printf("---------------------------------------------------------------\n");
    printf("---------------------------------------------------------------\n");
    printf("---------------------------------------------------------------\n");
    PrintGraph(&graph);
    return graph;
}
