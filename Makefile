
# Nombre del ejecutable
TARGET = app

# Carpetas
SRC_DIR = Scripts
BUILD_DIR = build

# Detectar automáticamente los .c
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Generar lista de .o en build/
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Compilador y flags
CC = gcc
CFLAGS = -Wall -std=c11 -I $(SRC_DIR)
LDFLAGS = -lm `pkg-config --cflags --libs cairo`

# Flags para debug y release
DEBUG_FLAGS = -g
RELEASE_FLAGS = -O2

# Regla principal (por defecto: release)
all: release

# Crear carpeta build si no existe
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compilación en modo release
release: CFLAGS += $(RELEASE_FLAGS)
release: $(TARGET)

# Compilación en modo debug
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)

# Enlazar el binario en la carpeta raíz
$(TARGET): $(BUILD_DIR) $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Cómo compilar cada .c a .o (con dependencias .d)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

# Incluir dependencias generadas
-include $(OBJS:.o=.d)

# Limpiar archivos generados
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
