
import os
import csv

def validate_csv(path, expected_lines=12):
    if not os.path.exists(path):
        return "[ERROR] No se generó el archivo CSV."
    size = os.path.getsize(path)
    with open(path, newline='') as f:
        rows = list(csv.reader(f))
    reporte = [f"[OK] CSV encontrado ({size} bytes)."]
    reporte.append(f"Filas: {len(rows)} (esperadas: {expected_lines})")
    reporte.extend([str(line) for line in rows[:5]])
    return "\n".join(reporte)

def validate_image(path):
    if not os.path.exists(path):
        return "[ERROR] No se generó la imagen."
    size = os.path.getsize(path)
    return f"[OK] Imagen encontrada ({size} bytes)." if size > 0 else "[ERROR] Imagen vacía."
