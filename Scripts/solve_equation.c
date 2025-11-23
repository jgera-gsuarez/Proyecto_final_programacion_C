//José Gerardo González Suárez y Alizon Pamela Lagos Tlahuice.

#include <stdio.h>
#include <math.h>

int main() {
    int i;
    double M0, Mf, t_final;
    double k_calido[6], k_frio[6];
    double promedio_calido = 0.0, promedio_frio = 0.0, promedio_global;
    double tiempo_total, dt;
    double M;
    FILE *archivo;

    // Calculo de k para ambiente cálido
    printf("=== Ambiente cálido ===\n");
    for (i = 0; i < 6; i++) {
        printf("\nVaso %d:\n", i + 1);
        printf("Ingrese masa inicial (M0): ");
        scanf("%lf", &M0);
        do{
            printf("Ingrese masa final (Mf): ");
            scanf("%lf", &Mf);
            if (Mf <= 0){
                printf("Error: la masa final debe ser mayor que 0.\n");
            }
        } while(Mf <= 0);
        printf("Ingrese tiempo total (t): ");
        scanf("%lf", &t_final);

        // Formula analítica para k
        k_calido[i] = (1.0 / t_final) * log(Mf / M0);
        promedio_calido += k_calido[i];
        printf("k calculada: %lf\n", k_calido[i]);
    }
    promedio_calido /= 6.0;

    // Calculo de k para ambiente frío
    printf("\n=== Ambiente frío ===\n");
    for (i = 0; i < 6; i++) {
        printf("\nVaso %d:\n", i + 1);
        printf("Ingrese masa inicial (M0): ");
        scanf("%lf", &M0);
        do{
            printf("Ingrese masa final (Mf): ");
            scanf("%lf", &Mf);
            if (Mf <= 0){
                printf("Error: la masa final debe ser mayor que 0.\n");
            }
        } while(Mf <= 0);
        printf("Ingrese tiempo total (t): ");
        scanf("%lf", &t_final);
        printf("Ingrese tiempo total (t): ");
        scanf("%lf", &t_final);

        k_frio[i] = (1.0 / t_final) * log(Mf / M0);
        promedio_frio += k_frio[i];
        printf("k calculada: %lf\n", k_frio[i]);
    }
    promedio_frio /= 6.0;

    // Calculo del promedio global
    promedio_global = (promedio_calido + promedio_frio) / 2.0;

    printf("\nPromedio k cálido: %lf\n", promedio_calido);
    printf("Promedio k frío: %lf\n", promedio_frio);

    // Simulación con Euler usando promedio cálido y frío
    printf("\nIngrese tiempo total de simulacion: ");
    scanf("%lf", &tiempo_total);
    printf("Ingrese paso de tiempo (dt): ");
    scanf("%lf", &dt);
    printf("Ingrese masa inicial para simulacion: ");
    scanf("%lf", &M0);

    archivo = fopen("simulacion.csv", "w");
    fprintf(archivo, "Tiempo,Masa_Calido,Masa_Frio\n");

    double M_calido = M0;
    double M_frio = M0;

    for (double tiempo = 0; tiempo <= tiempo_total; tiempo += dt) {
        fprintf(archivo, "%.2lf,%.6lf,%.6lf\n", tiempo, M_calido, M_frio);
        printf("Tiempo: %.2lf\tCalido: %.6lf\tFrio: %.6lf\n", tiempo, M_calido, M_frio);

        // Método de Euler
        M_calido = M_calido + promedio_calido * M_calido * dt;
        M_frio = M_frio + promedio_frio * M_frio * dt;
    }

    fclose(archivo);
    printf("\nDatos guardados en simulacion.csv\n");
    return 0;
}
