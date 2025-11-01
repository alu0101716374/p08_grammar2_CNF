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
#include "tools.h"

#include <fstream>
#include <set>

// PARA ACTIVAR/DESACTIVAR MODO INTERACTIVO (ver la traza paso por paso)
const bool INTERACTIVE{false};


/**
 * @brief Constructor a partir de fichero de entrada
 * 
 * @param input_file_name nombre del fichero de entrada 
 * @return void, es el constructor
 */
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

/**
 * @brief Sobrecarga de salida, (mismo formato que se usa para lectura)
 *
 * @param out_stream output creada
 * @param gramatica gramatica a imprimir
 * @return out_stream, la salida
 */
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

/**
 * @brief Comprueba que no existen producciones vacías o unitarias, imprime error en caso de no estar simplificada
 *
 * @return verdadero -> simplificada - falso -> no simplifcada
 */
bool Gramatica::IsSimplified() const {
  Simbolo arranque{no_terminales_[0]};
  // Iterar por todas las producciones
  for (auto [no_terminal, produccion] : producciones_) {
     
    
    // comprobar si hay produccion a la cadena vacía (solo en caso de que no sea el simboo de arranque)
    if (produccion == "&" && no_terminal != arranque) {
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

/**
 * @brief Aplica los dos partes del algoritmo de conversion a FNC, con modo INTERACTIVE puesto, vemos la traza paso por paso en la terminal
 * 
 *
 * @return void / modifica la gramática
 */
void Gramatica::ConvertToChomsky() {
  // Parte 1 del algoritmo de FNC
  int counter{1};
  if (INTERACTIVE) {
    std::cout << "--------------------------\nPART 1 OF ALGORITHM\n";
  }
  for (auto iterator{producciones_.begin()}; iterator != producciones_.end(); iterator++) {
    std::string& production{iterator->second};
    Simbolo no_terminal{iterator->first};
    if (INTERACTIVE) {
      ClickAny();
      std::cout << "ITERATION: " << counter << "\n"; 
      std::cout << "Start: " << no_terminal << " " << production << "\n";
    }
    if (production.size() >= 2) {
      // COmprbar que no hay no termianles
      for (int i{0}; i < static_cast<int>(production.size()); i++) {
        if (alfabeto_.Contains(production[i])) {
          std::string initial_production{production}; // (para modo interactive)
          // Es un carácter no terminal. cambiarlo
          std::string temp_production{production[i]};
          Simbolo replacement = FindProduction(temp_production);
          if (replacement == ' ')  {
            replacement = NewNonTerminal(temp_production);
          }
          production[i] = replacement;
          if (INTERACTIVE) {
            std::cout << "\t - From " << initial_production << " to " << production << "\n";
          }
        }
      }
    }
    if (INTERACTIVE) {
      std::cout << "Finish: " << no_terminal << " " << production << "\n";
    }
    counter++;
  }

  // Parte 2 del algorimo
  if (INTERACTIVE) {
    std::cout << "--------------------------\nPART 2 OF ALGORITHM\n";
  }
  for (auto iterator{producciones_.begin()}; iterator != producciones_.end(); iterator++) {
    std::string& production{iterator->second};
    Simbolo no_terminal{iterator->first};
    if (INTERACTIVE) {
      ClickAny();
      std::cout << "ITERATION: " << counter << "\n"; 
      std::cout << "Start: " << no_terminal << " " << production << "\n";
    }
    int production_length{static_cast<int>(production.size())};
    if (production_length >= 3) {
      while (production_length > 2) {
        std::string initial_production{production}; // (para modo INTERACTIVE)
        // pillar los ultimos 2 simbolos
        std::string old_section = production.substr(production_length - 2);
        Simbolo replacement = FindProduction(old_section);
        if (replacement == ' ') {
          replacement = NewNonTerminal(old_section);
        }
        // borrar ultimos 2 simbolos
        production.erase(production_length - 2); 
        // añadir el nuevo simbolo
        production += replacement;

        production_length--;
        if (INTERACTIVE) {
            std::cout << "\t - From " << initial_production << " to " << production << "\n";
          }
      }
    }
    if (INTERACTIVE) {
      std::cout << "Finish: " << no_terminal << " " << production << "\n";
    }
    counter++;
  }
}

/**
 * @brief comprueba si existe una produccion (nueva, creada durante el algoritmo)
 *
 * @param input_production produccion a buscar
 * @return ' ' en caso de no existir la produccion -  el simbolo NT si existe
 */
Simbolo Gramatica::FindProduction(const std::string& input_production) {
  // Iterar por producciones
  for (auto [no_terminal, production] : producciones_) {
    if (production == input_production) {
      // comprobar si la produccion es nueva
      for (Simbolo temp : new_no_terminales_) {
                if (temp == no_terminal) return no_terminal; 
            }
    }
  }
  return ' ';
}

/**
 * @brief Crea un simbolo NT nuevo, empezando en A, hasta Z (usa el primero que no existe ya)
 *
 * @param input_production produccion a crear
 * @return Return description
 */
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
    if (INTERACTIVE) {
      std::cout << "# Non terminal Added: " << new_terminal << " " << input_production << "\n";
    }
    // Actualiza la gramática
    new_no_terminales_.push_back(new_terminal);
    no_terminales_.push_back(new_terminal);
    producciones_.insert({new_terminal, input_production});
    non_terminal_amount_++;
    producciones_size_++;

    return new_terminal;
}

