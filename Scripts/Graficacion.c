#include <cairo/cairo.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define WIDTH 800
#define HEIGHT 600
#define MARGIN 50

void graficar_csv(const char *input_csv, const char *output_png) {
    FILE *archivo = fopen(input_csv, "r");
    if (!archivo) {
        fprintf(stderr, "Error al abrir %s: %s\n", input_csv, strerror(errno));
        return;
    }

    char linea[256];
    int capacidad = 1000;
    double *tiempo = malloc(capacidad * sizeof(double));
    double *masa_calido = malloc(capacidad * sizeof(double));
    double *masa_frio = malloc(capacidad * sizeof(double));
    if (!tiempo || !masa_calido || !masa_frio) {
        fprintf(stderr, "Error de memoria\n");
        fclose(archivo);
        return;
    }

    int n = 0;
    fgets(linea, sizeof(linea), archivo); // Saltar encabezado
    while (fgets(linea, sizeof(linea), archivo)) {
        if (n >= capacidad) {
            capacidad *= 2;
            tiempo = realloc(tiempo, capacidad * sizeof(double));
            masa_calido = realloc(masa_calido, capacidad * sizeof(double));
            masa_frio = realloc(masa_frio, capacidad * sizeof(double));
        }
        sscanf(linea, "%lf,%lf,%lf", &tiempo[n], &masa_calido[n], &masa_frio[n]);
        n++;
    }
    fclose(archivo);

    // Calcular máximos
    double max_t = tiempo[n - 1];
    double max_m = masa_calido[0];
    for (int i = 0; i < n; i++) {
        if (masa_calido[i] > max_m) max_m = masa_calido[i];
        if (masa_frio[i] > max_m) max_m = masa_frio[i];
    }
    max_m *= 1.1; // margen extra

    double scale_x = (WIDTH - 2 * MARGIN) / max_t;
    double scale_y = (HEIGHT - 2 * MARGIN) / max_m;

    cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, WIDTH, HEIGHT);
    cairo_t *cr = cairo_create(surface);

    if (cairo_surface_status(surface) != CAIRO_STATUS_SUCCESS) {
        fprintf(stderr, "Error creando superficie Cairo\n");
        free(tiempo); free(masa_calido); free(masa_frio);
        return;
    }

    // Fondo blanco
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);

    // Ejes
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 2);
    cairo_move_to(cr, MARGIN, HEIGHT - MARGIN);
    cairo_line_to(cr, WIDTH - MARGIN, HEIGHT - MARGIN);
    cairo_move_to(cr, MARGIN, HEIGHT - MARGIN);
    cairo_line_to(cr, MARGIN, MARGIN);
    cairo_stroke(cr);

    // Etiquetas
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 14);
    cairo_move_to(cr, WIDTH / 2, HEIGHT - 10);
    cairo_show_text(cr, "Tiempo");
    cairo_move_to(cr, 10, HEIGHT / 2);
    cairo_show_text(cr, "Masa");

    // Ticks en X
    int ticks = 10;
    for (int i = 0; i <= ticks; i++) {
        double t = max_t * i / ticks;
        double x = MARGIN + t * scale_x;
        cairo_move_to(cr, x, HEIGHT - MARGIN);
        cairo_line_to(cr, x, HEIGHT - MARGIN + 5);
        cairo_stroke(cr);
        char etiqueta[32];
        snprintf(etiqueta, sizeof(etiqueta), "%.1f", t);
        cairo_move_to(cr, x - 10, HEIGHT - MARGIN + 20);
        cairo_show_text(cr, etiqueta);
    }

    // Ticks en Y
    for (int i = 0; i <= ticks; i++) {
        double m = max_m * i / ticks;
        double y = HEIGHT - MARGIN - m * scale_y;
        cairo_move_to(cr, MARGIN, y);
        cairo_line_to(cr, MARGIN - 5, y);
        cairo_stroke(cr);
        char etiqueta[32];
        snprintf(etiqueta, sizeof(etiqueta), "%.1f", m);
        cairo_move_to(cr, 10, y + 5);
        cairo_show_text(cr, etiqueta);
    }

    // Curva cálido (rojo)
    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_set_line_width(cr, 2);
    cairo_move_to(cr, MARGIN, HEIGHT - MARGIN - masa_calido[0] * scale_y);
    for (int i = 1; i < n; i++) {
        cairo_line_to(cr, MARGIN + tiempo[i] * scale_x, HEIGHT - MARGIN - masa_calido[i] * scale_y);
    }
    cairo_stroke(cr);

    // Curva frío (azul)
    cairo_set_source_rgb(cr, 0, 0, 1);
    cairo_move_to(cr, MARGIN, HEIGHT - MARGIN - masa_frio[0] * scale_y);
    for (int i = 1; i < n; i++) {
        cairo_line_to(cr, MARGIN + tiempo[i] * scale_x, HEIGHT - MARGIN - masa_frio[i] * scale_y);
    }
    cairo_stroke(cr);

    // Leyenda
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_move_to(cr, WIDTH - 150, MARGIN);
    cairo_show_text(cr, "Cálido (rojo)");
    cairo_move_to(cr, WIDTH - 150, MARGIN + 20);
    cairo_show_text(cr, "Frío (azul)");

    cairo_surface_write_to_png(surface, output_png);
    cairo_destroy(cr);
    cairo_surface_destroy(surface);

    free(tiempo);
    free(masa_calido);
    free(masa_frio);

    printf("Gráfica exportada como %s\n", output_png);
}

void ejecutar_graficacion() {
    graficar_csv("Resultados/simulacion.csv", "Resultados/grafica.png");
    return;
}
