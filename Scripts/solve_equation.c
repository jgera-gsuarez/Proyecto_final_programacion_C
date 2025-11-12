#include <stdio.h>
#include <math.h>

int main() {
    double M0, Mt, t_medida, tiempo_total, dt;
    double k, M;
    FILE *archivo;

    // Entradas
    printf("Ingrese masa inicial (M0): ");
    scanf("%lf", &M0);
    printf("Ingrese masa medida (Mt): ");
    scanf("%lf", &Mt);
    printf("Ingrese tiempo en que se midio Mt: ");
    scanf("%lf", &t_medida);
    printf("Ingrese tiempo total de simulacion: ");
    scanf("%lf", &tiempo_total);
    printf("Ingrese paso de tiempo (dt): ");
    scanf("%lf", &dt);

    // Calculo de k usando la formula
    k = (1.0 / t_medida) * log(Mt / M0);
    printf("\nConstante k calculada: %lf\n", k);

    // Abrir archivo para guardar datos
    archivo = fopen("descomposicion.csv", "w");
    fprintf(archivo, "Tiempo,Masa\n");

    // Simulacion con Euler
    M = M0;
    for (double tiempo = 0; tiempo <= tiempo_total; tiempo += dt) {
        fprintf(archivo, "%.2lf,%.6lf\n", tiempo, M);
        printf("Tiempo: %.2lf\tMasa: %.6lf\n", tiempo, M);
        M = M - k * M * dt; // Euler
    }

    fclose(archivo);
    printf("\nDatos guardados en descomposicion.csv\n");
    return 0;
}