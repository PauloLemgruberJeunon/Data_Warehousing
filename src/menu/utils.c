/**
 * Matheus Carvalho Nali - 9313176
 * Bruna Yukari Fujii Yoshida - 9266431
 * Paulo Pinheiro Lemgruber Jeunon Sousa - 9266330
 * Matheus dos Santos Luccas - 9005961
**/

#include "utils.h"
#include <src/consts/printColors.h>
#include <src/consts/bool.h>
#include <src/menu/menu.h>

#include <string.h>

#define STATE_DIMENSION 0
#define STATE_ATTRIBUTE 1

void utils_removeNBar(void) {
    getchar();
}


/* Formated prints with colors ( the collors will only work on linux systems )*/
void utils_printMenuOptions(void) {
    printf("\n\n");
    printf("%s ================================================================= %s\n", BOLDMAGENTA, RESET);
    printf(" %s i -> input the graph %s\n", BOLDGREEN, RESET);
    printf(" %s p -> print the graph connections %s\n", BOLDMAGENTA, RESET);
    printf(" %s r -> read the arquive and obtain the whole graph or part of it %s\n", BOLDBLUE, RESET);
    printf(" %s t -> show the graph as a tree of ancestors and descendants %s\n", BOLDYELLOW, RESET);
    printf(" %s a -> Access registers of the saved input %s\n", BOLDGREEN, RESET);
    printf(" %s h -> print this options again %s\n", BOLDCYAN, RESET);
    printf(" %s e -> exit the program %s\n", BOLDRED, RESET);
    printf("%s ================================================================= %s\n", BOLDMAGENTA, RESET);
    printf("\n\n");
}


/**
*
* @Function: This function has the objective to copy the information of a Dimension without coping it's attributes. Then it will return the new copied
*                    Dimension to the caller function
* @Parameters: "Dimension *toCopy" -> Dimension that will be copied to an dynamically allocated Dimension
*
**/
Dimension* utils_copyDimensionWithoutAttrs(Dimension *toCopy) {

    /* Allocates the new Dimension */
    Dimension *dim = (Dimension*)malloc(sizeof(Dimension));
    dim->abbr = (char*)malloc(strlen(toCopy->abbr)+1);
    dim->dimensionName = (char*)malloc(strlen(toCopy->dimensionName)+1);

    /* Copies the "toCopy" dimension content to the "dim" Dimension */
    strcpy(dim->abbr, toCopy->abbr);
    strcpy(dim->dimensionName, toCopy->dimensionName);

    return dim;
}


/**
*
* @Function: This function has the objective to copy the information of an Attribute. Then it will return the new copied
*                    Attribute to the caller function
* @Parameters: "Attribute *toCopy" -> The Attribute that will be copied to an dynamically allocated Attribute
*
**/
Attribute* utils_copyAttribute(Attribute *toCopy) {

    /* Allocates the new Attribute */
    Attribute *attr = (Attribute*)malloc(sizeof(Attribute));
    attr->abbr = (char*)malloc(strlen(toCopy->abbr)+1);
    attr->attr = (char*)malloc(strlen(toCopy->attr)+1);

    /* Copies the "toCopy" dimension content to the "attr" Attribute */
    strcpy(attr->abbr, toCopy->abbr);
    strcpy(attr->attr, toCopy->attr);
    attr->weight = toCopy->weight;

    return attr;
}


