/**
 * Matheus Carvalho Nali - 9313176
 * Bruna Yukari Fujii Yoshida - 9266431
 * Paulo Pinheiro Lemgruber Jeunon Sousa - 9266330
 * Matheus dos Santos Luccas - 9005961
**/

#ifndef MENU_H
#define MENU_H

#include <src/consts/bool.h>
#include <src/menu/utils.h>
#include <src/graph/graph.h>

/* The main function to select and manage the functionalities of the program*/
void menu(void);

/* The functions commentaries are on the ".c" file of the same name (menu.c) */

void menu_attributeCombination(Info ***storedVerticesInfo, Dimension *dimVector, Info *verticesInfo, int start, int end, int index, int groupBy, int *counter);
void menu_storeVertexInfo(Info ***storedVerticesInfo, Info *verticesInfo, int counter);
Info* menu_inputMethod(Graph *g, Info *inputInfo);
FILE* menu_saveInput(Info *info);
FILE* menu_generateDOT(Graph *g, char *fileName);
void menu_accessMethod(FILE *save);
void menu_generateAncestorOrdescendantGraph(Graph *g, bool ancestor, bool direct);

#endif /* MENU_H */

