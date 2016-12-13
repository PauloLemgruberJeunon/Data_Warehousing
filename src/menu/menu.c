/**
 * Matheus Carvalho Nali - 9313176
 * Bruna Yukari Fujii Yoshida - 9266431
 * Paulo Pinheiro Lemgruber Jeunon Sousa - 9266330
 * Matheus dos Santos Luccas - 9005961
**/

#include "menu.h"
#include <src/menu/utils.h>
#include <src/consts/printColors.h>
#include <stdlib.h>
#include <string.h>
#include <src/consts/bool.h>


/**
 *
 *  @Funtion: Function that controls the flow of the program according to the user's necessities
 *  @ Parameters: nothing
 *
 **/
void menu(void) {

    /* This variable is for storing the user's functionality choice */
    char func = '0';

    /* Creates and starts the graph with default values */
    Graph *g = graph_init();

    /* Creates a "FILE" pointer to store the saved user input */
    FILE *save = NULL;

    /* Creates a "FILE" pointer to store the .dot file that represents the graph visually */
    FILE *dotFile = NULL;

    /* Creats the variable that will indicate if an graph is already initialized and sets a default value */
    bool hasGraph = false;

    while(true) {

        printf("\n %sEnter with the letter corresponding to the functionality that you want: %s", BOLDWHITE, RESET);
        scanf("%c", &func);
        utils_removeNBar();


        /* Switch function to select between the desired functionalities */
        switch(func) {

            /* Functionality to get the user input of Dimensions and their associated attributes */
            case 'i': {

            /* Checks if a graph is already initialized */
            if(hasGraph == false) {

                Info *i = utils_startInput();

                /* Calls the input method to get the user input and create the graph from it */
                i = menu_inputMethod(g, i);

                /* Save the user input on a file named save.bin */
                save = menu_saveInput(i);

                /* Based on the existing graph, creates a .dot file that represents the graph vertices and connections between them */
                dotFile = menu_generateDOT(g, "Graph.dot");

                /* Sets the "hasGraph" variable to true, indicating that the program already have an initialized graph */
                hasGraph = true;

                system("clear");

                utils_printMenuOptions();

                printf(" %sGraph was successifully created!%s \n\n", BOLDCYAN, RESET);

                /* In case that you already have an initialized graph */
            } else {

                /* Warning */
                printf("\n%s A graph already exists %s \n", BOLDYELLOW, RESET);
            }

            } break;

            /* Functionality to print all the connections between the graph vertices on the terminal */
            case 'p': {

                /* Clear the application terminal */
                system("clear");
                system("clear");

                /* prints all the connections of the graph on the terminal */
                graph_printAllEdges(g);

                utils_printMenuOptions();

            } break;

             /* Functionality to obtain the "user's input" through the previously saved user input ("save.bin") */
            case 'r': {

                /* Clear the application terminal */
                system("clear");

                /* Reprints the menu options */
                utils_printMenuOptions();

                /* Checks if a graph is already initialized */
                if(hasGraph == false) {

                    /* Open the file "save" that contain the saved user input */
                    FILE *save = fopen("save.bin", "rb");                    

                    /* Reads the user input and returns a struct equal to the struct created by a user input */
                    Info *i = utils_readSavedInput(save);

                    /* Close the file "save" */
                    fclose(save);

                    /* Call the "inputMethod" but already passing the input as an argument, so it only have to create the graph */
                    i = menu_inputMethod(g, i);

                    /* Re-save for debugging reasons */
                    save = menu_saveInput(i);

                    /* Re-generate the .dot file for debugging reasons */
                    dotFile = menu_generateDOT(g, "Graph.dot");

                    /* Sets the "hasGraph" variable to true, indicating that the program already have an initialized graph */
                    hasGraph = true;

                    printf("%s Graph was successifully loaded!%s \n\n", BOLDCYAN, RESET);

                    /* In case that you already have an initialized graph */
                } else {

                    /* Warning */
                    printf("\n%s A graph already exists %s \n", BOLDYELLOW, RESET);
                }

            } break;

            case 't': {

                system("clear");

                /* Checks if a Graph exists, if not, enter here */
                if(hasGraph == false) {
                    utils_printMenuOptions();
                    printf("\n%s There is no graph constructed, can not execute this opperation %s\n", BOLDYELLOW, RESET);
                    break;
                }

                printf("\n%s Obs%s: this function will %sprint the vertices%s of the descendants or ancestors of the wanted vertex on the graph\n ",
                                                                                                                                                             BOLDGREEN, BOLDWHITE, BOLDCYAN,BOLDWHITE);
                printf("%sand %sgenerate a '.dot' file%s representing a sub-graph of what was printed on screen.%s", BOLDWHITE,
                                                                                                                                                        BOLDCYAN, BOLDWHITE, RESET);

                printf("\n\n %s To get all the descendants, enter with %s 'ad' %s, for all the Ancestors, type %s 'aa' %s", BOLDWHITE, BOLDRED, BOLDWHITE,
                                                                                                                                                                                      BOLDYELLOW, RESET);
                printf("\n %s To get the Direct descendants, enter with %s 'dd' %s and for Direct Ancestors type %s 'da' %s \n", BOLDWHITE, BOLDBLUE,
                                                                                                                                                                                    BOLDWHITE, BOLDGREEN, RESET);
                /* Will store the letters of the word */
                char frag;

                /* Store the users choice */
                char *choice = NULL;

                int i = 0;
                /* Dinamic allocate the dimensionName char array as the user types on the keyboard */
                for(i = 0; ((frag = getchar()) != '\n') && (i<2) ; i++) {
                    choice = (char*)realloc(choice, (i+2)*sizeof(char));
                    choice[i] = frag;
                }
                choice[i] = '\0';

                /* Switchs between the function parameters according to the user's choise */
                if(strcmp(choice, "ad") == 0) {
                    menu_generateAncestorOrdescendantGraph(g, false, false);
                } else if(strcmp(choice, "aa") == 0) {
                    menu_generateAncestorOrdescendantGraph(g, true, false);
                } else if(strcmp(choice, "dd") == 0) {
                    menu_generateAncestorOrdescendantGraph(g, false, true);
                } else if(strcmp(choice, "da") == 0) {
                    menu_generateAncestorOrdescendantGraph(g, true, true);
                } else {

                }

            } break;

            /* Functionality to access the desired registers of the "save.bin" file and display them on the screen */
            case 'a': {

                /* Clear the application terminal */
                system("clear");

                /* Try to open the "save.bin" file and checks if it exists */
                if ((save = fopen("save.bin", "rb"))) {

                    /* Calls a method thar will read the fields of the "save.bin" arquive and print them according to the user's desire */
                    menu_accessMethod(save);

                    /* Close the previously opened "save.bin" file */
                    fclose(save);

                    /* If could not find the file */
                } else {

                    /* Warning */
                    printf("\n %s The save file was not found, try to create the graph again... %s", BOLDYELLOW, RESET);
                }

            } break;

            /* Functionality to print again the functionalities available */
            case 'h': {

                /* Clear the application terminal */
                system("clear");

                /* Print the colorful menu options again */
                utils_printMenuOptions();

            } break;

            /* Functionality to exit the program */
            case 'e': {

                /* Prints a polite message */
                printf("\n %s Good bye ..... %s\n\n", BOLDWHITE, RESET);

                /* Ends the menu function and, after, the program */
                return;
            } break;

            default: {
                printf("%s This option was not recognizable, try again ... %s \n\n", BOLDRED, RESET);
            }

        }

    }

}


