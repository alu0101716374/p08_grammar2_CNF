// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: grammar2_FNC
// Autor: Kye Brandon Rogers
// Correo: alu0101716374@ull.edu.es
// Fecha: 29/10/2025-
// Archivo gramatica.h
// declara clase Gramatica, lo cual perimte almacenar una gramática y convertirlo a su FNC
//
// Historial de revisiones
// 29/10/2025 - Creación (primera versión) del código

#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "simbolo.h"
#include "alfabeto.h"

#include <map>
#include <vector>

class Gramatica {
  public:
    // constructor a partir de fichero
    Gramatica(const std::string& input_file_name);

    // comporbacion de si esta simplificada
    bool IsSimplified() const;

    void ConvertToChomsky();

    // sobrecargas utiles
    friend std::ostream& operator<<(std::ostream& out_stream, const Gramatica& gramatica); 

  private:
    int alfabeto_size_{0};
    Alfabeto alfabeto_;
    int non_terminal_amount_{0};
    std::vector<Simbolo> no_terminales_;
    std::multimap<Simbolo, std::string> producciones_;
    int producciones_size_{0};
    std::vector<Simbolo> new_no_terminales_;

    Simbolo FindProduction(const std::string& input_production);
    Simbolo NewNonTerminal(const std::string& input_production);

};

#endif