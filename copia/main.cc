// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: grammar2_FNC
// Autor: Kye Brandon Rogers
// Correo: alu0101716374@ull.edu.es
// Fecha: 29/10/2025-
// Archivo main.cc
// Es el fichero main que simula la práctica 8
//
// Historial de revisiones
// 29/10/2025 - Creación (primera versión) del código

#include "tools.h"
#include "gramatica.h"

#include <fstream>
#include <string>

int main(int argc, char* argv []) {
  if (argc == 1) {
    PrintUsage();
  } else if (std::string(argv[1]) == "--help") {
    Help();
  } else if (argc == 3) {
    const std::string input_file_name{argv[1]}, output_file_name{argv[2]};
    Gramatica grammar{input_file_name};
    std::ofstream out_file;
    out_file.open(output_file_name);
    out_file << grammar;
  }
}