/**
*
* @Function: Asks and gets the user's input from the keyboard. All the input is dynamically allocated as the user types, so it only consume the
*                    necessary amount of memory
* @Parameters: none
*
**/
Info* utils_startInput() {
    printf("\n");

    /* Allocates the Info structs */
    Info *input = (Info*)malloc(sizeof(Info));

    /* Sets the Dimension vector from the input to NULL for the realloc function below */
    input->dimensions = NULL;

    /* Creates a Dimension vector to stores the dimensions */
    Dimension *dimVec = NULL;

    printf("%s Enter the dimensions that you want in the graph below %s \n", BOLDWHITE, RESET);

    /* Store the chosen option by the user below */
    char option = '0';

    /* Sets a default value */
    input->dimCounter = 0;

    /* This while is reponsible to get the dimensions from the user, and allocate the 'dimension' struct */
    while(true) {
        printf("\n%s To add another %s dimension %s enter %s 'd' %s and to %s stop %s adding enter %s 's'%s: %s ", BOLDWHITE, BOLDRED, BOLDWHITE, BOLDRED, BOLDWHITE,
                                                                                                                                                                                    BOLDYELLOW, BOLDWHITE, BOLDYELLOW, BOLDWHITE, RESET);
        scanf("%c", &option);
        utils_removeNBar();

        /* In case the user do not want to add any more dimension */
        if(option == 's') {
            break;
        }

        input->dimCounter++;
        dimVec = (Dimension*)realloc(dimVec, input->dimCounter*sizeof(Dimension));

        printf("\n%s Enter with %sdimension%s %d:  %s", BOLDWHITE, BOLDRED, BOLDWHITE, input->dimCounter, RESET);
        int i;
        char frag = '0';
        Dimension *currDim = &(dimVec[input->dimCounter-1]);
        currDim->dimensionName = NULL;

        /* Dinamic allocate the dimensionName char array as the user types on the keyboard */
        for(i = 0; (frag = getchar()) != '\n'; i++) {
            currDim->dimensionName = (char*)realloc(currDim->dimensionName, (i+2)*sizeof(char));
            currDim->dimensionName[i] = frag;
        }
        currDim->dimensionName[i] = '\0';

        /* Allocates the abbreviation of the dimension's name */
        currDim->abbr = utils_getAbbreviation(currDim->dimensionName);
    }

    printf("%s \n Now that your have entered the %sdimensions%s, enter their %sattributes%s in %sdecreasing order of granularity %s \n\n", BOLDWHITE,
                                                                                                                                    BOLDRED, BOLDWHITE, BOLDMAGENTA, BOLDWHITE, BOLDCYAN, RESET);

    int i;
    /* This 'for' is responsible to make possible for the user to add attributes to any dimension he/she had entered above */
    for(i = 0; i < input->dimCounter; i++) {
        Dimension *currDim = &(dimVec[i]);
        printf("\n%s The current %sdimension%s is %s %s %s, Enter the %sattributes%s for it below %s \n", BOLDWHITE, BOLDRED,
                                                                       BOLDWHITE, BOLDRED, currDim->dimensionName, BOLDWHITE, BOLDMAGENTA, BOLDWHITE, RESET);

        currDim->attrs = NULL;

        currDim->attrsCounter = 0;
        /* This while lets the user insert as many attributes he wants in the current dimension */
        while(true) {            

            printf("\n%s To add another %sattribute%s enter %s'a'%s and to %sstop%s adding enter %s's'%s: %s ", BOLDWHITE, BOLDMAGENTA, BOLDWHITE, BOLDMAGENTA,
                                                                                                       BOLDWHITE, BOLDYELLOW, BOLDWHITE, BOLDYELLOW, BOLDWHITE, RESET);
            scanf("%c", &option);
            utils_removeNBar();

            if(option == 's') {
                break;
            }

            currDim->attrsCounter++;

            currDim->attrs = (Attribute*)realloc(currDim->attrs, currDim->attrsCounter*sizeof(Attribute));

            Attribute *currAttr = &(currDim->attrs[currDim->attrsCounter-1]);
            currAttr->attr = NULL;
            currAttr->abbr = NULL;
            currAttr->weight = currDim->attrsCounter - 1;

            printf("\n%s Enter with %sattribute%s %d:  %s", BOLDWHITE, BOLDMAGENTA, BOLDWHITE, currDim->attrsCounter, RESET);

            int j;
            char frag = '0';
            /* Allocates the attributes name array as the user types */
            for(j = 0; (frag = getchar()) != '\n'; j++) {
                currAttr->attr = (char*)realloc(currAttr->attr, (j+2)*sizeof(char));
                currAttr->attr[j] = frag;
            }
            currAttr->attr[j] = '\0';

            /*  Allocates the abbreviation of the attribute's name */
            currAttr->abbr = utils_getAbbreviation(currAttr->attr);
        }
    }

    input->dimensions = dimVec;

    return input;
}


