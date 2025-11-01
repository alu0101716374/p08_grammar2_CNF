// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Kye Brandon Rogers
// Correo: alu0101716374@ull.edu.es
// Fecha: 20/09/2025-
// Archivo alfabeto.cc
// crea las funciones/metodos declaradas en el fichero alfabeto.h
//
// Historial de revisiones
// 20/09/2025 - Creación (primera versión) del código

#include "alfabeto.h"

#include "simbolo.h"
#include "tools.h"
#include <iostream>

/**
 * @brief inserts a symbol into the alphabet set
 *
 * @param simbolo the symbol you want to insert
 * @return void
 */
void Alfabeto::Insert(const Simbolo& simbolo) {
  // alphabets cannot contain the empty string &
  if (simbolo == '&') ErrorFour();
  alfabeto_.insert(simbolo);
}

/**
 * @brief Checks whether the alphabet contains a certain symbol
 *
 * @param simbolo The symbol to be searched for in the alphabet
 * @return True or False depending on if it is found
 */
bool Alfabeto::Contains(const Simbolo& simbolo) const {
  return (alfabeto_.find(simbolo) != alfabeto_.end());
}

std::set<Simbolo> Alfabeto::GetAlfabeto() {
  return alfabeto_;
}

/**
 * @brief default constructor, makes an empty alphabet
 *
 * @return void
 */
Alfabeto::Alfabeto() {};

/**
 * @brief output stream operator overload, prints the alphabet in the format {<symbol1>, <symbol2>, ...}
 *
 * @param os outstream that will be returned
 * @param alfabeto alphabet to be printed
 * @return out stream 
 */
std::ostream& operator<<(std::ostream& os, const Alfabeto& alfabeto) {
  for (Simbolo simbolo : alfabeto.alfabeto_) {
      os << simbolo << "\n";
  }
  return os;
}

