/**
 * Matheus Carvalho Nali - 9313176
 * Bruna Yukari Fujii Yoshida - 9266431
 * Paulo Pinheiro Lemgruber Jeunon Sousa - 9266330
 * Matheus dos Santos Luccas - 9005961
**/

#include "graph.h"
#include <src/consts/printColors.h>


/**
*    FILE *save = fopen("vertexInfo", "r");

    Info *fromVertexInfo = utils_readSavedInput(save);

    fclose(save);
* @Function: Creates and initializes a graph with default values
* @Parameters: none
*
**/
Graph* graph_init(void) {
	Graph *g = (Graph*)malloc(sizeof(Graph)); 

    /* Set the variables to a default value */
    g->root = NOT_EXIST;
	g->vertices = NOT_EXIST;
	g->vertexCount = 0;
	g->edges = NOT_EXIST;
	g->edgeCount = 0;

	return g;
}


/**
*
* @Function: Add a vertex to the graph structure
* @Parameters: "Graph *g" -> Graph where the vertex will be added
*                         "Info *info" -> Info structure that will serve as the vertex information
*                         "int biggestWeight" -> Information to check if a vertex is the root of the graph (the vertex with less granularity)
*
**/
void graph_addVertex(Graph *g, Info *info, int biggestWeight) {
	int posToAccess = g->vertexCount;

    /* If the information sent is NULL, do nothing */
    if(info == NULL) {
        return;
    }

    /* Increment the counter of the number of vertices inside the graph */
	g->vertexCount++;

    /* Allocate one more space inside the graph vertex array */
    g->vertices = (GraphVertex*)realloc(g->vertices, g->vertexCount*sizeof(GraphVertex));
	GraphVertex *vert = &(g->vertices[posToAccess]);
    vert->info = info;

    /* Set some default values and desired values to the variables */
	vert->outEdges = NOT_EXIST;
	vert->edgeCounter = 0;	

    /* Checks if the weight of the vertex is the biggest in the graph */
    if(biggestWeight == info->infoWeight) {
        graph_setRoot(g, vert);
        g->maxVertexWeight = biggestWeight;

    /* Checks if the weight of the added vertex is 0, so it is the bottom of the graph */
    } else if(info->infoWeight == 0) {
        graph_setBottom(g, vert);
    }
}


/**
*
* @Function: Add an edge to the graph structure
* @Parameters: "Graph *g" -> Graph where the edge will be added
*                         "GraphVertex *source" -> The address of the vertex that will be the source of the edge
*                         "GraphVertex *destination" -> The address of the vertex that will be the destination of the edge
*
**/
GraphEdge* graph_addEdge(Graph *g, GraphVertex *source, GraphVertex *destination) {
	int posToAccess = g->edgeCount;

    /* Increment the counter of the number of edges inside the graph */
	g->edgeCount++;	

    /* Allocate one more space inside the graph edge array */
	g->edges = (GraphEdge*)realloc(g->edges, g->edgeCount*sizeof(GraphEdge));
	GraphEdge *e = &(g->edges[posToAccess]);

    /* Set the source vertex, the destination vertex of the edge and some attributes */
	e->sourceVertex = source;
	e->destVertex = destination;

    /* Updates the array of edges that come out of the source vertex */
	int posToAccessV = source->edgeCounter;
	source->edgeCounter++;
	source->outEdges = (GraphEdge**)realloc(source->outEdges, source->edgeCounter*sizeof(GraphEdge*));
	source->outEdges[posToAccessV] = &(g->edges[posToAccess]);	

    return e;
}


/**
*
* @Function: Set the "root" pointer to a vertex structure
* @Parameters: "Graph *g" -> The graph where the root will be set
*                         "GraphVertex *root" -> The address of the vertex that the root will point to
*
**/
void graph_setRoot(Graph *g, GraphVertex *root) {
    /* Set the root vertex (optional) */
	g->root = root;
}


