#ifndef GRAPH_
#define GRAPH_

typedef struct Node *pnode;;

typedef struct Edge {
    int weight;
    pnode endpoint;
    struct Edge *next;
} Edge, *pedge;


typedef struct Node {
    int node_num;
    pedge edges;
    struct Node *next;
} Node, *pnode;

void BuildGraph(pnode *head, char** buffptr);
void InsertNode(pnode *head, char* buff);
void DeleteNode(pnode *head, char* buff);
void PrintGraph(pnode *head); //for self debug
void DeleteGraph(pnode* head);
void ShortestPath(pnode head);
void TSP(pnode source, pnode destination);

#endif