/**
 *
 *  @Funtion: Main funtion, responsible to create the graph and processing the user's input
 *  @ Parameters: "Graph *g" - > holds the adress of the graph stored on the menu funtion, used to create the graph
 *                           "Info *inputInfo" -> Can contain a NULL pointer in case the funtion will have to get the user's input, or
 *                                                         already contains all the information needed in case of the getting the stored input
 *
 **/
Info* menu_inputMethod(Graph *g, Info *inputInfo) {
    /* The user keyboard input is received below */
    if(inputInfo == NULL) {
        inputInfo = utils_autoInput();
    }

    /* All dimensions are divided to have one "Dimension" structure per attribute, so they are divided and gathered in the dimensionsVector */
    Dimension *dimensionsVector = utils_separateDimensions(inputInfo);

    /* dSize stores the size of the dimensionsVector */
    int i, dSize = 0;
    /* Gets the size of the dimensionsVector returned above by the separateDimensions function */
    for(i = 0; i < inputInfo->dimCounter; i++) {
        Dimension *currDim = &(inputInfo->dimensions[i]);
        dSize += currDim->attrsCounter;
    }

    /* Creates an temp Info structure (package) to hold the vertex information temporarily for the attributeCombination function */
    Info temp;
    temp.dimCounter = inputInfo->dimCounter;
    temp.dimensions = (Dimension*)malloc(temp.dimCounter*sizeof(Dimension));

    int groupBy = temp.dimCounter;

    /* The resultant and unfiltered data from the "attributeCombination" is stored here */
    Info **storedVerticesInfo = NULL;

    /* stores the size of the "storedVectorInfo" as it growns on the funcion below */
    int *counter = (int*)malloc(sizeof(int));
    *counter = 0;

    /* Recursive method that combines the attributes of the dimensions. It generates trash too, because it can combine attributes of the same
        dimension on the same Info that is what each vertex of the future graph will have for its data */
    menu_attributeCombination(&storedVerticesInfo, dimensionsVector, &temp, 0, dSize-1, 0, groupBy, counter);

    int biggestWeight;

    /* The function below will clean the unnecessary Infos inside the storedVerticesInfo and will set the infoWeight */
    utils_cleanTrashInfo(storedVerticesInfo, *counter, groupBy, &biggestWeight);

    /* Loop to iterate over all the elements on the "storedVerticesInfo" vector and add the graph's vertices */
    for(i = 0; i < *counter; i++) {
        Info *currInfo = storedVerticesInfo[i];

        /* Checks if the currInfo had been deleted, probabily because was a invalid combination of Dimensions */
        if(currInfo == NULL) {
            continue;
        }

        /* Add a vertex to the graph with his information being the currInfo, that contain one attribute per dimension and all diferent dimensions */
        graph_addVertex(g, currInfo, biggestWeight);

    }

    /* Function that connects all the vertices. All of them were preaviusly without any connections */
    graph_connectVertices(g, groupBy);    

    /* returns the user's input information */
    return inputInfo;
}


