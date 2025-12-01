import random
from configuration import MASA_INICIAL_RANGE, MASA_FINAL_RANGE, TIEMPO_RANGE

def generate_data(n=6):
    data_warm = [
        (1, 0.005, 6),
        (2, 0.005, 10),
        (3, 0.005, 13),
        (4, 0.005, 15),
        (5, 0.005, 19),
        (6, 0.005, 20)
	]
    data_cold = [
		(1, 0.005, 10),
        (2, 0.005, 16),
        (3, 0.005, 20),
        (4, 0.005, 25),
        (5, 0.005, 28),
        (6, 0.005, 30)
	]
    return data_warm, data_cold