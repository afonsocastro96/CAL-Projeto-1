#ifndef INIT_H
#define INIT_H


#include <QApplication>
#include <cstdio>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "graphviewer.h"
#include "mainwindow.h"
#include "preprocessing.h"

#include "Graph.h"
#include "Local.h"
#include "parseLinhasMetro.h"
#include "parseLinhasAutocarro.h"

#include "symbolics.h"

void loadNodes(Graph<Local*> &g);
void loadEdges(Graph<Local*> &g);
void loadFiles(Graph<Local*> &g);
void createFiles();
string exec(Graph<Local*> &g);
void init(Graph<Local*> &g);
void showFullMap();

extern Graph<Local*> g;
extern int resX;
extern int resY;
extern Preference preference;
extern int algorithm;
extern int idPartida;
extern int idChegada;

#endif // INIT_H