/**
*
* @Function: Creates an Dimension vector that stores Dimensions with only one attribute, so the inputInfo dimension are separated in a lot of other
*                      Dimensions each one with only one attribute
* @Parameters: "Info *inputInfo" -> Info that have the dimensions that need to be fragmented. For example: Produto:all,marca,produto -> Produto:all
*                                                        Produto:marca  Produto:produto
*
**/
Dimension* utils_separateDimensions(Info *inputInfo) {

    /* Creates the separate dimension vector that will be returned and will contain the separates dimensions */
    Dimension *dimensionVector = NULL;
    int dimensionsSize = inputInfo->dimCounter;

    /* Counter variables that will be used by the two loops below and a general counter to count the total size of the "dimensionVector" */
    int i, j, counter = 0;

    /* Iterates over all dimensions on the "inputInfo" variable */
    for(i = 0; i < dimensionsSize; i++) {

        /* Gets the current dimension */
        Dimension *currDim = &(inputInfo->dimensions[i]);

        /* Get the size of the current dimension attributes */
        int attrsSize = currDim->attrsCounter;

        /* Iterates over all the attributes of the "currDim" */
        for(j = 0; j < attrsSize; j++, counter++){

            dimensionVector = (Dimension*)realloc(dimensionVector, (counter+1)*sizeof(Dimension));

            /* Adds a new Dimension for each attribute and copies the content from the "inputInfo" to this "dimensionVector" array */
            dimensionVector[counter] = *(utils_copyDimensionWithoutAttrs(currDim));
            dimensionVector[counter].attrsCounter = 1;
            dimensionVector[counter].attrs = utils_copyAttribute(&(currDim->attrs[j]));
        }
    }

    /* Returns the generated dimension vector */
    return dimensionVector;
}


/**
*
* @Function: Creates a copy of an Info structure including all it has inside
* @Parameters: "Info *src" -> Info structure to be copied
*
**/
Info* utils_copyInfo(Info *src) {

    Info *dest = NULL;
    dest = (Info*)malloc(sizeof(Info));

    dest->dimCounter = src->dimCounter;
    dest->dimensions = (Dimension*)malloc(dest->dimCounter*sizeof(Dimension));

    int i;
    for(i = 0; i < dest->dimCounter; i++) {
        dest->dimensions[i] = *(utils_copyDimensionWithoutAttrs(&src->dimensions[i]));
        dest->dimensions[i].attrsCounter = 1;
        dest->dimensions[i].attrs = utils_copyAttribute(&src->dimensions[i].attrs[0]);
    }

    dest->infoWeight = src->infoWeight;

    return dest;
}


/**
*
* @Function: Throws away the Infos that have two or more dimensions structures with the same dimension. For example: Produto:all & Produto:marca
*                      inside the same Info structure.
* @Parameters: "Info **storedVerticesInfo" -> Info structure vector that contains, in the beginning Info packages with 2 or more equal dimensions
*                         "int infoSize" ->  The size of the "storedVerticesInfo"
*                         "int groupBy" -> The number of dimensions inside each Info structure on the "storedVerticesInfo" array
*                         "int *biggestWeight" - > Variable to count and hold the biggestWeight on a Info structure package (used latter by the
*                                                                caller of this function)
*
**/
void utils_cleanTrashInfo(Info **storedVerticesInfo, int infoSize, int groupBy, int *biggestWeight) {

    /* Counters for the two firsts "for" loops below */
    int i, j;

    /* Condition to stop comparring the names of the dimensions because it already has found that they are trash infos */
    bool stopCondition = false;

    /* Iterates over all Info structures inside "storedVerticesInfo" array */
    for(i = 0; i < infoSize; i++) {

        /* Get currente Info */
        Info* currInfo = storedVerticesInfo[i];

        /* Resets the "stopCondition" value */
        stopCondition = false;
        for(j = 0; j < groupBy; j++) {

            /* Checks if it has to stop comparring */
            if(stopCondition) {
                break;
            }

            /* Get the current dimension name */
            char *currDimName = currInfo->dimensions[j].dimensionName;

            /* Counter for the "for" loop below*/
            int k;

            /* Iterates over all dimensions of the currInfo "Info" structure */
            for(k = j+1; k < groupBy; k++) {

                /* Checks if there is two dimensions with the same name inside the same info structure */
                if(strcmp(currDimName, currInfo->dimensions[k].dimensionName) == 0) {
                    storedVerticesInfo[i] = NULL;
                    stopCondition = true;
                    break;
                }
            }
        }
    }

    /* At the end calls a function to give the Info packages a weight according to their attributes */
    utils_setInfoWeights(storedVerticesInfo, infoSize, groupBy, biggestWeight);
}


