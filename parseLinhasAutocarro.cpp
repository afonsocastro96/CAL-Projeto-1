//
// Created by afonso on 24-04-2015.
//

#include <fstream>
#include <iostream>

#include "Local.h"
#include "parseLinhasAutocarro.h"
#include "symbolics.h"

vector<vector<Local *> > obterLinhasAutocarro(vector<string> nomeLinhas) {
    vector<vector<string> > linhas = extrairLinhasAutocarro(nomeLinhas);
    return parseLocais(linhas);
}

Local* parseLocal(string local) {
    /* Quando encontrada a palavra "coordinates", quer dizer que encontramos a informacao da latitude e longitude */
    unsigned index = local.find("coordinates");
    string xstr = "";
    string ystr = "";
    string name = "";

    while (true) {
        index++;
        /* Incrementar o index enquanto nao encontrarmos um numero */
        if (isdigit(local[index]) || local[index] == '-') {
            /* Numero encontrado, preencher o valor de x com esse numero */
            if (xstr.empty()) {
                xstr.push_back(local[index]);
                index++;
                /* Enquanto encontrarmos digitos ou um ponto, por para a string o numero */
                while (isdigit(local[index]) || local[index] == '.') {
                    xstr.push_back(local[index]);
                    index++;
                }
            }
            else {
                /* Fazer o mesmo para o y */
                ystr.push_back(local[index]);
                index++;
                while (isdigit(local[index]) || local[index] == '.') {
                    ystr.push_back(local[index]);
                    index++;
                }
                break;
            }
        }
    }

    /* Procurar o nome da paragem */
    index = local.find("name");
    index += 5;
    while (true) {
        index++;
        /* Se encontrarmos umas aspas, quer dizer que o nome vai comecar */
        if (local[index] == '"') {
            index++;
            /* Ler ate encontrarmos outras aspas */
            while (local[index] != '"') {
                name.push_back(local[index]);
                index++;
            }
            break;
        }
    }

    /* Conversao de latitude e longitude para valores de pixeis. Isto permite-nos representar graficamente o grafo com mais facilidade  */
    int x = (int) ((HSIZE * (stringToDouble(xstr) - XINICIAL)) / DELTAH) + MARGIN;
    int y = (int) ((VSIZE * (stringToDouble(ystr) - YINICIAL)) / DELTAV) + MARGIN;

    return new Local(x, y, name);
}

int paragemExiste(Graph<Local *> &g, Local *p){
    for(unsigned local = 0; local < g.getVertexSet().size(); local++) {
        if (*g.getVertexSet().at(local)->getInfo() == *p) {
            return local;
        }
    }
    return -1;
}

vector<vector<Local *> > parseLocais(vector<vector<string> > linhas) {
    vector<vector<Local *> > vecLinhas;
    vector<Local *> locais;

    /*  */
    for (unsigned linha = 0; linha < linhas.size(); linha++) {
        for (unsigned local = 0; local < linhas[linha].size(); local++) {
            locais.push_back(parseLocal(linhas[linha][local]));
        }
        vecLinhas.push_back(locais);
        locais.clear();
    }
    return vecLinhas;
}

vector<vector<string> > extrairLinhasAutocarro(vector<string> linhas) {
    string linhaAtual;
    vector<vector<string> > ret;

    for (unsigned linha = 0; linha < linhas.size(); linha++) {
        for (int sentido = 0; sentido <= 1; sentido++) {
            char sentidoStr = sentido + 48; //Such conversao de int para char, much ilegivel daqui a 2 semanas, wow.
            linhaAtual = "linha" + linhas[linha] + "sentido" + sentidoStr;
            ret.push_back(extraiLinha(linhaAtual));
        }

    }

    return ret;
}

vector<string> extraiLinha(string fichLinhaAtual) {
    ifstream i_ficheiro;
    string path = PATH_TO_LINHAS + fichLinhaAtual;
    i_ficheiro.open(path.c_str());
    vector<string> locals;


    if (!i_ficheiro) {
        cout << "Falha ao abrir o ficheiro "<< path << endl;
        return locals;
    }

    string file;
    getline(i_ficheiro, file);
    string locations = file.substr(file.find("locations"));
    string local;
    unsigned index = 0;
    int nChavetas = 0;

    /* Ler a o ficheiro com a linha */
    while (index != locations.size()) {
        index++;
        /* Quando encontrarmos uma chaveta, temos de ler toda a informacao ate encontrar a chaveta que fecha esta */
        if (locations[index] == '{') {
            nChavetas++;
            local.push_back(locations[index]);
            while (!(locations[index] == '}' && nChavetas == 0)) {
                index++;
                /* Atualizar o numero de chavetas */
                if (locations[index] == '{')
                    nChavetas++;
                else if (locations[index] == '}')
                    nChavetas--;
                local.push_back(locations[index]);
            }
            /* Colocar a paragem no vetor, voltar ao inicio do ciclo para ir buscar a paragem seguinte */
            locals.push_back(local);
            local = "";
        }
    }

    return locals;
}

void inserirParagensNoGrafo(Graph<Local *> &g, vector<vector<Local *> > locais){
    int lastBusLocal;
    int index;
    for(int linha = 0; linha < locais.size();linha++){

        if(locais[linha].size() == 0)
            continue;

        /* Se o local ja existir, nao e preciso fazer mais nada, pois a funcao paragemExiste() ja coloca o indice da
         * ultima estacao lida. */
        lastBusLocal = paragemExiste(g, locais[linha][0]);


        /* Primeiro local nao existe, adicionar ao grafo e atualizar o valor da ultima paragem de autocarro */
        if(lastBusLocal == -1) {
            locais[linha][0]->setId(g.getNumVertex());
            g.addVertex(locais[linha][0]);
            lastBusLocal = g.getNumVertex() - 1;
        }

        /* Inserir os locais seguintes da linha. O primeiro tem de estar separado dos restantes por causa das ligacoes
         * entre os vertices. */
        for(int local = 1; local < locais[linha].size();local++){
            index = paragemExiste(g, locais[linha][local]);
            /* O mesmo raciocinio que a primeira paragem */
            if(index == -1) {
                locais[linha][local]->setId(g.getNumVertex());
                g.addVertex(locais[linha][local]);

                g.addEdge(g.getVertexSet().at(lastBusLocal)->getInfo(),g.getVertexSet().at(g.getNumVertex()-1)->getInfo(),1, 1, BUS);
                lastBusLocal = g.getNumVertex()-1;

                if(locais[linha][local]->getId() == 1224){
                    cout << "cenas";
                }
            }
            else {
                bool alreadyHaveEdge = false;
                for(int k = 0; k < g.getVertexSet().at(lastBusLocal)->getAdj().size(); k++) {
                    if (g.getVertexSet().at(lastBusLocal)->getAdj().at(k)->getDest()->getInfo() == g.getVertexSet().at(index)->getInfo()) {
                        alreadyHaveEdge = true;
                        break;
                    }
                }

                if(index == 1224){
                    cout << "cenas";
                }

                if(!alreadyHaveEdge)
                    g.addEdge(g.getVertexSet().at(lastBusLocal)->getInfo(),g.getVertexSet().at(index)->getInfo(), 1, 1, BUS);
                lastBusLocal = index;
            }
        }
    }
}