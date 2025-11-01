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

#include <fstream>
#include <string>

#include "gramatica.h"
#include "tools.h"

int main(int argc, char* argv[]) {
  if (argc == 1) {
    PrintUsage();
  } else if (std::string(argv[1]) == "--help") {
    Help();
  } else {
    const std::string input_file_name{argv[1]};
    // por defecto en out.gra
    std::string output_file_name{"out.gra"};
    if (argc == 3) {
      output_file_name = argv[2];
    }
    Gramatica grammar{input_file_name};
    std::ofstream out_file;
    out_file.open(output_file_name);
    // Comprobar que esta simplificada
    if (!grammar.IsSimplified()) NotSimplified();
    grammar.ConvertToChomsky();
    out_file << grammar;
  }
}