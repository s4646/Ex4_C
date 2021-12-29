#ifndef GRAPH_
#define GRAPH_

typedef struct Node *pnode;
;

typedef struct Edge
{
    int weight;
    pnode endpoint;
    struct Edge *next;
} Edge, *pedge;

typedef struct Node
{
    int node_num;
    float weight;
    int tag;
    pedge edges;
    struct Node *next;
} Node, *pnode;

typedef struct L_Node
{
    pnode value;
    struct L_Node *next;
} l_node, *node_list;

void BuildGraph(pnode *head, char **buffptr);
void InsertNode(pnode *head, char **buffptr);
void DeleteNode(pnode *head, char *buff);
void PrintGraph(pnode *head); //for self debug
void DeleteGraph(pnode *head);
void ShortestPath(pnode head, int src, int dest);
void TSP(pnode source, pnode destination);

#endif
