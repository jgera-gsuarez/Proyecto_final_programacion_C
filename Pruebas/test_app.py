import os
import subprocess
from configuration import binary_path, csv_file, img_file, SIM_TIEMPO_TOTAL, SIM_DT, SIM_MASA_INICIAL
from data import generate_data
from valid import validate_csv, validate_image

# Generar datos para ambos ambientes
vasos_calido, vasos_frio = generate_data()

# Construir entrada completa para el menú
inputs = "1\n"
for vaso in vasos_calido + vasos_frio:
    inputs += f"{vaso[0]}\n{vaso[1]}\n{vaso[2]}\n"
inputs += f"{SIM_TIEMPO_TOTAL}\n{SIM_DT}\n{SIM_MASA_INICIAL}\n"
inputs += "2\n3\n"  # Graficar y salir

print("[INFO] Ejecutando flujo completo...")
try:
    # Cambiar directorio de trabajo a la raíz del proyecto
    project_root = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
    proc = subprocess.run(
        [binary_path],
        input=inputs,
        text=True,
        capture_output=True,
        timeout=60,
        cwd=project_root  # <-- Aquí está la clave
    )
    print("[OK] Programa ejecutado correctamente.")
    print(f"Salida:\n{proc.stdout}")
except subprocess.TimeoutExpired:
    print("[ERROR] El programa excedió el tiempo límite (60s).")
except FileNotFoundError:
    print("[ERROR] Binario no encontrado. Asegúrate de compilar solve_equation.")

# Validaciones
print("\n--- Validación CSV ---")
print(validate_csv(csv_file))

print("\n--- Validación Imagen ---")
print(validate_image(img_file))
