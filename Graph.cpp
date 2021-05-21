#include "Graph.hpp"
#include <math.h>
#include<iostream>
//setting up constructor for the edge class


//deallocating dynamic memory through deconstructor

void Graph::addVertex(int labelx_, int labely_, int labelz_)
{
	Vertex newVertex; //add Vertex
	newVertex.labelx = labelx_;
	newVertex.labely = labely_; //set value of the vertex point
	newVertex.labelz = labelz_;	//flag variable turned off as it is not yet visited
	newVertex.minDist = 0x3f3f3f3f;  //setting the distance to infinity because it is not yet connected to anything
	newVertex.visited = false;	
	vertices.push_back(newVertex); //add to the vertices vector
}
vector<Vertex> Graph::getNeighbors(Vertex A_, int dist, int num)
{int a;

	vector<Vertex> Neighbors;
	while (Neighbors.size() < num)
	{
		for (Vertex vert : vertices)
		{
			if ((vert.labelx != A_.labelx) && (vert.labely != A_.labely) && (vert.labelz != A_.labelz))
			{	a = distance(A_.labelx, A_.labely, A_.labelz,
				vert.labelx, vert.labely, vert.labelz);
				//cout<<"this is the dist "<<a<<endl;
				//break;
				if (a <= dist)
				{
					Neighbors.push_back(vert);
				}
			}
			//cout<<"what?"<<endl;
		}
		//cout<<"listen"<<endl;
		//break;
	}
	return Neighbors;
}
	int Graph::distance(int x, int y, int z, int x2, int y2, int z2)
	{ int answer;
	//cout<<z<<z2<<endl;
	answer =ceil(sqrt(pow((x2 - x), 2) + pow((y2 - y), 2) + pow((z2 - z), 2)));
	//cout<<answer;
		return answer;
	}

	//method to connect the edges
	void Graph::addEdge(Vertex A_, Vertex B_, int dist)
	{ //connect edge to vertex

		Edge edge;
		edge.A = A_;
		edge.B = B_;
		edge.w = dist;
		edges.push_back(edge);

	
		
	}
	void Graph::shortestPath(const Vertex start, const Vertex end, vector<Vertex>& path)
{
	

//set the start point to the value inserted by the user
	for (unsigned int i = 0; i < vertices.size(); i++) {
		if (vertices.at(i).labelx == start.labelx && vertices.at(i).labely == start.labely && vertices.at(i).labelz == start.labelz ) {
			vertices.at(i).minDist = 0;
			vertices.at(i).shortestPath.clear();
			vertices.at(i).shortestPath.push_back(start); //start ipoint set with distance 0
		}
	}

//put the paths visited in the priority queue
	queue<Vertex> shortPaths;
//make the first pair
	shortPaths.push(start);

	do {
		Vertex minElem = shortPaths.front();//move to the top
		shortPaths.pop();	//remove it

		int minVertexIndex;
		for (unsigned int i = 0; i < vertices.size(); i++) {
			if (vertices.at(i).labelx == minElem.labelx &&vertices.at(i).labely == minElem.labely &&vertices.at(i).labelz == minElem.labelz) {
				minVertexIndex = i;
			}
		}

		for (unsigned int j = 0; j < edges.size(); j++) {
			if (edges.at(j).A.labelx == minElem.labelx && edges.at(j).A.labely == minElem.labely && edges.at(j).A.labelz == minElem.labelz) {
				for (unsigned int k = 0; k < vertices.size(); k++) { //if the smallest path is available then update the current weight to the new weight and add the min distance to the weight
					if ((edges.at(j).B.labelx == vertices.at(k).labelx && edges.at(j).B.labely == vertices.at(k).labely && edges.at(j).B.labelz == vertices.at(k).labelz) && 
					((vertices.at(minVertexIndex).minDist + edges.at(j).w) < vertices.at(k).minDist) && (vertices.at(k).visited == false)) {
						vertices.at(k).minDist = vertices.at(minVertexIndex).minDist + edges.at(j).w;
						if (minElem.labelx == start.labelx && minElem.labely == start.labely &&minElem.labelz == start.labelz) {
							vertices.at(k).shortestPath.clear();
							vertices.at(k).shortestPath.push_back(start);
						}
						else {
							vertices.at(k).shortestPath.clear();
							vertices.at(k).shortestPath = vertices.at(minVertexIndex).shortestPath;
							vertices.at(k).shortestPath.push_back(vertices.at(minVertexIndex));
						}
						shortPaths.push(vertices.at(k));
					}
				}
			}
		}
		vertices.at(minVertexIndex).visited = true; //once the node/vertex is visited it is added to the list of shortest path and never visited again
	}while (!shortPaths.empty()); //do this until the list is complete


	for (unsigned int i = 0; i < vertices.size(); i++) {
		if (end.labelx == vertices.at(i).labelx && end.labely == vertices.at(i).labely && end.labelz == vertices.at(i).labelz) {
			//shortestDist = vertices.at(i).minDist;
			vertices.at(i).shortestPath.push_back(end);
			path = vertices.at(i).shortestPath;
		}
	}


}
	
