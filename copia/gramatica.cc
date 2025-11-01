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
#include <set>

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
  out_stream << gramatica.alfabeto_size_ << "\n"
             << gramatica.alfabeto_ << gramatica.non_terminal_amount_ << "\n";
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

// TODO:: make sure start production ca accept empty string production
bool Gramatica::IsSimplified() const {
  // Iterar por todas las producciones
  for (auto [no_terminal, produccion] : producciones_) {
    // comprobar si hay produccion a la cadena vacía
    if (produccion == "&") {
      std::cout << "#####################################\n";
      std::cout << "Produccion vacia encontrada: " << no_terminal << " "
                << produccion << "\n\n";
      return false;
    }
    // comprobar si es Unitaria
    if (produccion.size() == 1) {
      for (Simbolo no_terminal_temp : no_terminales_) {
        if (produccion[0] == no_terminal_temp) {  // pongo produccion[0] para no
                                                  // pasarlo a simbolo/char
          std::cout << "#####################################\n";
          std::cout << "Produccion Unitaria encontrada: " << no_terminal << " "
                    << produccion << "\n\n";
          return false;
        }
      }
    }
  }
  return true;
}

void Gramatica::ConvertToChomsky() {
  // Parte 1 del algoritmo de FNC
  for (auto iterator{producciones_.begin()}; iterator != producciones_.end(); iterator++) {
    Simbolo no_terminal{iterator->first};
    std::string& production{iterator->second};
    if (production.size() >= 2) {
      // COmprbar que no hay no termianles
      for (int i{0}; i < production.size(); i++) {
        if (alfabeto_.Contains(production[i])) {
          // Es un carácter no terminal. cambiarlo
          std::string temp_production{production[i]};
          Simbolo replacement = FindProduction(temp_production, new_no_terminales_);
          if (replacement == ' ')  {
            replacement = NewNonTerminal(temp_production);
          }
          production[i] = replacement;
        }
      }
    }

  }
}


Simbolo Gramatica::FindProduction(const std::string& input_production, std::vector<Simbolo> list) {
  for (auto [no_terminal, production] : producciones_) {
    if (production == input_production) {
      for (Simbolo temp : list) {
                if (temp == no_terminal) return no_terminal; 
            }
    }
  }
  return ' ';
}

Simbolo Gramatica::NewNonTerminal(const std::string& input_production) {
   Simbolo new_terminal{'A'};
    bool exists = true; 
    while (exists) {
        exists = false;
        for (Simbolo existing : new_no_terminales_) {
            if (existing == new_terminal) {
                exists = true;
                break; 
            }
        }
        if (exists) ++new_terminal;
    }

    new_no_terminales_.push_back(new_terminal);
    no_terminales_.push_back(new_terminal);
    producciones_.insert({new_terminal, input_production});
    std::cout << new_terminal << " añadido a new_no_terminals\n";
    std::cout << "NNT añadiendo produccion " << new_terminal << " " << input_production << "\n";
    non_terminal_amount_++;
    producciones_size_++;

    return new_terminal;
}


std::string Gramatica::UpdateProduction(const std::string& production,
                                         const Simbolo& symbol,
                                         const Simbolo& replacement) {
  std::string new_production{""};
  for (Simbolo simbolo : production) {
    if (simbolo == symbol) {
      new_production += replacement;
    } else {
      new_production += simbolo;
    }
  }
  return new_production;
}