/**
*
* @Function: Set the "bottom" pointer to a vertex structure
* @Parameters: "Graph *g" -> The graph where the bottom will be set
*                         "GraphVertex *bottom" -> The address of the vertex that the bottom will point to
*
**/
void graph_setBottom(Graph *g, GraphVertex *bottom) {
    /* Set the root vertex (optional) */
    g->bottom = bottom;
}


/**
*
* @Function: Free the space in memory that a graph is occupying
* @Parameters: "Graph *g" -> Graph to be erased
*
**/
void graph_deleteGraph(Graph *g) {

    int i;

	/* Free all the vertices */
	for(i = 0; i < g->vertexCount; i++) {
		GraphVertex *v = &(g->vertices[i]);
        free(v->info->dimensions);
        free(v->info);
        /*free(v);*/
	}

    free(g->edges);

	/* Free the graph */
	free(g);
}



/**
*
* @Function: Function to get all unconnected vertices of the graph and make all the connections. It only works if all the vertices on the graph are
*                     unconnected
* @Parameters: "Graph *g" -> Graph to have all the vertices connected
*                         "int groupBy" -> The number of dimension on each vertex "Info" structure
*
**/
/* This function is used to get a Graph with none of its vertices connected and connect them all */
void graph_connectVertices(Graph *g, int groupBy) {

    /* Counters for the "for" loops below */
    int i, j;

    /* Iterates over all vertices */
    for(i = 0; i < g->vertexCount; i++) {

        /* Holds a vertex to compare with all the other vertices */
        GraphVertex *currVertex = &(g->vertices[i]);

       /* Iterates over all vertices */
        for(j = 0; j < g->vertexCount; j++) {

            /* change every time to be compared with the "currVertex" vertex */
            GraphVertex *tempVertex = &(g->vertices[j]);

            /* Prevents self-comparrisons */
            if(i != j) {

                /* Checks if the "currVertex" have less granularity than the "tempVertex" */
                if(currVertex->info->infoWeight == (tempVertex->info->infoWeight + 1)) {

                    /* Will compare two vertex attributes to see if they have only one attribute that is different from the other vertex atttribute,
                        if it only has one different, it will make a connection between them*/
                    if(graph_compareVertexAttrs(currVertex->info, tempVertex->info, groupBy, 1) == true) {
                        graph_addEdge(g, currVertex, tempVertex);
                    }
                }
            }
        }
    }
}


/**
*
* @Function: Compare the attributes of two diferent vertices of the graph
* @Parameters: "Info *currVertexInfo" -> The first vertex to have the attributes compared
*                         "Info *tempVertexInfo" -> The second vertex to have the attributes compared
*                         "int groupBy" -> The number of dimensions and attributes (You have one attribute per dimension here)
*                          "int diff" -> The number of different attributes the function must identify to return true
*
**/
bool graph_compareVertexAttrs(Info *currVertexInfo, Info *tempVertexInfo, int groupBy, int diff) {

    /* Loop counter variables */
    int k, l;

    /* The number of equal attributes found */
    int equalAttrsCount = 0;

    /* Iterates over the attributes of the "currVertex" */
    for(k = 0; k < groupBy; k++) {

        /* Stores the current attribute */
        char *currAttr = currVertexInfo->dimensions[k].attrs[0].attr;

        /* Compare the "currAttribute" with all the attributes of the "tempVertex" */
        for(l = 0; l < groupBy; l++) {
            /* Stores the attribute of the "tempVertex" */
            char *tempAttr = tempVertexInfo->dimensions[l].attrs[0].attr;

            /* Compares the "currAttr" with the "tempAttr" and if they are equal, checks if they have the same dimension */
            if(strcmp(currAttr, tempAttr) == 0) {
                char *currDim = currVertexInfo->dimensions[k].dimensionName;
                char *tempDim = tempVertexInfo->dimensions[l].dimensionName;

                /* If the dimmension of them is the same, the edge is created. The "currVertex" is the source and the other is the dest */
                if(strcmp(currDim, tempDim) == 0) {
                    /* Count the number of equal attributes in commom between the "currVertex" and "tempVertex" */
                    equalAttrsCount++;
                }
            }
        }
    }
    /* An edge only can connect two vertices if them have only the "groupBy"-1 number of attributes in commom */
    if(equalAttrsCount == groupBy-diff) {
        return true;
    }

    return false;
}


