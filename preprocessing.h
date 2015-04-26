//
// Created by afonso on 25-04-2015.
//

#ifndef PROJETOITINERARIOSMULTIMODAIS_PREPROCESSING_H
#define PROJETOITINERARIOSMULTIMODAIS_PREPROCESSING_H

#include "Graph.h"
#include "Local.h"

void saveNodes(Graph<Local*> &graph);
void saveEdges(Graph<Local*> &graph);
void calculateWalkableEdges(Graph<Local*> &graph);

#endif //PROJETOITINERARIOSMULTIMODAIS_PREPROCESSING_H
