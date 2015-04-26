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

using namespace std;

void loadNodes(Graph<Local*> &g){
    string idStr;
    string nome;
    string xStr;
    string yStr;
    int id;
    int x;
    int y;

    ifstream ifile("nodes.txt");

    while(!ifile.eof()){
        getline(ifile, idStr);
        id = atoi(idStr.c_str());

        getline(ifile,nome);

        getline(ifile, xStr);
        x = atoi(xStr.c_str());

        getline(ifile, yStr);
        y = atoi(yStr.c_str());

        ifile.get(); //Limpar a linha separadoera do ficheiro
        Local* l = new Local(id, x,y,nome);
        g.addVertex(l, l->getX(), l->getY());
    }

    ifile.close();
}

void loadEdges(Graph<Local*> &g){
    int partida;
    int chegada;
    double distancia;
    double preco;
    Transport tipoTransporte;
    int transport;

    ifstream ifile("edges.txt");

    while(!ifile.eof()){
        ifile >> partida;
        ifile >> chegada;
        ifile >> distancia;
        ifile >> preco;
        ifile >> transport;
        if(ifile.get() == EOF)
            break;

        if(transport == BUS)
            tipoTransporte = BUS;
        else if(transport == METRO)
            tipoTransporte = METRO;
        else if(transport == WALK)
            tipoTransporte = WALK;

        g.addEdge(g.getVertexSet().at(partida)->getInfo(),g.getVertexSet().at(chegada)->getInfo(),preco,distancia, tipoTransporte);
    }
}

void loadFiles(Graph<Local*> &g) {
    loadNodes(g);
    loadEdges(g);
}

void createFiles(){
    Graph<Local*> g;

    //Parse Info from downloaded files
    vector<vector<Local *> > p = obterLinhasAutocarro(vector<string>(lines));
    vector<Local *> pm = extrairEstacoesMetro();

    //Create temporary graph with parsed info
    inserirParagensNoGrafo(g, p);
    inserirEstacoesNoGrafo(g, pm);
    calculateWalkableEdges(g);

    //Save parsed info
    saveNodes(g);
    saveEdges(g);

    return;
}

int main() {
    Graph<Local*> g;
    int edgeID = 0;

    /* Abrir os ficheiros */

    ifstream i_nodes("nodes.txt");
    ifstream i_edges("edges.txt");

    if(!(i_nodes && i_edges))
        createFiles();

    loadFiles(g);

    /* Criar os locais */
    GraphViewer* gv = new GraphViewer(HSIZE, VSIZE, false);
    gv->setBackground("/home/afonso/Imagens/DiHnkJ2.jpg");
    gv->createWindow(1288, 766);

    for(int local = 0; local < g.getVertexSet().size(); local++){
        gv->addNode(g.getVertexSet().at(local)->getInfo()->getId(),g.getVertexSet().at(local)->getInfo()->getX(),g.getVertexSet().at(local)->getInfo()->getY());
    }

    for(int local = 0; local < g.getVertexSet().size(); local++){
        for(int ligacao = 0; ligacao < g.getVertexSet().at(local)->getAdj().size();ligacao++)
            gv->addEdge(edgeID++,g.getVertexSet().at(local)->getInfo()->getId(),g.getVertexSet().at(local)->getAdj().at(ligacao)->getDest()->getInfo()->getId(),EdgeType::DIRECTED);
    }

    cout << "Acabei!" << endl;

    /* Hora de mostrar a confusao total */
    gv->rearrange();

    #ifdef __linux__
    #else
        while(true) {}
    #endif

    return 0;
}