/**
*
* @Function: Will print on the terminal all the existent vertices on the graph
* @Parameters: "Graph *g" -> Graph where the vertices to be printed are
*
**/
void graph_printAllVertices(Graph *g, Info *unWantedInfo) {

    /*loop counter variable*/
    int i;

    /* Iterates over all the graph vertices */
    for(i = 0; i < g->vertexCount; i++) {        

        if(graph_compareVertexAttrs(g->vertices[i].info, unWantedInfo, unWantedInfo->dimCounter, 0) == true) {
            continue;
        }

        /* Print each vertex each time with the green color */
        utils_printInfo(g->vertices[i].info, BOLDGREEN);
    }

}


/**
*
* @Function: Print all existing edges on the graph, showing all the graph structure
* @Parameters: "Graph *g" -> Graph where the edges to be printed are
*
**/
void graph_printAllEdges(Graph *g) {

    /*loop counter variable*/
    int i;

    /* Clear the terminal screen fo make it easier to see the output */
    /*system("clear");*/

    printf("\n%s The height of a vertex is inversely proportional to it's granularity %s \n", BOLDGREEN, RESET);
    printf("%s The maximum height of this graph is %d %s \n\n", BOLDBLUE, g->maxVertexWeight, RESET);

    /* Iterates over all the graph edges */
    for(i = 0; i < g->edgeCount; i++) {

        /* Print each edge on screen */
        graph_printEdge(&g->edges[i]);
    }
}


/**
*
* @Function: Print an edge on screen
* @Parameters: "GraphEdge *e" -> Edge to be printed on screen
*
**/
void graph_printEdge(GraphEdge *e) {

    /* holds the source and destination vertices of the edge */
    GraphVertex *source = e->sourceVertex;
    GraphVertex *dest = e->destVertex;

    /* Prints them */
    printf("%s *From graph height %d to %d: %s", BOLDWHITE, source->info->infoWeight, dest->info->infoWeight, RESET);
    printf("%s{ %sSource Vertex%s (Attributes = %s)%s } %s-> %s{ %sDestination Vertex%s (Attributes = %s)%s }",
              BOLDWHITE, BOLDGREEN, BOLDYELLOW, graph_getVertexAttrs(source), BOLDWHITE, BOLDRED, BOLDWHITE, BOLDCYAN,
               BOLDYELLOW, graph_getVertexAttrs(dest), BOLDWHITE);


    printf("\n\n %s ---------------------------- %s \n\n", BOLDMAGENTA, RESET);
}


/**
*
* @Function: Get a vertex attribute together in only one formated string
* @Parameters: "GraphVertex *v" -> Vertex to have the attributes united in one string
*
**/
char* graph_getVertexAttrs(GraphVertex *v) {

    /* Loop counter variables */
    int i, j = 0, k = 0;

    /* char that will store the current letters */
    char *attrs = NULL;
    attrs = (char*)malloc(sizeof(char));

    /* Iterates over all dimensions */
    for(i = 0; i < v->info->dimCounter; i++) {

        /* Gets the attribute to it's '\0' character and add each character at a time to the attrs string */
        while((attrs[j] = v->info->dimensions[i].attrs->attr[k]) != '\0') {
            j++;
            k++;
            attrs = (char*)realloc(attrs, (j+1)*sizeof(char));
        }

        /* Resets "k" counter */
        k = 0;

        /* Format the attrs string only in it is not the last attrs */
        if(i < v->info->dimCounter-1) {
            attrs[j] = ' ';
            attrs = (char*)realloc(attrs, (j+4)*sizeof(char));
            attrs[j+1] = '&';
            attrs[j+2] = ' ';
            j += 3;
        }

    }

    /* Return the formated attribute string */
    return attrs;
}


