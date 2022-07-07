#ifndef Utils_HPP
#define Utils_HPP

#include <vector>
#include <string>

/**
 * @brief Retorna um vetor de strings contendo as partes da string maior
 * 
 * @param str String a ser dividida
 * @param separator Caractere separador da string maior em string menores
 * @return Um vetor de strings Com as strings menores
 */
std::vector<std::string> split(std::string str, char separator);

#endif