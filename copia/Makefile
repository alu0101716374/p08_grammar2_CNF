# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Asignatura: Computabilidad y Algoritmia
# Curso: 2º
# Práctica 2: Cadenas y lenguajes
# Autor: Kye Brandon Rogers
# Correo: alu0101716374@ull.edu.es
# Fecha: 29/10/2025
# Archivo Makefile
#
# Historial de revisiones
# 29/10/2025 - Creación (primera versión) del código

ejecutable := grammar2_FNC

all:
	@echo "Programa compilado"
	g++ -Wall main.cc tools.cc alfabeto.cc gramatica.cc -o $(ejecutable)

clean: $(ejecutable)
	@echo "Ejecutable borrado del directorio"
	rm -f $(ejecutable)
	rm -rf *.txt *.gra