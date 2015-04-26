//
// Created by afonso on 24-04-2015.
//

#include <iostream>
#include <fstream>

#include "symbolics.h"
#include "Graph.h"
#include "Local.h"
#include "parseLinhasMetro.h"

bool estacaoExiste(vector<Local *> locals, Local *local){
    for(int i = 0; i < locals.size(); i++){
        if(locals[i]->getNome() == local->getNome()){
            return true;
        }
    }

    return false;
}

vector<Local *> extrairEstacoesMetro(){
    vector<Local *> locais;

    ifstream i_ficheiro;
    string path = SUBWAYSTOPSFILE;
    i_ficheiro.open(path.c_str());
    string line;

    int x;
    int y;
    string name = "";
    string xstr = "";
    string ystr = "";
    int index;

    if (!i_ficheiro) {
        cout << "Falha ao abrir o ficheiro "<< path << endl;
        return locais;
    }

    /* Le linhas ate chegar ao fim do ficheiro  */
    while(!i_ficheiro.eof()){
        getline(i_ficheiro,line);
        /* Quando encontrar a string "lon" quer dizer que encontrou a longitude de uma estacao */
        index = line.find("\"lon\"");
        if(index != -1){
            while(!isdigit(line[index]))
                index++;
            index--; //Necessario porque as coordenadas em x sao negativas
            /* Encontrou um digito. Enquanto houver potenciais digitos de um numero, continuar a ler */
            while(isdigit(line[index]) || line[index] == '.' || line[index] == '-')
                xstr.push_back(line[index++]);
            /* Converter de coordenadas geograficas para pixeis representaveis no grafo */
            x = (int) ((HSIZE * (stringToDouble(xstr)-XINICIAL)) / DELTAH) + MARGIN;
            xstr = "";
        }

        /* Mesmo raciocinio da longitude, mas para a latitude */
        index = line.find("\"lat\"");
        if(index != -1){
            while(!isdigit(line[index]))
                index++;
            while(isdigit(line[index]) || line[index] == '.' || line[index] == '-')
                ystr.push_back(line[index++]);
            y = (int) ((VSIZE * (stringToDouble(ystr)-YINICIAL)) / DELTAV) + MARGIN;



            ystr = "";
        }

        /* Encontrou o nome da paragem. Le-lo */
        index = line.find("\"name\": \"");
        if(index != -1){
            index+=9; //Avanco necessario para ler corretamente o nome da paragem.
            /* Enquanto nao encontrar uma aspa, ler o nome da estacao */
            while(line[index] != '\"')
                name.push_back(line[index++]);

            /* Dado que o ficheiro obtido do openstreetmaps vem com bastante informacao inutil depois das estacoes,
             * quando o texto "Linha B" estiver escrito na string, quer dizer que chegamos a esse ponto. Parar o ciclo */
            if (line.find("Linha B") != -1)
                break;

            Local* local = new Local(x, y, name);
            if(!(x < 0 || y < 0 || x > HSIZE || y > VSIZE) && !estacaoExiste(locais, local)) {
                locais.push_back(local);
                cout << local->getNome() << endl;
                cout << local->getX() << endl;
                cout << local->getY() << endl << endl;
            }
            name = "";
        } else {
            continue;
        }
    }

    return locais;
}

void inserirEstacoesNoGrafo(Graph<Local *> &g, vector<Local *> locais){
    string paragemMetro = "";
    string linhaMetro = "linhas/metro/linha";
    ifstream i_ficheiro;
    int index = -1;
    int previousIndex = -1;
    char letraLinhaMetro = 'A';
    int teste;

    i_ficheiro.open((linhaMetro + letraLinhaMetro).c_str());

    /* A funcao espera ficheiros com o nome linha[letra da linha]. Para quando ja nao conseguir abrir mais, ou seja,
     * quando tivermos ultrapassado a ultima linha */
    while(i_ficheiro){

        getline(i_ficheiro,paragemMetro);
        /* Coloca a primeira paragem da linha no grafo. E necessario separar a primeira das seguintes para poder colocar
         * as arestas entre as paragens. */
        for(int paragem = 0; paragem < locais.size(); paragem++){
            if(paragemMetro == locais[paragem]->getNome()){
                previousIndex = g.addVertex(locais[paragem]);
                if(previousIndex == g.getNumVertex() - 1)
                    locais[paragem]->setId(g.getNumVertex()-1);
                cout << "Local: " << locais[paragem]->getNome() << endl;
                cout << "Id da primeira paragem: " << locais[paragem]->getId() << endl;
                break;
            }
        }

        /* Coloca as paragens seguintes */
        while(!i_ficheiro.eof()){
            getline(i_ficheiro,paragemMetro);
            for(int paragem = 0; paragem < locais.size(); paragem++){
                if(paragemMetro == locais[paragem]->getNome()){
                    index = g.addVertex(locais[paragem]);
                    if(index != -1) {
                        cout << "Local v2: " << g.getVertexSet().at(index)->getInfo()->getNome() << endl;
                        if(index == g.getNumVertex() - 1)
                            g.getVertexSet().at(index)->getInfo()->setId(index);
                    }
                    break;

                }
            }

            bool alreadyHaveEdge = false;
            for(int k = 0; k < g.getVertexSet().at(previousIndex)->getAdj().size(); k++) {
                if (g.getVertexSet().at(previousIndex)->getAdj().at(k)->getDest()->getInfo() == g.getVertexSet().at(index)->getInfo()) {
                    alreadyHaveEdge = true;
                    break;
                }
            }

            cout << previousIndex << " " << index << endl;
            if(!alreadyHaveEdge)
                g.addEdge(g.getVertexSet().at(previousIndex)->getInfo(),g.getVertexSet().at(index)->getInfo(), 1, 1, METRO);
            previousIndex = index;
        }

        /* Fim da linha, preparar a leitura da linha seguinte */
        letraLinhaMetro++; //Mais uma conversao de int para char.
        i_ficheiro.close();
        i_ficheiro.open((linhaMetro + letraLinhaMetro).c_str());
    }
}