/* Stores the Vertices Info on the "storedVerticesInfo" array of pointers */
void menu_storeVertexInfo(Info ***storedVerticesInfo, Info *verticesInfo, int counter)  {
    /* reallocates the array */
    *(storedVerticesInfo) = (Info**)realloc(*(storedVerticesInfo), (counter+1)*sizeof(Info*));
    /* copy the information */
    (*storedVerticesInfo)[counter] = utils_copyInfo(verticesInfo);
}


/**
 *
 *  @Funtion: Function responsible to generate all the combinations between the "Dimension *dimVector", including combinations with
 *                   the two or more dimensions with same Dimensions, like: Produto:marca & Produto:produto
 *  @ Parameters: "Info ***storedVerticesInfo" - > Triple pointer that will be reallocated and filled with all the possible combinations of the "dimVector".
 *                           "Dimension *dimVector" -> Holds all the dimensions with each one containing only one attribute, so, for example, there could
 *                                                                      possibly have 3 dimensions of Produto, but each one will have a different attribute
 *                           "Info *verticesInfo" ->  Info structure (package) to hold the vertex information
 *                           "int groupBy" -> Indicates how many dimensions will be inserted on each element (Info structure) of the "verticesInfo" and after
 *                                                     on the "storedVerticesInfo"
 *                           "int *counter" -> Indicates how many elements will be stored on the "storedVerticesInfo"
 *                           "int start" -> Serves as a indicator for where the function's loop should start
 *                           "int end" -> Indicate when the loop should stop
 *                           ""
 *
 **/
void menu_attributeCombination(Info ***storedVerticesInfo, Dimension *dimVector, Info *verticesInfo, int start, int end, int index, int groupBy, int *counter) {

    /* If this is true, means that the wanted group size was formed (size of the combination) */
    if (index == groupBy) {
        /* Store "combined" Info on "storedVerticesInfo" vector */
        menu_storeVertexInfo(storedVerticesInfo, verticesInfo, *(counter));
        (*counter)++;
        return;
    }

    /* Loop counter variable */
    int i;

    /* Goes through the dimVector, getting some of them and calling itself each time to make the combinations */
    for (i = start; i<=end && end-i+1 >= -index; i++) {

        verticesInfo->dimensions[index] = *(utils_copyDimensionWithoutAttrs(&(dimVector[i])));
        verticesInfo->dimensions[index].attrsCounter = 1;
        verticesInfo->dimensions[index].attrs = utils_copyAttribute(dimVector[i].attrs);

        /* Calls itself */
        menu_attributeCombination(storedVerticesInfo, dimVector, verticesInfo, i+1, end, index+1, groupBy, counter);
    }
}


