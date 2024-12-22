#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <iostream>>

struct edge{
    char destVertexID;
    int weight;
    edge* nextEdge;
};
struct vertex{
    char idVertex;
    vertex* nextVertex;
    edge* firstEdge;
};
struct graph{
    vertex* firstVertex;
};

typedef vertex* adrVertex;
typedef edge* adrEdge;

void createVertex(char newVertexID,adrVertex &v);
void initGraph(graph *G);
void addVertex(graph *G,char newVertexID);
void buildGraph(graph *G);
void addEdge(vertex *from, vertex *to);
void printGraph(graph *G);
bool cekHubungan(const graph *G, char fromID, char toID);
void saranFollowers(graph *G, char fromID);
void exportToDot(graph *G);
void deleteFirstVertex(graph *G);
void deleteLastVertex(graph *G);
void deleteAfterVertex(graph *G, char afterID);

#endif // GRAPH_H_INCLUDED
