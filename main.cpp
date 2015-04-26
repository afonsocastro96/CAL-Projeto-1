#include "init.h"

using namespace std;

Graph<Local*> g;

int resX = 1024;
int resY = 768;

void callUpdateBusScript(){
#ifdef __linux__
    string command = "sh /home/afonso/Documentos/CAL/Projeto - Itinerarios Multimodais/ProjetoItinerariosMultiModais/linhas/autocarro/download.sh";
    system(command.c_str());
#else
#endif
}

void callUpdateSubwayScript(){
#ifdef __linux__
    string command = "sh /home/afonso/Documentos/CAL/Projeto - Itinerarios Multimodais/ProjetoItinerariosMultiModais/linhas/metro/download.sh";
    system(command.c_str());
#else
#endif
}

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

void init(Graph<Local*> &g){

    /* Abrir os ficheiros */
    ifstream i_nodes("nodes.txt");
    ifstream i_edges("edges.txt");

    if(!(i_nodes && i_edges))
        createFiles();

    loadFiles(g);
}


int exec(Graph<Local*> &g){
    int edgeID = 0;

    g.aStarShortestPath(*g.getVertexSet().at(2385),*g.getVertexSet().at(1001), DISTANCE);

    /* Criar os locais */
    GraphViewer* gv = new GraphViewer(HSIZE, VSIZE, false);
    gv->setBackground("/home/afonso/Imagens/DiHnkJ2.jpg");
    gv->createWindow(resX, resY);


    for(unsigned int local = 0; local < g.getVertexSet().size(); local++){
        gv->addNode(g.getVertexSet().at(local)->getInfo()->getId(),g.getVertexSet().at(local)->getInfo()->getX(),g.getVertexSet().at(local)->getInfo()->getY());
    }

    g.paintBestPath(*g.getVertexSet().at(2385),*g.getVertexSet().at(1001),gv);

    cout << "Acabei!" << endl;

    /* Update graph */
    gv->rearrange();

    #ifdef __linux__
    #else
        while(true) {}
    #endif

    return 0;
}

void showFullMap(){
    int edgeID = 0;

    /* Criar os locais */
    GraphViewer* gv = new GraphViewer(HSIZE, VSIZE, false);
    gv->setBackground("/home/afonso/Imagens/DiHnkJ2.jpg");
    gv->createWindow(resX, resY);


    for(unsigned int local = 0; local < g.getVertexSet().size(); local++){
        gv->addNode(g.getVertexSet().at(local)->getInfo()->getId(),g.getVertexSet().at(local)->getInfo()->getX(),g.getVertexSet().at(local)->getInfo()->getY());
        gv->setVertexLabel(g.getVertexSet().at(local)->getInfo()->getId(),g.getVertexSet().at(local)->getInfo()->getNome());
    }

    for(unsigned int local = 0; local < g.getVertexSet().size(); local++){
        for(unsigned int ligacao = 0; ligacao < g.getVertexSet().at(local)->getAdj().size();ligacao++){
            if(g.getVertexSet().at(local)->getAdj().at(ligacao)->getTransport() != WALK)
                gv->addEdge(edgeID++,g.getVertexSet().at(local)->getInfo()->getId(),g.getVertexSet().at(local)->getAdj().at(ligacao)->getDest()->getInfo()->getId(),EdgeType::DIRECTED);
       }
    }


    cout << "Acabei!" << endl;

    /* Update graph */
    gv->rearrange();

    #ifdef __linux__
    #else
        while(true) {}
    #endif
}



int main(int argc, char *argv[]) {
    init(g);
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Planeamento de Itinerários Multimodais");
    w.show();

    return a.exec();
}