/**
 *
 *  @Funtion: Function to save the user input to the "save.bin" file
 *  @ Parameters: "Info *info" -> Info structure to be saved
 *
 **/
FILE* menu_saveInput(Info *info) {

    /* Counters for the two loops below */
    int i, j;

    /* Stores the size of the "char" type */
    int charSize = sizeof(char);

    /* Open the "save.bin" file */
    FILE *save = fopen("save.bin", "wb");

    /* Iterates over all dimensions */
    for(i = 0; i < info->dimCounter; i++) {

        /* This checks if it can put a delimiter "|" */
        if(i != 0) {
            fwrite("|", charSize, 1, save);
        }

        /* Writes a word to the arquive, in this case is the dimension name */
        utils_writeWord(info->dimensions[i].dimensionName, save);

        /* Writes a word to the arquive, in this case is the dimension abbreviation */
        utils_writeAbbr(info->dimensions[i].abbr, save);

        /* Writes another delimiter to indicate that from this point to the next "|" the words represents the attributes of the preaviusly written dimension */
        fwrite(":", charSize, 1, save);

        /* Get the current Dimension and stores it on a temp variable */
        Dimension *currDim = &(info->dimensions[i]);

        /* Iterates over all the current dimension's attributes */
        for(j = 0; j < info->dimensions[i].attrsCounter; j++) {

            /* Condition to put another delimiter on the file to separate the attributes from themselves */
            if(j != 0) {
                fwrite(",", charSize, 1, save);
            }

            /* Write the attribute name */
            utils_writeWord(currDim->attrs[j].attr, save);

            /* Write the attribute name abbreaviation right after between parentheses */
            utils_writeAbbr(currDim->attrs[j].abbr, save);
        }

    }

    /* Close the file before exiting */
    fclose(save);

    /* returns the created "FILE" pointer */
    return save;
}


/**
 *
 *  @Funtion: Function to create and generate the ".dot" file to latter be user to generate a gaphical graph representation of the gaph in pdf format
 *  @ Parameters: "Graph *g" -> Filled graph where the vertices and edges information will be obtained
 *
 **/
FILE* menu_generateDOT(Graph *g, char *fileName) {

    /* Opens the file that will store the DOT code that will be used to creates the graph image */
    FILE *dotFile = fopen(fileName, "w");

    /* First line indicating the name of my gaph and the type of graph (Name: Data_WareHousing || Graph_type: digraph ) */
    fprintf(dotFile, "digraph Data_Warehousing {\n");

    /* Couter variable for the "for" loob below */
    int i;

    /* Loop that iterates over all edges of the graph */
    for(i = 0; i < g->edgeCount; i++) {

        /* Get the current vertex */
        GraphEdge *currEdge = &g->edges[i];

        /* Get the source vertex of the current edge */
        GraphVertex *source = currEdge->sourceVertex;

        /* Get the destination vertex of the current edge */
        GraphVertex *destination = currEdge->destVertex;

        /* Writes a line on the file indicating a connection between the source vertex and the destination vertex in this direction (source -> dest) */
        fprintf(dotFile, "\t%s -> %s;\n", graph_getVertexAttrsAbbrs(source), graph_getVertexAttrsAbbrs(destination));
    }

    /* Writes a Brace for DOT sintax to work */
    fprintf(dotFile, "}");

    /* Close the opened ".dot" file */
    fclose(dotFile);

    /* Returns the address of the file to the Menu funtion, to store it there */
    return dotFile;
}


/**
 *
 *  @Funtion: Function to access the "save.bin" arquive and print it's registers according to the will of the user
 *  @ Parameters: "FILE *save" -> pointer that holds the address of the file containing the saved input ("save.bin")
 *
 **/
void menu_accessMethod(FILE *save) {

    printf("\n\n%s Do you want to get an specific register or you want to get them all? %s", BOLDWHITE, RESET);
    printf("\n%s Type 'a' for all or 's' for a specific register: %s", BOLDGREEN, RESET);

    /* Get the user input */
    char input;
    scanf("%c", &input);
    utils_removeNBar();


    /* First option: if the user wants to print all the "save.bin" file fields */
    if(input == 'a') {

        /* Calls a method that get all the fields of the "save.bin" file */
        utils_printRegisters(save, NULL, true);

        /* In case the user wants to get an specific field of the file ("save.bin") */
    } else if(input == 's') {

        printf("\n %s Enter the name of the name of the dimension that you want to search: %s ", BOLDWHITE, RESET);

        char *dimName = NULL;
        char frag = '0';
        int i;

        /* Dinamic allocate the dimensionName char array as the user types on the keyboard */
        for(i = 0; (frag = getchar()) != '\n'; i++) {
            dimName = (char*)realloc(dimName, (i+2)*sizeof(char));
            dimName[i] = frag;
        }
        dimName[i] = '\0';

        /* Calls a method that get the wanted field of the "save.bin" file based on the dimName inputed by the user */
        utils_printRegisters(save, dimName, false);

        /* Falls here if the user input was different from the letter 'a' or 's' */
    } else {
        printf("%s \n Could not recognize your input, exiting to main menu %s \n", BOLDYELLOW, RESET);
    }
}

