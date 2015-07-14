# Compilador que será utilizado
CC=g++

# flags de compilación
CFLAGS=-g -Wall -std=c++11 -pg

# flags de linkeo
LDFLAGS=-pg

# Agrear acá los directorios a incluir en la compilación
INCDIR=../../tp3

# Agregar acá los archivos .cpp a compilar
SOURCES=test.cpp Driver.cpp ArbolSintactico.cpp ../DCNET/dcnet.cpp ../Red/Red.cpp

# Objetos que serán generados (no tocar)
OBJECTS=$(SOURCES:.cpp=.o)

# Nombre del ejecutable a generar
EXECUTABLE=test

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)

.cpp.o:
	$(CC) -I$(INCDIR) $(CFLAGS) $< -c -o $@
