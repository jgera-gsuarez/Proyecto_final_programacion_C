#include <stdio.h>
#include "app.h"

int main() {
    int opcion;
    do
    {
        printf("\n=== Aplicación Decaimiento Exponencial ===\n");
        printf("1. Calcular y simular\n");
        printf("2. Graficar datos\n");
        printf("3. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                calcular();
				simular();
                break;
            case 2:
                graficar_csv("Resultados/simulacion.csv", "Resultados/grafica.png");
                break;
            case 3:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción inválida.\n");
        }
    } while(opcion != 3);

    return 0;
}