/* Set the infoWeight of all infos inside the storedVerticesInfo */
/**
*
* @Function: Set the infoWeight of all infos inside the "storedVerticesInfo" variable
* @Parameters: "Info **storedVerticesInfo" -> Stores the informations strcutures that will go into the Vertices of the future graph
*                         "int infoSize" -> Size of the "storedVerticesInfo" array
*                         "int groupBy" -> Number of dimensions inside each info structure
*                         "int *biggestWeight" -> Calculate and hold the value of the biggest Info weight inside the "storedVerticesInfo" array
*
**/
void utils_setInfoWeights(Info **storedVerticesInfo, int infoSize, int groupBy, int *biggestWeight) {

    /* Couters for the "for" loops below */
    int i, j;

    /* Sets a minimum value to the "biggestWeight" variable */
    *biggestWeight = -1;

    /* Iterates over all Info elements of the "stor*                         "char *color" -> color that you want to the information to be printededVerticesInfo" array */
    for(i = 0; i < infoSize; i++) {

        /* Holds the current Info */
        Info *currInfo = storedVerticesInfo[i];

        /* See if it was erased */
        if(currInfo == NULL) {
            continue;
        }

        /* Sets a default weight to the Info */
        currInfo->infoWeight = 0;

        /* Iterates over all dimensions of the "currInfo" variable */
        for(j = 0; j < groupBy; j++) {

            /* Gets the weight of each one and sum it to the Info total weight */
            Dimension *currDimension = &(currInfo->dimensions[j]);
            currInfo->infoWeight += currDimension->attrs->weight;
        }

        /* Checks if the biggestWeight is outdated */
        if(currInfo->infoWeight > (*biggestWeight)) {
            (*biggestWeight) = currInfo->infoWeight;
        }
    }
}


/**
*
* @Function: Prints on the screen the information inside a Info structure
* @Parameters: "Info *info" -> Info structure to be printed
*                         "char *color" -> color that you want to the information to be printed
*
**/
void utils_printInfo(Info *info, char *color) {
    int i;

    /* checks if the information is not a null Pointer */
    if(info == NULL) {
        printf(" NULL\n\n");
        return;
    }

    printf("\n %sVertex Information:%s \n", BOLDYELLOW, RESET);

    /* Iterates over all dimensions of the information and print them on the terminal */
    for(i = 0; i < info->dimCounter; i++) {
        printf("%s Dimension name = %s %s\n", color, info->dimensions[i].dimensionName, RESET);
        printf("%s Attribute = %s %s\n", color, info->dimensions[i].attrs[0].attr, RESET);
        printf("%s Attr weight = %d %s\n\n", color, info->dimensions[i].attrs[0].weight, RESET);
    }
    printf("\n %s-----------------------------------------------------------------------------------------%s \n", BOLDMAGENTA, RESET);
}


/**
*
* @Function: Writes on the correct format an abbreviation to an arquive
* @Parameters: "char *abbr" -> holds the name to be written
*                         "FILE *file" -> Holds an opened file to where the string should be written to
*
**/
void utils_writeAbbr(char *abbr, FILE *file) {
    fwrite("(", sizeof(char), 1, file);
    utils_writeWord(abbr, file);
    fwrite(")", sizeof(char), 1, file);
}


