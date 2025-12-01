import os

# Calcula la ruta base relativa al archivo actual
base_dir = os.path.dirname(os.path.abspath(__file__))

binary_path = os.path.join(base_dir, "..", "app")
result_dir = os.path.join(base_dir, "..", "Resultados")
csv_file = os.path.join(result_dir, "simulacion.csv")
img_file = os.path.join(result_dir, "grafica.png")


MASA_INICIAL_RANGE = (1, 20)
MASA_FINAL_RANGE = (0.0001, 20)
TIEMPO_RANGE = (0.00001, 100)

SIM_TIEMPO_TOTAL = 100
SIM_DT = 0.03
SIM_MASA_INICIAL = 10

