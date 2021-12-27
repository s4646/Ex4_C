#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

Node* GetNode(pnode* head, int num)
{
    pnode *temp = head;
    while (*temp!=NULL && (*temp) -> node_num != num)
    {
        temp = &((*temp) -> next);
    }
    return *temp;
}

int GetNum(char* buff)
{
    char num[6];
    int i = 0;
    while((*(buff+1)!=' ' && *(buff+1)!='\n') && i<6)
    {
        num[i]=*(buff++);
        i++;
    }
    num[i]=*buff;
    return atoi(num);
}

void PrintEdges(pedge head)
{
    pedge temp = head;
    while(temp !=NULL)
    {
        printf("Edge's destinstion: %d, weight: %d\n", temp->endpoint->node_num, temp->weight);
        temp = temp->next;
    }
}

void PrintGraph(pnode* head)
{
    pnode* temp = head;
    while((*temp)->next !=NULL)
    {
        printf("Node's ID: %d, next is %d\n", (*temp)->node_num, (*temp)->next->node_num);
        PrintEdges((*temp)->edges);
        temp = &((*temp) -> next);
    }
    printf("Node's ID: %d\n", (*temp)->node_num);
    PrintEdges((*temp)->edges);
}

void DeleteGraph(pnode *head)
{
    if(*head==NULL)
        return;
    
    pnode *ntemp = head;
    pedge *etemp = NULL;
    pnode nprev = NULL;
    pedge eprev = NULL;
    // remove nodes
    while (*ntemp != NULL)
    {
        
        etemp = &((*ntemp) -> edges);
        // remove edges of node
        while(*etemp != NULL)
        {
            eprev = *etemp;
            etemp = &((*etemp) -> next);
            free(eprev);
        }
        nprev = *ntemp;
        ntemp = &((*ntemp) -> next);
        free(nprev);
    }
}

void BuildGraph(pnode *head, char** buffptr)
{
    char* buff = *buffptr;
    // delete the previous graph if exists
    DeleteGraph(head);
    
    // create nodes for the new graph
    buff += 2; // 4
    int counter = 0;
    // head = (pnode*)malloc(GetNum(buff)*sizeof(pnode));
    pnode *nptr = head;

    while (counter < GetNum(buff))
    {
        (*nptr) = (pnode)malloc(sizeof(Node));
        (*nptr) -> node_num = counter;
        (*nptr) -> edges = NULL;
        (*nptr) -> next = NULL;
        nptr  = &((*nptr) -> next);
        counter++;
    }
    
    // add edges to the graph
    while(*(buff+2)!='A' && *(buff+2)!='B' && *(buff+2)!='D' && *(buff+2)!='S' && *(buff+2)!='T')
    {
        // if reached end of input
        if(*(buff+1)=='\0' || *(buff+1)=='\n')
        {
            buff++;
            break;
        }
        buff += 2; // n
        // get node of given ID
        if(*buff=='n')
        {
            buff += 2; // 0
            nptr = head;
            while ((*nptr) -> node_num != GetNum(buff))
            {
                nptr = &((*nptr) -> next);
            }
        }

        pedge *eptr = &((*nptr) -> edges);

        // add edges to node
        while(*(buff+2)>='0' && *(buff+2)<='9' )
        {
            *eptr = (pedge)malloc(sizeof(Edge));
            (*eptr) ->next = NULL;  
            
            // add edge's destination
            buff += 2; // 2

            (*eptr) -> endpoint = GetNode(head, GetNum(buff));
            
            // add edge's weight
            buff += 2; // 5

            (*eptr) -> weight = GetNum(buff);
            eptr = &((*eptr) ->next);
        }
    }
    *buffptr = buff;
}

void InsertNode(pnode* head, char** buffptr)
{
    char* buff = *buffptr;

    pnode *nptr = head;
    // if node does not exist, go to end of the list
    while(*nptr != NULL)
    {
        // if node already exist, remove its out edges
        if((*nptr)->node_num==GetNum(buff+2))
        {
             pedge *etemp = &((*nptr) -> edges);
             pedge eprev = NULL;

            while(*etemp != NULL)
            {
                eprev = *etemp;
                etemp = &((*etemp) -> next);
                free(eprev);
            }
            break;
        }
        nptr = &((*nptr) ->next);
    }
    
    // add node to the list
    if(*nptr == NULL)
    {
        *nptr = (pnode)malloc(sizeof(Node));
        buff+=2;
        (*nptr)->node_num = GetNum(buff);
        (*nptr)->next=NULL;
    }
    else
    {
        buff+=2;
        (*nptr)->node_num = GetNum(buff);
    }

    // add edges to node
    while(*(buff+2)!='A' && *(buff+2)!='B' && *(buff+2)!='D' && *(buff+2)!='S' && *(buff+2)!='T')
    {   
         pedge *eptr = &((*nptr) -> edges);
        
        while(*(buff+2)>='0' && *(buff+2)<='9' )
        {
            *eptr = (pedge)malloc(sizeof(Edge));
            (*eptr) ->next = NULL;  
            
            // add edge's destination
            buff += 2; // 2

            (*eptr) -> endpoint = GetNode(head, GetNum(buff));
            
            // add edge's weight
            buff += 2; // 5

            (*eptr) -> weight = GetNum(buff);
            eptr = &((*eptr) ->next);
            
            // if reached end of input
            if(*(buff+1)=='\0' || *(buff+1)=='\n')
            {
                buff++;
                *buffptr = buff;
                return;
            }
        }
    }
    *buffptr = buff;
}