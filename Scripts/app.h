// --Header File--
#ifndef APP_H // Si no está definido APP_H
#define APP_H // Define APP_H

void calcular(); //Declaramos la función que va a calcular los valores de k
void simular();  //Declaramos la función que llevará la simulación con los valores obtenidos de k
void graficar_csv(const char *input_csv, const char *output_png); //Declaramos la función que graficará
                                                                  //los datos de la simulación

#endif //Cierra la condición que define APP_H