/**
*
* @Function: Writes a word to an arquive
* @Parameters: "Info *info" -> Word to be written
*                         "char *color" -> Holds an opened file to where the word should be written to
*
**/
void utils_writeWord(char *word, FILE *file) {
    int size = strlen(word);
    fwrite(word, sizeof(char), size, file);
}


/**
*
* @Function: Function that works, based on a state machine, to read the information of the "save.bin" file, containing the user saved input, and
*                     allocating this information on a structure to be turned into a graph latter
* @Parameters: "FILE *file" -> File address containing the information to be read
*
**/
Info* utils_readSavedInput(FILE *file) {

    /* Allocates the Info structure */
    Info *input = (Info*)malloc(sizeof(Info));

    /* Allocates the dimension array for a first element and set default values to other variables*/
    input->dimCounter = 0;
    input->dimensions = (Dimension*)malloc(sizeof(Dimension));
    input->infoWeight = 0;

    /* Checks if the file exists */
    if(file == NULL) {
        printf("%s [WARNING] file pointer == NULL %s \n", BOLDRED, RESET);
    }

    /* Creates support variables for the state machine below and set some default values to them */
    char letter = '0';
    int charSize = sizeof(char);
    int state = STATE_DIMENSION;
    int letterCount = 0;

    /* Creates variables to hold the currDimension and Attribute */
    Dimension *currDim = &(input->dimensions[0]);
    currDim->dimensionName = NULL;
    Attribute *currAttr = NULL;


    /* Loop that will interate until the end of the file (EOF) */
    while(true) {

        /* Read only one character of the file at a time */
        fread(&letter, charSize, 1, file);

        /* Checks if the end of file was reached */
        if(feof(file)!=0) {

            /* The file alwyas end in a attribute, so the opperations below are for finishing the last attribute of the arquive */
            utils_finishAnAttribute(currAttr, currDim, charSize, letterCount);

            break;
        }

        /* Switch function to enter in the correct state of the state machine */
        switch(state) {

            /* State Dimension: Is the current state when the function is reading a dimension, and stops when find a ':' char */
            case STATE_DIMENSION: {

                /* Ignores the abbreviations, bacause they will be regenerated again latter for simplicity and checks if it reached the end of file */
                if(utils_passThroughAbbr(file, &letter, charSize) == true) {
                    break;
                }

                /* Checks if it has reached a ':' char, if so it will change the state to STATE_ATTRIBUTE */
                if(letter == ':') {

                    /* Puts a '\0' char in the end of the string */
                    currDim->dimensionName = (char*)realloc(currDim->dimensionName, (letterCount+1)*charSize);
                    currDim->dimensionName[letterCount] = '\0';

                    /* switch the state */
                    state = STATE_ATTRIBUTE;

                    /* Resets the letterCount */
                    letterCount = 0;

                    /* Get the abbreviation for the name of the dimension */
                    input->dimensions[input->dimCounter].abbr = utils_getAbbreviation(input->dimensions[input->dimCounter].dimensionName);

                    /* Allocates the first attribute of the dimension and set the "currAttr" pointer to that position */
                    currDim->attrs = (Attribute*)malloc(sizeof(Attribute));
                    currDim->attrsCounter = 0;
                    currAttr = &(currDim->attrs[0]);
                    currAttr->attr = NULL;
                    break;
                }

                /* Reallocates the "dimensionName" and inserts a letter inside it */
                currDim->dimensionName = (char*)realloc(currDim->dimensionName, (letterCount+1)*charSize);
                currDim->dimensionName[letterCount] = letter;
                letterCount++;

            } break;

            /* State Attribute: Is the current state when the function is reading an Attribute, and stops when find a '|' char */
            case STATE_ATTRIBUTE: {

                /* Ignores the abbreviations, bacause they will be regenerated again latter for simplicity and checks if it reached the end of file */
                if(utils_passThroughAbbr(file, &letter, charSize) == true) {
                    break;
                }

                /* Checks if it has reached the '|' , if so the state need to prepare itself to change the state back to the STATE_DIMENSION */
                if(letter == '|') {

                    /* Finishes the current attribute */
                    utils_finishAnAttribute(currAttr, currDim, charSize, letterCount);

                    /* Switch the state */
                    state = STATE_DIMENSION;

                    /* Increases the dimCounter variable*/
                    input->dimCounter++;

                    /* Reallocatees a new dimension on the Info's dimension array */
                    input->dimensions = (Dimension*)realloc(input->dimensions, (input->dimCounter+1)*sizeof(Dimension));

                    /* Updates the currDImension */
                    currDim = &(input->dimensions[input->dimCounter]);
                    currDim->dimensionName = NULL;

                    /* Resets letter count */
                    letterCount = 0;
                    break;
                }

                /* Checks if it has reached the ',' , if so the state need to prepare itself to start reading another attribute */
                if(letter == ',') {

                    /* Finishes the current attribute */
                    utils_finishAnAttribute(currAttr, currDim, charSize, letterCount);

                    /* Reallocates the current dimension's attribute array, reset and set some default values */
                    currDim->attrs = (Attribute*)realloc(currDim->attrs, (currDim->attrsCounter+1)*sizeof(Attribute));
                    currAttr = &(currDim->attrs[currDim->attrsCounter]);
                    currAttr->attr = NULL;
                    letterCount = 0;
                    break;
                }

                /* Reallocates the name of the attribute and inserts a letter inside it */
                currAttr->attr = (char*)realloc(currAttr->attr, (letterCount+1)*charSize);
                currAttr->attr[letterCount] = letter;
                letterCount++;

            } break;

        }

    }

    /* Count the last dimension*/
    input->dimCounter++;

    /* Return the obtained input to the caller */
    return input;
}


