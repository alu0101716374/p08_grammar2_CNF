// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: grammar2_FNC
// Autor: Kye Brandon Rogers
// Correo: alu0101716374@ull.edu.es
// Fecha: 29/10/2025-
// Archivo gramatica.cc
// crea los metodos de la clase Gramatica declaradas en gramatica.h
//
// Historial de revisiones
// 29/10/2025 - Creación (primera versión) del código

#include "gramatica.h"
#include <fstream>

Gramatica::Gramatica(const std::string& input_file_name) {
  std::ifstream input_file;
  input_file.open(input_file_name);

  // Primer linea es tamaño del alfabeto
  input_file >> alfabeto_size_;

  // crear alfabeto
  Simbolo temp_simbolo;
  for (int i{0}; i < alfabeto_size_; i++) {
    input_file >> temp_simbolo;
    alfabeto_.Insert(temp_simbolo);
  }

  // En esta linea se encuentra el numero de Simbolos no terminales
  input_file >> non_terminal_amount_;

  // Guardar no terminales
  for (int i{0}; i < non_terminal_amount_; i++) {
    input_file >> temp_simbolo;
    no_terminales_.push_back(temp_simbolo);
  }

  // Numero de producciones
  input_file >> producciones_size_;

  // Guardar Producciones
  std::string produccion{""};
  for (int i{0}; i < producciones_size_; i++) {
    input_file >> temp_simbolo >> produccion;
    producciones_.insert({temp_simbolo, produccion});
  }
}

std::ostream& operator<<(std::ostream& out_stream, const Gramatica& gramatica) {
  out_stream << gramatica.alfabeto_size_  << "\n" << gramatica.alfabeto_ << gramatica.non_terminal_amount_ << "\n";
  // Imprimir no terminales
  for (Simbolo no_terminal : gramatica.no_terminales_) {
    out_stream << no_terminal << "\n";
  } 
  // Imprimir cantidad de producciones
  out_stream << gramatica.producciones_size_ << "\n";
  // Imprimir producciones
  for (auto [no_terminal, produccion] : gramatica.producciones_) {
    out_stream << no_terminal << " " << produccion << "\n";
  } 
  return out_stream;

}