#include <stdio.h>
#include <stdlib.h>

int main() {
    // Comando para GNUplot
    FILE *gnuplot = popen("gnuplot -persistent", "w");
    if (gnuplot) {
        fprintf(gnuplot, "set title 'Decaimiento Exponencial'\n");
        fprintf(gnuplot, "set xlabel 'Tiempo'\n");
        fprintf(gnuplot, "set ylabel 'Cantidad'\n");
        fprintf(gnuplot, "plot 'datos.csv' using 1:2 with lines title 'Descomposición'\n");
        pclose(gnuplot);
    } else {
        printf("Error al abrir GNUplot.\n");
    }
    return 0;
}