/**
*
* @Function: Get a string with all the vertex attributes abbreviations together and formated
* @Parameters: "GraphVertex *v" -> Vertex to have the attributes abbreviations united and formated
*
**/
char* graph_getVertexAttrsAbbrs(GraphVertex *v) {

    /* Loop counter variables */
    int i, j = 0, k = 0;

    /* char pointer that will be filled with all the attribute abbreviations */
    char *abbrs = NULL;
    abbrs = (char*)malloc(sizeof(char));

    /* Iterates over all dimensions of the vertex "v" */
    for(i = 0; i < v->info->dimCounter; i++) {

        /* Gets the attribute's abbreviation to it's '\0' character and add each character at a time to the abbrs string */
        while((abbrs[j] = v->info->dimensions[i].attrs->abbr[k]) != '\0') {
            j++;
            k++;
            abbrs = (char*)realloc(abbrs, (j+1)*sizeof(char));
        }

        /* Resets the k counter */
        k = 0;

        /* Format the abbrs string only in it is not the last abbrs */
        if(i < v->info->dimCounter-1) {
            abbrs[j] = '_';
            j++;
            abbrs = (char*)realloc(abbrs, (j+1)*sizeof(char));
        }

    }

    /* Return a string with all the abbreviations og the vertex formated */
    return abbrs;
}


/**
*
* @Function: Find a vertex on the graph according to the Info structure passed
* @Parameters: "Graph *g" -> Graph where the wanted vertex is
*                         "Info *info" -> Info that will be used to find the vertex
*
**/
GraphVertex* graph_findVertex(Graph *g, Info *info) {

    /* Loop counter variable */
    int i;

    /* Iterates over a list containing all the vertices */
    for(i = 0; i < g->vertexCount; i++) {

        /* Get the current vertex*/
        GraphVertex *tempVertex = &g->vertices[i];

        /* Compare its attributes with the "info" attributes passed to this function. If it is the same, will return the pointer to the wanted vertex */
        if(graph_compareVertexAttrs(info, tempVertex->info, tempVertex->info->dimCounter, 0) == true) {
            return tempVertex;
        }
    }

    /* If is not found will return a NULL pointer*/
    return NOT_EXIST;
}


void graph_findAncestorsWithRepetitions(Graph *g, GraphVertex ***storedAncestors, int *ancestorsCounter, GraphVertex *fromVertex, bool direct) {

    /* Loop counter variable */
    int i;

    /* Iterates over all edges in the graph */
    for(i = 0; i < g->edgeCount; i++) {

        /* Set a current Edge */
        GraphEdge *currEdge = &g->edges[i];

        /* If this edge has the destination to the wanted vertex, so the source of this edge is an ancestor of the "fromVertex" */
        if(fromVertex == currEdge->destVertex) {

            /* If the source vertex is the root of the graph ends the function (got to the top) */
            if(currEdge->sourceVertex == g->root) {
                return;
            }

            /* Allocates and inserts a ancestor on the "storedAncestors" array */
            (*storedAncestors) = (GraphVertex**)realloc((*storedAncestors), ((*ancestorsCounter)+1)*sizeof(GraphVertex*));
            (*storedAncestors)[(*ancestorsCounter)] = currEdge->sourceVertex;
            (*ancestorsCounter) = (*ancestorsCounter)+1;

            /* Function call itself recursevely to get the ancestor of the ancestor only if you do not want a direct ancestor */
            if(direct == false) {
                graph_findAncestorsWithRepetitions(g, storedAncestors, ancestorsCounter, currEdge->sourceVertex, direct);
            }
        }
    }
}


