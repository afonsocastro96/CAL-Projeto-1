#ifndef INIT_H
#define INIT_H

#include "mainwindow.h"
#include <QApplication>
#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>

#include <string>
#include <iostream>
#include <fstream>

#include "Graph.h"
#include "Local.h"
#include "parseLinhasMetro.h"
#include "parseLinhasAutocarro.h"
#include "preprocessing.h"
#include "graphviewer.h"
#include "symbolics.h"

void loadNodes(Graph<Local*> &g);
void loadEdges(Graph<Local*> &g);
void loadFiles(Graph<Local*> &g);
void createFiles();
int exec(Graph<Local*> &g);
void init(Graph<Local*> &g);
void callUpdateBusScript();
void callUpdateSubwayScript();

extern Graph<Local*> g;

#endif // INIT_H

