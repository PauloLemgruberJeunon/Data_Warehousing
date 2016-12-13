/**
 * Matheus Carvalho Nali - 9313176
 * Bruna Yukari Fujii Yoshida - 9266431
 * Paulo Pinheiro Lemgruber Jeunon Sousa - 9266330
 * Matheus dos Santos Luccas - 9005961
**/

#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <src/consts/bool.h>


typedef struct attribute {
    char *attr; /* Attribute's name */
    char *abbr; /* Abbreviation */
    int weight; /* Weight of the attribute (higher the weight, lower the granularity) */
} Attribute;

typedef struct dimension {
    char *dimensionName  /* Dimension's name */;
    char *abbr;                   /* Abbreviatoin */
    Attribute *attrs;            /* Attributes */
    int attrsCounter;         /* Counter of the number onf Attributes inside the dimension */
} Dimension;

typedef struct inputInfo {
    Dimension *dimensions; /* Dimensions array */
    int dimCounter; /* stores the number of dimensions */
    int infoWeight;  /* Weight associated with all the info (sum of the weights of the attributes) */
} Info;


/* Functions */
/* Documentation on the .c file (utils.c) */
void utils_removeNBar(void);
void utils_printMenuOptions(void);
Info *utils_startInput();
Dimension* utils_copyDimensionWithoutAttrs(Dimension *toCopy);
Attribute* utils_copyAttribute(Attribute *toCopy);
Dimension *utils_separateDimensions(Info *inputInfo);
Info *utils_copyInfo(Info *src);
void utils_cleanTrashInfo(Info **storedVerticesInfo, int infoSize, int groupBy, int *biggestWeight);
void utils_setInfoWeights(Info **storedVerticesInfo, int infoSize, int groupBy, int *biggestWeight);
void utils_printInfo(Info *info, char *color);
void utils_writeWord(char *word, FILE *file);
Info* utils_autoInput(void);
char* utils_getAbbreviation(char *word);
Info* utils_readSavedInput(FILE *file);
char *utils_getOneRegister(FILE *file);
void utils_printRegisters(FILE *file, char *dimName, bool all);
void utils_writeAbbr(char *abbr, FILE *file);
bool utils_passThroughAbbr(FILE *file, char *letter, int charSize);
void utils_finishAnAttribute(Attribute *currAttr, Dimension *currDim, int charSize, int letterCount);
Info* utils_createInfoPackage(int groupBy);

#endif /* UTILS_H */