void graph_finddescendantsWithRepetitions(Graph *g, GraphVertex ***storeddescendants, int *descendantsCounter, GraphVertex *fromVertex, bool direct) {

    /* Loop counter variable */
    int i;

    /* Iterates over all edges in the graph */
    for(i = 0; i < g->edgeCount; i++) {

        /* Set a current Edge */
        GraphEdge *currEdge = &g->edges[i];

        /* If this edge has the destination to the wanted vertex, so the source of this edge is an ancestor of the "fromVertex" */
        if(fromVertex == currEdge->sourceVertex) {

            /* If the source vertex is the root of the graph ends the function (got to the top) */
            if(currEdge->destVertex->info->infoWeight == 0) {
                return;
            }

            /* Allocates and inserts a ancestor on the "storedAncestors" array */
            (*storeddescendants) = (GraphVertex**)realloc((*storeddescendants), ((*descendantsCounter)+1)*sizeof(GraphVertex*));
            (*storeddescendants)[(*descendantsCounter)] = currEdge->destVertex;
            (*descendantsCounter) = (*descendantsCounter)+1;

            /* Function call itself recursevely to get the ancestor of the ancestor only if you do not want a direct descendant */
            if(direct == false) {
                graph_finddescendantsWithRepetitions(g, storeddescendants, descendantsCounter, currEdge->destVertex, direct);
            }
        }
    }
}


GraphVertex** graph_eliminateVertexRepetitions(GraphVertex **storedAncestors, int *ancestorsCounter, int *repetitionsCounter) {

    /* Loop Counter variables */
    int i, j;

    /* Set a default value */
    (*repetitionsCounter) = 0;

    /* Varible to check if an repetition has ocurred */
    bool repetition;

    /* Allocates the first position on the new ancestors vector that will contain no repetitions */
    GraphVertex **allAncestors = (GraphVertex**)malloc(sizeof(GraphVertex*));

    /* Iterates over all elements of the "storedAncestors" array */
    for(i = 0; i < (*ancestorsCounter); i++) {        

        /* Lock on the current vertex */
        GraphVertex *currVertex = storedAncestors[i];

        /* Resets the value of the "repetition" variable to false */
        repetition = false;

        /* Iterates one position in from o "i" to the end of the ancestors vector */
        for(j = i+1; j < (*ancestorsCounter); j++) {            

            /* Holds a temporary vertex */
            GraphVertex *tempVertex = storedAncestors[j];

            /* Checks if there is an repetition */
            if(currVertex == tempVertex) {

                /* Sets the variable to true */
                repetition = true;

                /* refresh the number of repetitions on the counter */
                (*repetitionsCounter)++;
                break;
            }

        }

        /* If there were no repetitions, include the pointer to the vertex in the "allAncestors" array */
        if(repetition == false) {
            allAncestors[i-(*repetitionsCounter)] = currVertex;
            allAncestors = (GraphVertex**)realloc(allAncestors, (i-(*repetitionsCounter)+2)*sizeof(GraphVertex*));
        }
    }

    /* free preaviously allocated array */
    free(storedAncestors);

    /* Return the new vector with the vertex with out repetition */
    return allAncestors;
}


Graph* graph_createSubGraph(GraphVertex *rootOrBottom, GraphVertex *fromVertex, GraphVertex **allAncestors, int allAncestorsSize, int biggestWeight) {

    /* Creates an initializes a new empty graph */
    Graph *ancestorsGraph = graph_init();

    /* Add the Root and the leaf of the new graph, respectively */
    if(rootOrBottom != NULL) {
        graph_addVertex(ancestorsGraph, utils_copyInfo(rootOrBottom->info), biggestWeight);
    }

    graph_addVertex(ancestorsGraph, utils_copyInfo(fromVertex->info), biggestWeight);

    /* Loop counter variable */
    int i;

    /* Iterates over all the ancestors array */
    for(i = 0; i < allAncestorsSize; i++) {
        GraphVertex *currVertex = allAncestors[i];
        graph_addVertex(ancestorsGraph, utils_copyInfo(currVertex->info), biggestWeight);
    }

    /* Connect all the loose vertex on the graph */
    graph_connectVertices(ancestorsGraph, fromVertex->info->dimCounter);

    /* return the new graph */
    return ancestorsGraph;
}



