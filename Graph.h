/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <limits.h>
#include <cstddef>
#include <math.h>
#include "symbolics.h"

using namespace std;

const int INT_INFINITY = INT_MAX;

enum Preference {
    PRICE,
    DISTANCE,
    TIME,
    SWAP
};

enum Transport {
    METRO,
    BUS,
    WALK
};

template<class T>
class Edge;

template<class T>
class Graph;

template<class T>
class Vertex {
    T info;
    vector<Edge<T> *> adj;
    bool visited;

    bool processing;

    double cost;

    long double x;

    long double y;

    void addEdge(Vertex<T> *d, Vertex<T> *o, double price, double distance, Transport transport);

    bool removeEdgeTo(Vertex<T> *d);

public:
    Vertex* path;

    Vertex(T in, int x, int y);

    friend class Graph<T>;

    double getCost() { return cost; }

    vector<Edge<T> *> getAdj() const;

    T getInfo() const;
};

template<class T>
vector<Edge<T> *> Vertex<T>::getAdj() const {
    return adj;
}

template<class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
    typename vector<Edge<T> *>::iterator it = adj.begin();
    typename vector<Edge<T> *>::iterator ite = adj.end();
    while (it != ite) {
        if ((*it)->dest == d) {
            adj.erase(it);
            return true;
        }
        else it++;
    }
    return false;
}

template<class T>
Vertex<T>::Vertex(T in, int x, int y) : info(in), x(x), y(y), visited(false) { }

template<class T>
T Vertex<T>::getInfo() const {
    return this->info;
}


template<class T>
void Vertex<T>::addEdge(Vertex<T> *d, Vertex<T> *o, double price, double distance, Transport transport) {
    Edge<T> * edgeD = new Edge<T>(d, o, price, distance, transport);
    adj.push_back(edgeD);
}

template<class T>
class Edge {
    Vertex<T> * dest;
    Vertex<T> * orig;
    double price;
    double distance;
    Transport transport;
public:
    Edge(Vertex<T> *d, Vertex<T> *o, double price, double distance, Transport transport) ;

    Vertex<T> *getDest();

    double getPrice() { return price; }

    double getDistance() { return distance; }

    Transport getTransport() { return transport; }

    friend class Graph<T>;

    friend class Vertex<T>;
};

template<class T>
Vertex<T> *Edge<T>::getDest() {
    return dest;
}

template<class T>
Edge<T>::Edge(Vertex<T> *d, Vertex<T> *o, double price, double distance, Transport transport) : dest(d), orig(o), price(price), distance(distance), transport(transport) { }

template<class T>
class Graph {
    vector<Vertex<T> *> vertexSet;

    void dfs(Vertex<T> *v, vector<T> &res) const;

public:
    int addVertex(T &in, long double x, long double y);

    bool addEdge(const T &sourc, const T &dest, double price, double distance, Transport transport);

    bool removeVertex(const T &in);

    bool removeEdge(const T &sourc, const T &dest);

    vector<T> dfs() const;

    vector<T> bfs(Vertex<T> *v) const;

    int maxNewChildren(Vertex<T> *v, T &inf) const;

    Vertex<T>* getVertex(const T &v) const;

    vector<Vertex<T> *> getVertexSet() { return vertexSet; }

    int getNumVertex() const;

    void aStarShortestPath(const Vertex<T> &source, const Vertex<T> &dest, Preference preferencia);
};

template<class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
Vertex<T>* Graph<T>::getVertex(const T &v) const {
    for(unsigned int i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->info == v) return vertexSet[i];
    return NULL;
}

template<class T>
int Graph<T>::addVertex(T &in, long double x, long double y) {
    typename vector<Vertex<T> *>::iterator it = vertexSet.begin();
    typename vector<Vertex<T> *>::iterator ite = vertexSet.end();
    for (; it != ite; it++)
        if ((*it)->info == in) {
            return it - vertexSet.begin();
        }
    Vertex<T> *v1 = new Vertex<T>(in, x, y);
    vertexSet.push_back(v1);
    return getNumVertex()-1;
}

template<class T>
bool Graph<T>::removeVertex(const T &in) {
    typename vector<Vertex<T> *>::iterator it = vertexSet.begin();
    typename vector<Vertex<T> *>::iterator ite = vertexSet.end();
    for (; it != ite; it++) {
        if ((*it)->info == in) {
            Vertex<T> *v = *it;
            vertexSet.erase(it);
            typename vector<Vertex<T> *>::iterator it1 = vertexSet.begin();
            typename vector<Vertex<T> *>::iterator it1e = vertexSet.end();
            for (; it1 != it1e; it1++) {
                (*it1)->removeEdgeTo(v);
            }
            delete v;
            return true;
        }
    }
    return false;
}