/**
*
* @Function: Support function for the "utils_readSavedInput". Finishes and attribute with some values
* @Parameters: "Attribute *currAttr" -> Current attribute to be finalized
*                         "Dimension *currDim" -> Current Dimension to give some necessary values and have the attrs couter increased
*                         "int charSize" -> The size of the "char" type
*                         "int letterCount" -> The size of the name of the attribute
*
**/
void utils_finishAnAttribute(Attribute *currAttr, Dimension *currDim, int charSize, int letterCount) {

    /* Gets the abbreviation for the attribute's name */
    currAttr->abbr = utils_getAbbreviation(currAttr->attr);

    /* Sets the weight of the attribute */
    currAttr->weight = currDim->attrsCounter;

    /* Reallocate the name of the attribute to insert a '\0' character in the end */
    currAttr->attr = (char*)realloc(currAttr->attr, (letterCount+1)*charSize);
    currAttr->attr[letterCount] = '\0';

    /* Increases the attributes counter of the current Dimension*/
    currDim->attrsCounter++;
}


/**
*
* @Function: Ignores the atrtibute on an arquive when find one
* @Parameters: "FILE *file" -> File to be read
*                         "char *letter" -> Character to hold the current char read from the arquive
*                         "int charSize" -> Stores the size of the "char" type
*
**/
bool utils_passThroughAbbr(FILE *file, char *letter, int charSize) {

    /* Checks if it has found an abbreviation */
    if((*letter) == '(') {

        /* Iterates to the end of the abbreviation */
        while(true) {

            /* Read one char of the arquive */
            fread(letter, charSize, 1, file);

            /* Checks if it has found the end of the abbreviation */
            if((*letter) == ')') {
                break;
            }
        }

        /* Read one last char of the arquive */
        fread(letter, charSize, 1, file);
    }

    /* Checks if it has reached the end of file */
    if(feof(file) != 0) {
        return true;
    }

    /* Returns false in case the end of file has not been reached */
    return false;
}


