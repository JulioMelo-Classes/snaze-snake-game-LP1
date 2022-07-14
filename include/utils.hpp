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


/**
 * @brief Verifica se um determinado valor está em um vetor
 * 
 * @tparam value valor a ser verificado no vetor
 * @tparam v vetor em que o dado será buscado
 * @return true se o valor existe no vetor, false caso contrário
 */
template <typename type>
bool isIn(type value, std::vector<type> v){
    for(size_t i=0; i < v.size(); i++)
        if(v[i] == value) return true;

    return false;
}

#endif