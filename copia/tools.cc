// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: grammar2_FNC
// Autor: Kye Brandon Rogers
// Correo: alu0101716374@ull.edu.es
// Fecha: 29/10/2025-
// Archivo tools.cc
// cea las duncionas declaradas en el tools.h
//
// Historial de revisiones
// 29/10/2025 - Creación (primera versión) del código

#include "tools.h"

#include <iostream>

void PrintUsage() {
  std::cout << "Modo de empleo: ./Grammar2CNF input.gra output.gra\n" 
  <<  "Pruebe 'Grammar2CNF --help' para mas informacion.\n";
}

void Help() {
  PrintUsage();
  std::cout << "RELLENAR CON --help\n";
}


/**
 * @brief & cannot be part of alphabet error, force close program
 *
 * @return exit(1)
 */
void ErrorFour() {
  std::cerr << "Error 4: The symbol '&' cannot be in the alphabet as it is saved to represent the empty string\nPROGRAM TERMINATED\n";
  std::exit(1);
}