/**
*
* @Function: Creates an abbreviation of an word
* @Parameters: "char *word" -> Word to be abbreviated
*
**/
char* utils_getAbbreviation(char *word) {

    /* Counter for the "for" loop below */
    int j;

    /* variable to hold the generated abbreviation */
    char *abbr = NULL;

    /*Iterates 3 times*/
    for(j = 0; j < 3; j++) {

        /* Get the first 3 letters of a word and turn them into an abbreviation*/
        char currLetter = word[j];
        abbr = (char*)realloc(abbr, (j+2)*sizeof(char));

        /* If the word has less than 3 letters puts an zero at the end of it */
        if(currLetter == '\0') {
            abbr[j] = '0';
        } else {
            abbr[j] = word[j];
        }
    }

    /* Puts an '\0' to indicate the end of the string */
    abbr[j] = '\0';

    /* Return the abreviation */
    return abbr;
}


/**
*
* @Function: Prints on the screen the register of the saved input file ("save.bin")
* @Parameters: "FILE *file" -> file to have the register read from
*                         "char *dimName" -> Can contain the wanted dimension name of the register
*                         "bool all" -> indicates if the user wants to print all the registers
*
**/
void utils_printRegisters(FILE *file, char *dimName, bool all) {


    /* If all == to true enter here */
    if(all) {

        /* Prints the first file register */
        char option;
        printf("\n %s %s %s \n", BOLDGREEN, utils_getOneRegister(file), RESET);

        /* Loop to print other registers*/
        while(true) {

            /* Checks if the end of the file has been reached */
            if(feof(file) != 0) {
                break;
            }


            /* Asks if the user wants to get another register from the arquive */
            printf("\n %s Do you want to print the next register or exit? %s \n", BOLDWHITE, RESET);
            printf("\n %s Press %s 'e' %s to exit or %s 'c' %s to continue:  %s", BOLDWHITE, BOLDRED, BOLDWHITE, BOLDGREEN, BOLDWHITE, RESET);
            scanf("%c", &option);
            utils_removeNBar();

            /* If yes ('c') enters here and print another register */
            if(option == 'c') {
                printf("\n %s %s %s \n", BOLDGREEN, utils_getOneRegister(file), RESET);

                /* If no ('e') exit the function here */
            } else if(option == 'e') {
                break;

                /* In case the option choosed was not reconizable */
            } else {
                printf("\n Could not comprehend the input typed... try again \n");
            }
        }

        /* If the user wants to print an specific register */
    } else {

        /* Creates some support variables */
        char *frag = NULL;
        char *reg = NULL;
        bool foundDim = false;
        int charSize = sizeof(char);

        /* Loop to find the wanted register based on the wanted dimension name ("dimName") */
        while(true) {

            /* Cheks if it has reached the end of the file or has found the wanted dimension */
            if(feof(file) != 0 || foundDim == true) {
                break;
            }

            /* Get one register from the arquive*/
            reg = utils_getOneRegister(file);

            /* allocates the right size for the "frag" support variable */
            frag = (char*)realloc(frag, (strlen(reg)+1)*charSize);

            /* Copie the content of the "reg" string to the "frag" string */
            strcpy(frag, reg);

            /* Get the piece of the frag string, containing the dimension name */
            frag = strtok(frag, "(");

            /* Compares the wanted dimension name with the curr register frag name (which is the dimension name of the curr register)
                 and if is the same name, print the register, if not keep searching */
            if(strcmp(frag, dimName) == 0) {
                printf("\n %s %s %s \n", BOLDGREEN, reg, RESET);

                /* Set that the dimension was already found */
                foundDim = true;
            }
        }

        /* In case the dimension was not found */
        if(foundDim == false) {
            printf("\n%s Could not found the wanted dimension... verify your input... %s", BOLDRED, RESET);
        }
    }
}


