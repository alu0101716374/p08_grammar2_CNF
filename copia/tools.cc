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

/**
 * @brief Imprime el modo de empleo
 *
 * @return void
 */
void PrintUsage() {
  std::cout << "Modo de empleo: ./Grammar2CNF input.gra output.gra\n" 
  <<  "Pruebe 'Grammar2CNF --help' para mas informacion.\n";
}

/**
 * @brief Exlica todo lo importante sobre el uso del programa
 *
 * @return void
 */
void Help() {
  PrintUsage();
  std::cout << "# Si no se especifica fichero de salida, el programa \n  Usará out.gra por defecto\n";
  std::cout << "####################\nFormato de fichero de entrada\n";
  std::cout << "\t - Primera linea = n (nº de simbolos en alfabeto)\n";
  std::cout << "\t - n lineas siguientes = simbolo del alfabeto\n";
  std::cout << "\t - linea siguiente = m (nº de no terminales)\n";
  std::cout << "\t - m lineas siguientes = no terminal -> PRIMERA POSICION = ARRANQUE\n";
  std::cout << "\t - linea siguiente = v (nº de producciones)\n";
  std::cout << "\t - v lineas siguientes = <no terminal> <produccion>\n";
  std::cout << "\n\nLa gramatica debe estar simplificada\n";
  std::cout << "# Existe modo interactivo para ver la traza\n";
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

/**
 * @brief Imprime un mensaje de error pr producciones vacías o unitarias
 *
 * @return void
 */
void NotSimplified() {
  std::cout << "#####################################\n";
  std::cout << "No se puede pasar a FNC, elimina producciones VACIAS y UNITARIAS\n";
}

/**
 * @brief Para el modo INTERACTIVO, el usuario tendrá que pulsar Enter para seguir
 *
 * @return void
 */
void ClickAny() {
  std::cout << "\n######################################\nClick ENTER to continue: \n";
  std::cin.get();
}