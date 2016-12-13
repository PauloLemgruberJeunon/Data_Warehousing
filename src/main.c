/**
 * Matheus Carvalho Nali - 9313176
 * Bruna Yukari Fujii Yoshida - 9266431
 * Paulo Pinheiro Lemgruber Jeunon Sousa - 9266330
 * Matheus dos Santos Luccas - 9005961
**/

#include <src/consts/printColors.h>
#include <src/consts/bool.h>
#include <src/graph/graph.h>
#include <src/menu/menu.h>
#include <src/menu/utils.h>

/* Program starts here */
int main (void) {

    /* Prints the first menu options */
    utils_printMenuOptions();

    /* Starts the menu funcion for the user choose the functionality he wants */
    menu();

    return 0;
}
