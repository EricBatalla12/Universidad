# Opciones del compilador
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -I./include
DEBUG_FLAGS = -g

# Directorios
SRC_DIR = src
LIB_DIR = lib

# Archivos fuente compartidos (las clases)
LIB_SOURCES = $(LIB_DIR)/tabbcom.cpp $(LIB_DIR)/tcomplejo.cpp $(LIB_DIR)/tvectorcom.cpp
# Los .o correspondientes
LIB_OBJECTS = $(LIB_SOURCES:.cpp=.o)

# Archivo principal (usamos tad.cpp para que el evalua.sh funcione perfecto)
MAIN_SOURCE = $(SRC_DIR)/tad.cpp
MAIN_OBJECT = $(MAIN_SOURCE:.cpp=.o)

# Nombres de los ejecutables
EXEC = tad
EXEC_DEBUG = tad.debug

# --- TARGETS ---

# Target por defecto: construye ambos ejecutables
all: $(EXEC) $(EXEC_DEBUG)

# 1. Regla para el ejecutable normal (compila rápido usando los .o)
$(EXEC): $(LIB_OBJECTS) $(MAIN_OBJECT)
	$(CXX) $(CXXFLAGS) -o $@ $^

# 2. Regla para el ejecutable de debug (compila todo de cero con la bandera -g)
$(EXEC_DEBUG): $(LIB_SOURCES) $(MAIN_SOURCE)
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) -o $@ $^

# Regla genérica para compilar los .cpp en .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para limpiar la basura generada
clean:
	rm -f $(LIB_DIR)/*.o $(SRC_DIR)/*.o $(EXEC) $(EXEC_DEBUG)

# Phony targets para evitar conflictos con archivos reales que se llamen así
.PHONY: all clean