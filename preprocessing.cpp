//
// Created by afonso on 21-04-2015.
//
#include <fstream>
#include <iostream>

#include "preprocessing.h"
#include "symbolics.h"

using namespace std;

/**
 * - eliminar repetidos bus
 * - elimininar repetidos metro
 * - adicionar tudo ao grafo
 * - calcular arestas "walkable" e adicionar
 */


void saveNodes(Graph<Local*> &graph) {
    ofstream o;
    o.open("nodes.txt");

    vector<Vertex<Local*> *> vertices = graph.getVertexSet();
    Vertex<Local*> * local;
    for(unsigned int i = 0; i < vertices.size(); i++) {
        local = vertices.at(i);
        o << *(local->getInfo()) << endl << endl;
    }
}

void saveEdges(Graph<Local*> &graph) {
    ofstream o;
    o.open("edges.txt");

    vector<Vertex<Local*> *> vertices = graph.getVertexSet();
    Vertex<Local*> * local;
    vector<Edge<Local*> *> edges;
    Edge<Local*> * edge;
    for(unsigned int i = 0; i < vertices.size(); i++) {
        local = vertices.at(i);
        edges = local->getAdj();
        for(unsigned int j = 0; j < edges.size(); j++) {
            edge = edges.at(j);
            o << local->getInfo()->getId() << " " << edge->getDest()->getInfo()->getId() << " " << edge->getDistance() << " " << edge->getPrice() << " " << edge->getTransport() << endl;

        }
    }
}

void calculateWalkableEdges(Graph<Local*> &graph) {
    vector<Vertex<Local*> *> vertices = graph.getVertexSet();
    Vertex<Local *> * sourceLocal; Vertex<Local *> * destLocal;
    Edge<Local *> * destEdge;
    bool edgeWithSameSource = false;
    double xGeoSource, yGeoSource, xGeoDest, yGeoDest, distance;

    // Loop for all vertices to check which might be connected to others with walkable edges
    for(unsigned int i = 0; i < vertices.size(); i++) {
        sourceLocal = vertices.at(i);
        xGeoSource = (((sourceLocal->getInfo()->getX() - MARGIN) * DELTAH) / HSIZE) + XINICIAL;
        xGeoSource *= LONGITUDE_UNIT;
        yGeoSource = (((sourceLocal->getInfo()->getY() - MARGIN) * DELTAV) / VSIZE) + YINICIAL;
        yGeoSource *= LATITUDE_UNIT;

        // Check which vertices might be connected as walkable edges
        for(unsigned int j = 0; j < vertices.size(); j++) {
            destLocal = vertices.at(j);
            if(sourceLocal->getInfo() == destLocal->getInfo())
                continue;

            xGeoDest = (((destLocal->getInfo()->getX() - MARGIN) * DELTAH) / HSIZE) + XINICIAL;
            xGeoDest *= LONGITUDE_UNIT;
            yGeoDest = (((destLocal->getInfo()->getY() - MARGIN) * DELTAV) / VSIZE) + YINICIAL;
            yGeoDest *= LATITUDE_UNIT;

            distance = sqrt(pow(xGeoDest - xGeoSource, 2) + pow(yGeoDest - yGeoSource, 2));
            if(distance > MAX_DISTANCE)
                continue;

            // Check if there is an edge with the same destination
            edgeWithSameSource = false;
            for(unsigned int k = 0; k < sourceLocal->getAdj().size(); k++) {
                destEdge = sourceLocal->getAdj().at(k);
                if(destEdge->getDest()->getInfo() == destLocal->getInfo()) {
                    edgeWithSameSource = true;
                    break;
                }
            }

            if(edgeWithSameSource)
                continue;

            graph.addEdge(sourceLocal->getInfo(), destLocal->getInfo(), distance * FOOTPRICEPERMETER, distance, WALK);
        }
    }
}
