#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <queue>
#include <vector>
#include "Graph.hpp"
#define infinity 10000000
using namespace std;
vector<vector<vector<int>>> World;
unsigned long shortestPath(Graph &tree, Vertex &StartNode, Vertex &EndNode, vector<Vertex> &path);
int distance(int x, int y, int z, int x2, int y2, int z2);
bool path_exists(vector<vector<vector<int>>> &space, Vertex A_, Vertex B_);

int main()
{
    string line;
    int xupper;
    int xlower;
    int yupper;
    int ylower;
    int zupper;
    int zlower;
    int obs1x, obs1y, obs1z, edge1;
    int obs2x, obs2y, obs2z, edge2;
    int obs3x, obs3y, obs3z, edge3;
    int obs4x, obs4y, obs4z, edge4;
    int startx, starty, startz;
    int goalx, goaly, goalz;
    string filename;
    ifstream input_file;
    cout << "Please enter file name." << endl;
    cin >> filename;
    input_file.open(filename);
    while (input_file)
    {
        input_file >> xlower >> xupper >> ylower >> yupper >> zlower >> zupper >> obs1x >> obs1y >> obs1z >> edge1 >> obs2x >> obs2y >> obs2z >> edge2 >> obs3x >> obs3y >> obs3z >> edge3 >> obs4x >> obs4y >> obs4z >> edge4 >> startx >> starty >> startz >> goalx >> goaly >> goalz;
    }
    input_file.close();

    cout << "here is the cofigration space\n"
         << xlower << " " << xupper << "\n"
         << ylower << " " << yupper << "\n"
         << zlower << " " << zupper << "\n"
         << obs1x << " " << obs1y << " " << obs1z << " " << edge1 << "\n"
         << obs2x << " " << obs2y << " " << obs2z << " " << edge2 << "\n"
         << obs3x << " " << obs3y << " " << obs3z << " " << edge3 << "\n"
         << obs4x << " " << obs4y << " " << obs4z << " " << edge4 << "\n"
         << startx << " " << starty << " " << startz << "\n"
         << goalx << " " << goaly << " " << goalz << "\n";

    World.resize((xupper - xlower) + 2);
    for (int i = 0; i < ((xupper - xlower) + 2); i++)
    {
        World.at(i).resize((yupper - ylower) + 2);
        for (int j = 0; j < ((yupper - ylower) + 2); j++)
        {
            World.at(i).at(j).resize((zupper - zlower) + 2);
        }
    }
    for (int i = (obs1x - ((edge1 / 2))); i < ((edge1 / 2)) + (obs1x); i++)
    {
        for (int j = (obs1y - ((edge1 / 2))); j < ((edge1 / 2)) + obs1y; j++)
        {
            for (int k = (obs1z - ((edge1 / 2))); k < ((edge1 / 2)) + obs1z; k++)
            {

                World.at(i).at(j).at(k) = -1;
            }
        }
    }
    for (int i = (obs2x - ((edge1 / 2) + 1)); i < ((edge2 / 2)) + obs2x; i++)
    {
        for (int j = ((obs2y) - ((edge2 / 2))); j < ((edge2 / 2)) + obs2x; j++)
        {
            for (int k = (obs2z - ((edge2 / 2))); k < ((edge2 / 2)) + (obs2z); k++)
            {

                World.at(i).at(j).at(k) = -1;
            }
        }
    }

    for (int i = xlower; i < xupper; i++)
    {
        for (int j = ylower; j < yupper; j++)
        {
            for (int k = zlower; k < zupper; k++)
            {
                if (pow((i - obs3x), 2) + (pow((j - obs3y), 2)) + (pow((k - obs3z), 2)) <= (int)((pow(edge3, 2) + 1)))
                {
                    World.at(i).at(j).at(k) = -1;
                }
            }
        }
    }
    for (int i = xlower; i < xupper - 1; i++)
    {
        for (int j = ylower; j < yupper - 1; j++)
        {
            for (int k = zlower; k < zupper - 1; k++)
            {
                if (pow((i - obs4x), 2) + (pow((j - obs4y), 2)) + (pow((k - obs4z), 2)) <= (int)((pow(edge4, 2) + 1)))
                {
                    World.at(i).at(j).at(k) = -1;
                }
            }
        }
    }
   
    int len = 3000;
    int neigh = 5;
    int dist = 8;
    int x;
    int y;
    int z;
    Graph tree;
    Vertex FirstNode;
    Vertex LastNode;
    FirstNode.labelx = startx;
    FirstNode.labely = starty;
    FirstNode.labelz = startz;
    LastNode.labelx = goalx;
    LastNode.labely = goaly;
    LastNode.labelz = goalz;
    tree.addVertex(FirstNode.labelx, FirstNode.labely, FirstNode.labelz);
    
    while (tree.vertices.size() < len)
    {
        x = rand() % (xupper + xlower);
        y = rand() % (yupper + ylower);
        z = rand() % (zupper + zlower);

        if (World.at(x).at(y).at(z) == -1 && World.at(x).at(y).at(z) != 0)
        {
            continue;
        }
        else
        {
            World.at(x).at(y).at(z) = 2;
            Vertex vertex;
            vertex.labelx = x;
            vertex.labely = y;
            vertex.labelz = z;
            tree.addVertex(vertex.labelx, vertex.labely, vertex.labelz);
        }
    }
    
    tree.addVertex(LastNode.labelx, LastNode.labely, LastNode.labelz);

    cout << "Linking Vertices please wait .. Getting Neighboring Vertices and Adding Edges" << endl;
    vector<Vertex> nei;
    int getdist_ = 0 ;
    for (Vertex vert : tree.vertices)
    {
        nei = tree.getNeighbors(vert, dist, neigh);

        for (Vertex v : nei)
        {
            if (path_exists(World, vert, v) == true)
            {   getdist_ = distance(vert.labelx,vert.labely, vert.labelz, v.labelx, v.labely, v.labelz);
                    tree.addEdge(vert, v, getdist_);
                    
            }
        }
    }
    
    ofstream myfile1;
    myfile1.open("Edges.txt");
    for (Edge e : tree.edges)
    {
        myfile1 << e.A.labelx << "," << e.A.labely << "," << e.A.labelz <<endl;
        myfile1 << e.B.labelx << "," << e.B.labely << "," << e.B.labelz <<endl;
        

    }

    ofstream myfile;
    myfile.open("Neighbors.txt");

    for (Vertex v : tree.vertices)
    {
        
        myfile << v.labelx << "," << v.labely << "," << v.labelz << endl;
    }

    vector<Vertex>path;

    tree.shortestPath(FirstNode,LastNode,path);
    ofstream myfile4;
    myfile4.open("linesegment.txt");
    for(int i=0; i< path.size(); i++){
        myfile4<<path.at(i).labelx<<","<< path.at(i).labely<<","<<path.at(i).labelz<< endl;
    }
}
bool path_exists(vector<vector<vector<int>>> &space, Vertex A_, Vertex B_)
{
    int x0 = A_.labelx;
    int y0 = A_.labely;
    int z0 = A_.labelz;
    int x1 = B_.labelx;
    int y1 = B_.labely;
    int z1 = B_.labelz;
    int distx, disty, distz;
    distx = x1 - x0;
    disty = y1 - y0;
    distz = z1 - z0;

    double normal = sqrt((pow(distx, 2) + pow(disty, 2) + pow(distz, 2)));
    double normx = (distx / normal);
    double normy = (disty / normal);
    double normz = (distz / normal);
    int delta = 2;
    double magnitude_X = x0 + (normx * delta);

    double magnitude_Y = y0 + (normy * delta);

    double magnitude_z = z0 + (normz * delta);

    int ans = ceil(distance(x0, y0, z0, magnitude_X, magnitude_Y, magnitude_z));
    int ans2 = ceil(distance(x0, y0, z0, x1, y1, z1));

    while (ans < ans2)
    {
        if (space.at(magnitude_X).at(magnitude_Y).at(magnitude_z) == -1)
        {
            return false;
        }
        delta = delta + 2;
        magnitude_X = x0 + (normx * delta);
        magnitude_Y = y0 + (normy * delta);
        magnitude_z = z0 + (normz * delta);
        ans = ceil(distance(x0, y0, z0, magnitude_X, magnitude_Y, magnitude_z));
    }

    return true;
}

int distance(int x, int y, int z, int x2, int y2, int z2)
{
    return ceil(sqrt(pow((x2 - x), 2) + pow((y2 - y), 2) + pow((z2 - z), 2)));
}