/**
*
*@ Function: Function to generate the ancestors or descendants of the graph and generate a .dot arquive for each of them
*@ Parameters: "Graph *g" -> Graph from wich the ancestors or descendents will be generated
*                         "bool ancestor" -> Configuration boolean, if it is true, the user wants an ancestor
*                         "bool direct" -> Configuration boolean, if it is true, the user wants an direct ancestor or descendant
*
**/
void menu_generateAncestorOrdescendantGraph(Graph *g, bool ancestor, bool direct) {

    /* Vertex array that will store the initial array of ancestors and descendants */
    GraphVertex **storedAnOrDec = NULL;

    /* Counters to indicate the size of the "storedAnOrDec" array and the repetitions that it has */
    int anOrDenCounter = 0;
    int repetitionCounter = 0;

    /* Get the vertex that the user wants */
    Info *fromVertexInfo = utils_createInfoPackage(g->root->info->dimCounter);

    /* Find the wanted vertex on the graph to calculate the ancestors or the descendants */
    GraphVertex *fromVertex = graph_findVertex(g, fromVertexInfo);

    /* Call the recursive funtion according to the user will, to generate the ancestors or descendants of the "fromVertex" */
    /* If "ancestor" is true, enter here */
    if(ancestor == true) {
        graph_findAncestorsWithRepetitions(g,&storedAnOrDec, &anOrDenCounter, fromVertex, direct);

        /* If it's not, enter here */
    } else {
        graph_finddescendantsWithRepetitions(g,&storedAnOrDec, &anOrDenCounter, fromVertex, direct);
    }

    /* Creates another vertex to store the vertices without repetition */
    GraphVertex **allAncestorsOrdescendants = graph_eliminateVertexRepetitions(storedAnOrDec, &anOrDenCounter, &repetitionCounter);

    /* Creates an graph to after generate the dot and the ancestors tree */
    Graph *subAnOrDecGraph = NULL;

    /* Switches between the functions according to the option chosen by the user */
    /* If ancestor, enter here */
    if(ancestor) {

        /* If direct ancestor, enter here */
        if(direct) {
            subAnOrDecGraph = graph_createSubGraph(NULL, fromVertex, allAncestorsOrdescendants,
                                                                                    (anOrDenCounter - repetitionCounter), g->root->info->infoWeight);
            menu_generateDOT(subAnOrDecGraph, "directAncestorsGraph.dot");

            /* If all ancestors, enter here */
        } else {
            subAnOrDecGraph = graph_createSubGraph(g->root, fromVertex, allAncestorsOrdescendants,
                                                                                   (anOrDenCounter - repetitionCounter), g->root->info->infoWeight);
            menu_generateDOT(subAnOrDecGraph, "ancestorsGraph.dot");
        }

        /* If descendant, enter here */
    } else {

        /* If direct descendant, enter here */
        if(direct) {
            subAnOrDecGraph = graph_createSubGraph(NULL, fromVertex, allAncestorsOrdescendants,
                                                                                    (anOrDenCounter - repetitionCounter), g->root->info->infoWeight);
            menu_generateDOT(subAnOrDecGraph, "directDescendantsGraph.dot");

            /* If all  descendants, enter here */
        } else {
            subAnOrDecGraph = graph_createSubGraph(g->bottom, fromVertex, allAncestorsOrdescendants,
                                                                                   (anOrDenCounter - repetitionCounter), g->root->info->infoWeight);
            menu_generateDOT(subAnOrDecGraph, "descendantsGraph.dot");
        }
    }

    /* Print all the vertices of the ancestor or descendant graph */
    graph_printAllVertices(subAnOrDecGraph, fromVertex->info);

    /* Delete the generated graph */
    graph_deleteGraph(subAnOrDecGraph);

}