template<class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double price, double distance, Transport transport) {
    typename vector<Vertex<T> *>::iterator it = vertexSet.begin();
    typename vector<Vertex<T> *>::iterator ite = vertexSet.end();
    int found = 0;
    Vertex<T> *vS, *vD;
    while (found != 2 && it != ite) {
        if ((*it)->info == sourc) {
            vS = *it;
            found++;
        }
        if ((*it)->info == dest) {
            vD = *it;
            found++;
        }
        it++;
    }
    if (found != 2) return false;
    vS->addEdge(vD, vS, price, distance, transport);
    return true;
}

template<class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    typename vector<Vertex<T> *>::iterator it = vertexSet.begin();
    typename vector<Vertex<T> *>::iterator ite = vertexSet.end();
    int found = 0;
    Vertex<T> *vS, *vD;
    while (found != 2 && it != ite) {
        if ((*it)->info == sourc) {
            vS = *it;
            found++;
        }
        if ((*it)->info == dest) {
            vD = *it;
            found++;
        }
        it++;
    }
    if (found != 2) return false;
    return vS->removeEdgeTo(vD);
}

template <class T>
struct vertex_greater_than {
    bool operator()(Vertex<T> * a, Vertex<T> * b) const {
        return a->getCost() > b->getCost();
    }
};

template <class T>
void Graph<T>::aStarShortestPath(const Vertex<T> &source, const Vertex<T> &dest, Preference preferencia) {
    for(unsigned int i = 0; i < vertexSet.size(); i++) {
        vertexSet[i]->path = NULL;
        vertexSet[i]->cost = INT_INFINITY;
        vertexSet[i]->processing = false;
    }

    Transport lastTransport;

    double xGeoSource, yGeoSource, xGeoDest, yGeoDest, costEdge, distanceToDest;

    xGeoDest = (((dest.x - MARGIN) * DELTAH) / HSIZE) + XINICIAL;
    xGeoDest *= LONGITUDE_UNIT;
    yGeoDest = (((dest.y - MARGIN) * DELTAV) / VSIZE) + YINICIAL;
    yGeoDest *= LATITUDE_UNIT;

    Vertex<T>* v = &source;
    v->cost = 0;

    vector< Vertex<T>* > pq;
    pq.push_back(v);

    make_heap(pq.begin(), pq.end());

    while( !pq.empty() ) {

        v = pq.front();
        pop_heap(pq.begin(), pq.end());
        pq.pop_back();

        if(v->getInfo() == dest)
            break;

        xGeoSource = (((v->x - MARGIN) * DELTAH) / HSIZE) + XINICIAL;
        xGeoSource *= LONGITUDE_UNIT;
        yGeoSource = (((v->y - MARGIN) * DELTAV) / VSIZE) + YINICIAL;
        yGeoSource *= LATITUDE_UNIT;

        for(unsigned int i = 0; i < v->adj.size(); i++) {
            Vertex<T>* w = v->adj[i]->dest;

            distanceToDest = sqrt(pow(xGeoDest - xGeoSource, 2) + pow(yGeoDest - yGeoSource, 2));

            if(preferencia == PRICE) {
                costEdge = distanceToDest * v->adj[i]->price;
            } else if(preferencia == DISTANCE) {
                costEdge = distanceToDest * v->adj[i]->distance;
            } else if(preferencia == TIME) {
                if(v->adj[i]->transport == METRO) {
                    costEdge = distanceToDest * v->adj[i]->distance / 25;
                } else if(v->adj[i]->transport == BUS) {
                    costEdge = distanceToDest * v->adj[i]->distance / 15;
                } else {
                    costEdge = distanceToDest * v->adj[i]->distance / 5;
                }
            } else if(preferencia == SWAP) {
                if(v->adj[i]->transport != lastTransport)
                    costEdge = distanceToDest * 1;
                else
                    costEdge = 0;
            }

            if(v->cost + costEdge < w->cost ) {
                w->cost = v->cost + costEdge;
                w->path = v;

                //se ja estiver na lista, apenas a actualiza
                if(!w->processing)
                {
                    w->processing = true;
                    pq.push_back(w);
                }

                lastTransport = v->adj[i]->transport;

                make_heap (pq.begin(),pq.end(),vertex_greater_than<T>());
            }
        }
    }
}



#endif /* GRAPH_H_ */
