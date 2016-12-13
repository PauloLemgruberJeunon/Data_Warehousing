/**
 * Matheus Carvalho Nali - 9313176
 * Bruna Yukari Fujii Yoshida - 9266431
 * Paulo Pinheiro Lemgruber Jeunon Sousa - 9266330
 * Matheus dos Santos Luccas - 9005961
**/

#ifndef GRAPH_H
#define GRAPH_H

#include <src/menu/utils.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define NOT_EXIST NULL

typedef struct stack Stack;

/* Structures */
typedef struct graphVertex GraphVertex;
typedef struct graphEdge GraphEdge;
typedef struct graph Graph;

struct graphVertex {
    GraphEdge **outEdges;      /* A vector of edges that came out of it */
    int edgeCounter;               /* Number of out-Vertices comming out of this vertex */
    Info *info;                    /* Array that stores the dimensions present of the vertex */
};

struct graphEdge {
    GraphVertex *sourceVertex; /* The vertex where the edge begins */
    GraphVertex *destVertex;     /* The vertex where the edge ends */
};

struct graph {
    GraphVertex *root;           /* If the graph has some sort of root this will point to it, if not will be NULL */
    GraphVertex *bottom;      /* Indicates the lower vertex on the graph */
    GraphVertex *vertices;    /* Vector of the vertices inside the graph */
    int vertexCount;              /* Stores the number of vertices inside the graph */
    GraphEdge *edges;          /* Vector of the edges inside the graph */
    int edgeCount;                /* Stores the number of edges in the graph */
    int maxVertexWeight;
};


/* Functions */
/* Documentation on the .c file (graph.c) */
Graph* graph_init();
void graph_addVertex(Graph *g, Info *info, int biggestWeight);
GraphEdge* graph_addEdge(Graph *g, GraphVertex *source, GraphVertex *destination);
void graph_deleteGraph(Graph *g);
void graph_setRoot(Graph *g, GraphVertex *root);
void graph_setBottom(Graph *g, GraphVertex *bottom);
void graph_connectVertices(Graph *g, int groupBy);
void graph_printAllVertices(Graph *g, Info *unWantedInfo);
void graph_printAllEdges(Graph *g);
void graph_printEdge(GraphEdge *e);
char* graph_getVertexAttrs(GraphVertex *v);
char* graph_getVertexAttrsAbbrs(GraphVertex *v);
bool graph_compareVertexAttrs(Info *currVertexInfo, Info *tempVertexInfo, int groupBy, int diff);
GraphVertex* graph_findVertex(Graph *g, Info *info);
Graph* graph_createSubGraph(GraphVertex *root, GraphVertex *fromVertex, GraphVertex **allAncestors, int allAncestorsSize, int biggestWeight);
GraphVertex** graph_eliminateVertexRepetitions(GraphVertex **storedAncestors, int *ancestorsCounter, int *repetitionsCounter);
void graph_findAncestorsWithRepetitions(Graph *g, GraphVertex ***storedAncestors, int *ancestorsCounter, GraphVertex *fromVertex, bool direct);
void graph_finddescendantsWithRepetitions(Graph *g, GraphVertex ***storeddescendants, int *descendantsCounter, GraphVertex *fromVertex, bool direct);

#endif /* GRAPH_H */
