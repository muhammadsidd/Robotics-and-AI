#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <queue>
#include <utility>

using namespace std;


class Vertex {
public:
	int labelx;
	int labely;
	int labelz;
	unsigned long minDist;
	vector<Vertex> shortestPath;
	bool visited;
	
};


class Edge {
public:
	Vertex A;
	Vertex B;
	int w;
};

class Graph {
	friend class Vertex;
	friend class Edge;

public:
	void addVertex(int labelx, int labely, int labelz);
	void addEdge(Vertex A, Vertex B, int w);
	vector<Vertex> vertices;
	vector<Edge> edges;
	vector<Vertex> getNeighbors(Vertex a_,int distance, int numberOfNeigh); 
	int distance(int x, int y, int z, int x2, int y2, int z2);
	void shortestPath(const Vertex start, const Vertex end, vector<Vertex>& path);
};

#endif