/**
*
* @Function: Get one register from the "save.bin" file
* @Parameters: "FILE *file" -> file to read and get the save from
*
**/
char *utils_getOneRegister(FILE *file) {

    /* Support variables */
    int letterCounter = 0;
    int charSize = sizeof(char);

    /* Letter to store the read char from the arquive */
    char *letter = (char*)malloc(charSize);
    *letter = '0';

    /* Pointer to store the entire register */
    char *reg = NULL;

    /* Read the first char and put it into letter */
    fread(letter, charSize, 1, file);

    /* Iterates over all the register */
    while(true) {

        /* Checks if it has reached the end of file or it has found the end of the register */
        if(feof(file) != 0 || (*letter) == '|') {
            /* Exit the loop */
            break;
        }

        /* Reallocates the reg string and insert a letter to the end of it */
        reg = (char*)realloc(reg, (letterCounter+2)*charSize);
        reg[letterCounter] = (*letter);
        letterCounter++;

        /* Read another char of the arquive */
        fread(letter, charSize, 1, file);
    }

    /* Insert a '\0' character to indicate the end of the string */
    reg[letterCounter] = '\0';

    /* return the register */
    return reg;
}


Info* utils_createInfoPackage(int groupBy) {

    printf("\n%s Enter with %s(all of the dimentions)%s %d dimensions and %sONE%s attribute for each dimension after %s \n", BOLDWHITE,
                                                                                                                       BOLDYELLOW, BOLDWHITE, groupBy, BOLDRED, BOLDWHITE, RESET);
    printf("%s Obs: the order that you insert the attributes does not matter. %s \n", BOLDGREEN, RESET);

    return utils_startInput();

}


/* DEBBUGING FUNCTION */
Info* utils_autoInput(void) {
    Info *info = (Info*)malloc(sizeof(Info));

    info->dimCounter = 3;
    info->dimensions = (Dimension*)malloc(3*sizeof(Dimension));

    Dimension *currDim = &info->dimensions[0];
    currDim->dimensionName = "Produto";
    currDim->abbr = "Pro";

    currDim->attrs = (Attribute*)malloc(3*sizeof(Attribute));
    currDim->attrsCounter = 3;


    Attribute *currAttr = &currDim->attrs[0];
    currAttr->attr = "all";
    currAttr->abbr = "all";
    currAttr->weight = 0;

    currAttr = &currDim->attrs[1];
    currAttr->attr = "marca";
    currAttr->abbr = "mar";
    currAttr->weight = 1;

    currAttr = &currDim->attrs[2];
    currAttr->attr = "produto";
    currAttr->abbr = "pro";
    currAttr->weight = 2;

/* ---------------------------------------------------------------------------------------------------------------- */

    currDim = &info->dimensions[1];
    currDim->dimensionName = "Local";
    currDim->abbr = "Loc";

    currDim->attrs = (Attribute*)malloc(4*sizeof(Attribute));
    currDim->attrsCounter = 4;

    currAttr = &currDim->attrs[0];
    currAttr->attr = "all";
    currAttr->abbr = "all";
    currAttr->weight = 0;

    currAttr = &currDim->attrs[1];
    currAttr->attr = "estado";
    currAttr->abbr = "est";
    currAttr->weight = 1;

    currAttr = &currDim->attrs[2];
    currAttr->attr = "cidade";
    currAttr->abbr = "cid";
    currAttr->weight = 2;

    currAttr = &currDim->attrs[3];
    currAttr->attr = "filial";
    currAttr->abbr = "fil";
    currAttr->weight = 3;

/* ---------------------------------------------------------------------------------------------------------------- */

    currDim = &info->dimensions[2];
    currDim->dimensionName = "Tempo";
    currDim->abbr = "Tem";

    currDim->attrs = (Attribute*)malloc(3*sizeof(Attribute));
    currDim->attrsCounter = 3;

    currAttr = &currDim->attrs[0];
    currAttr->attr = "all";
    currAttr->abbr = "all";
    currAttr->weight = 0;

    currAttr = &currDim->attrs[1];
    currAttr->attr = "mes";
    currAttr->abbr = "mes";
    currAttr->weight = 1;

    currAttr = &currDim->attrs[2];
    currAttr->attr = "dia";
    currAttr->abbr = "dia";
    currAttr->weight = 2;

    return info;
}
