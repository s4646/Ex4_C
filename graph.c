#include <stdio.h>
#include <stdlib.h>
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
    char num[6];
    int i = 0;
    while ((*(buff + 1) != ' ' && *(buff + 1) != '\n') && i < 6)
    {
        num[i] = *(buff++);
        i++;
    }
    num[i] = *buff;
    return atoi(num);
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
        (*nptr)->node_num = counter;
        (*nptr)->edges = NULL;
        (*nptr)->next = NULL;
        (*nptr)->tag = 0;
        (*nptr)->weight = 0;
        nptr = &((*nptr)->next);
        counter++;
    }

    // add edges to the graph
    while (*(buff + 2) != 'A' && *(buff + 2) != 'B' && *(buff + 2) != 'D' && *(buff + 2) != 'S' && *(buff + 2) != 'T')
    {
        // if reached end of input
        if (*(buff + 1) == '\0' || *(buff + 1) == '\n')
        {
            buff++;
            break;
        }
        buff += 2;
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
        while (*(buff + 2) >= '0' && *(buff + 2) <= '9')
        {
            *eptr = (pedge)malloc(sizeof(Edge));
            (*eptr)->next = NULL;

            // add edge's destination
            buff += 2;

            (*eptr)->endpoint = GetNode(head, GetNum(buff));

            // add edge's weight
            buff += 2;

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
            break;
        }
        nptr = &((*nptr)->next);
    }

    // add node to the list
    // if at the end of the list, malloc a new node
    if (*nptr == NULL)
    {
        *nptr = (pnode)malloc(sizeof(Node));
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
    while (*(buff + 2) != 'A' && *(buff + 2) != 'B' && *(buff + 2) != 'D' && *(buff + 2) != 'S' && *(buff + 2) != 'T')
    {
        pedge *eptr = &((*nptr)->edges);

        while (*(buff + 2) >= '0' && *(buff + 2) <= '9')
        {
            *eptr = (pedge)malloc(sizeof(Edge));
            (*eptr)->next = NULL;

            // add edge's destination
            buff += 2;

            (*eptr)->endpoint = GetNode(head, GetNum(buff));

            // add edge's weight
            buff += 2;

            (*eptr)->weight = GetNum(buff);
            eptr = &((*eptr)->next);

            // if reached end of input
            if (*(buff + 1) == '\0' || *(buff + 1) == '\n')
            {
                buff++;
                *buffptr = buff;
                return;
            }
        }
    }
    *buffptr = buff;
}

// an add for the dlikstra
void d_add(node_list list_tail, pnode node)
{
    l_node *newNode = (l_node *)malloc(sizeof(l_node));

    if (newNode == NULL)
    {
        printf("Couldnt allocate memory, shutting down!");
        exit(1);
    }

    newNode->next = NULL;
    newNode->value = node;
    list_tail->next = newNode;
}

// a remove for djikstra
void d_remove(pnode *list, int node_id)
{
    if (list != NULL)
    {
        pnode temp = *(list);

        while (temp->next->node_num != node_id)
        {
            temp = temp->next;
        }

        pnode nextNode = temp->next->next;
        free(temp->next);
        temp->next = nextNode;
    }
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
    while (temp->node_num != id)
    {
        temp = temp->next;
    }

    return temp;
}

void ShortestPath(pnode head, int src, int dest)
{

    /*need to make so that we put src as head then i will be done*/

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
    l_node ln = {srcNode, NULL};
    node_list list_head = &ln;
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
        // free(list_head);
        list_head = next_head;
    }
    pnode destNode = get_node(head, dest);
    printf("Shortest distance from %d to %d is: %.3f\n", src, dest, destNode->weight);
}