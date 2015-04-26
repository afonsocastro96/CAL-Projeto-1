//
// Created by afonso on 21-04-2015.
//
#pragma once

using namespace std;

/**
 * @brief Verifica se uma estacao de metro existe no vetor de estacoes de metro
 *
 * @param locals vetor com os locais
 * @param local local a procurar
 *
 * @return true caso o local exista, false caso nao exista
 */
bool estacaoExiste(vector<Local *> locals, Local *local);

/**
 * @brief Extrai do ficheiro as estacoes de metro, faz parse das mesmas, colocando-as num vetor.
 *
 * @return O vetor com as estacoes de metro.
 */
vector<Local *> extrairEstacoesMetro();

/**
 * @brief Insere as estacoes de metro, ja tratadas, no grafo de locais.
 *
 * @param g O grafo a inserir as estacoes.
 * @param locais O vetor a inserir no grafo.
 */
void inserirEstacoesNoGrafo(Graph<Local *> &g, vector<Local *> locais);
