#pragma once

#include <vector>
#include <string>

#include "Graph.h"

/**
 * @brief Funcao que chama todas as funcoes que tratam da extracao e tratamento da informacao referente aos autocarros.
 * Extrai dos ficheiros todas as linhas de autocarro, e coloca-as num vetor de Locais para serem posteriormente tratadas.
 * @param nomeLinhas vetor com o nome das linhas a extrair
 * @return vetor de locais com informacao acerca de todas as locais de todas as linhas, ainda repetidas.
 */
vector<vector<Local *> > obterLinhasAutocarro(vector<string> nomeLinhas);

/**
 * @brief Extrai dos ficheiros todas as linhas de autocarro, para um vetor de vetores de strings, ainda com a informacao "raw".
 * Cada vetor contem informacao acerca de cada linha .
 * @param linhas vetor com o nome de linhas a extrair
 * @return vetor de vetores de strings, cada vetor contendo informacao "raw" sobre cada local.
 */
vector<vector<string> > extrairLinhasAutocarro(vector<string> linhas);

/**
 * @brief Extrai todas as locais de uma linha em "raw mode". Utilizada como funcao auxiliar de obterLinhasAutocarro()
 * @param fichLinhaAtual nome do ficheiro que contem a linha.
 * @return Um vetor de locais em "raw" mode.
 */
vector<string> extraiLinha(string fichLinhaAtual);

/**
 * @brief Pega no vetor com todas as linhas e retorna um vetor de Locais, em formato utilizavel pela aplicacao.
 * @param linhas vetor com todas as linhas da rede de autocarros, em formato "raw".
 * @return Vetor de locais.
 */
vector<vector<Local *> > parseLocais(vector<vector<string> > linhas);

/**
 * @brief Converte as locais de formato "raw" para formato tratavel pela aplicacao. Funcao auxiliar de parseLocais()
 * @param local Local a converter.
 * @return Instancia da classe Local com a informacao em forma utilizavel pela aplicacao.
 */
Local* parseLocal(string local);

/**
 * Insere no grafo os locais ja extraidos e tratados.
 * @param g Grafo a adicionar os locais
 * @param locais vetor de vetores (linhas) de paragens
 */
void inserirParagensNoGrafo(Graph<Local *> &g, vector<vector<Local *> > locais);

/**
 * @brief Verifica se uma paragem ja existe no grafo.
 * @param g O grafo.
 * @param p A local.
 * @return indice da local caso encontre, -1 em caso contrario
 */
int paragemExiste(Graph<Local *> &g, Local *p);
