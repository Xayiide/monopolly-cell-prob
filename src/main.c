#include <stdio.h>
#include <stdlib.h> /* exit, EXIT_FAILURE, strtoul, srand */
#include <stdint.h> /* uint_t */
#include <time.h>   /* time   */

#include <unistd.h> /* sleep  */

#include "inc/monopoly.h"

int main(int argc, char *argv[])
{
    uint64_t num_tiradas = 0;
    uint64_t lista_caidas[MONOPOLY_NUM_CASILLAS] = { 0 };
    uint64_t i;
    int      posicion = 0;
    int      dados[2];
    int      tirada_dados;
    int      dobles_seguidos = 0;
    //uint64_t ultimo_doble = 0;

    if (argc != 2) {
        fprintf(stderr, "uso: %s <num tiradas>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    num_tiradas = strtoul(argv[1], NULL, 10);

    srand(time(NULL));

    // Imprimir el array
    // for (i = 0; i < MONOPOLY_NUM_CASILLAS; i++)
    //     printf("[%02d] %s\n", i, monopoly_casillas[i]);

    for (i = 0; i < num_tiradas; i++) {
        dados[0] = (rand() % 6) + 1;
        dados[1] = (rand() % 6) + 1;

        if (dados[0] == dados[1]) { /* dobles */
            dobles_seguidos++;           
        }
        else {
            dobles_seguidos = 0;
        }


        if (dobles_seguidos == 3) {
            posicion = 10; /* Nos vamos a la cárcel por tres dobles seguidos */
            lista_caidas[posicion]++;
            //printf("[%ld] Han salido tres dobles %d seguidos. "
            //        "El último hace %ld tiradas.\n",
            //        i, dados[0], i - ultimo_doble);
            //ultimo_doble = i;
            continue;
        }

        tirada_dados = dados[0] + dados[1];
        posicion = (posicion + tirada_dados) % MONOPOLY_NUM_CASILLAS;
        lista_caidas[posicion]++;

        if (posicion == 30) { /* ir a la cárcel */
            posicion = 10;
        }
    }

    for (i = 0; i < MONOPOLY_NUM_CASILLAS; i++) {

        printf("[%ld = %0.4f%%] %s\n", lista_caidas[i], 
                                ((lista_caidas[i] * 1.0) / num_tiradas) * 100,
                                monopoly_casillas[i]);
    }

    return 0;
}
