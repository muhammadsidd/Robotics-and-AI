#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <queue>
#include <vector>
using namespace std;

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

    int cspace[xupper - xlower][yupper - ylower][zupper - zlower];
    int startpoint = cspace[startx][starty][startz];
    int goal = cspace[goalx][goaly][goalz];
    int obsticle1 = cspace[obs1x][obs1y][obs1z];
    int r;
    int c;
    int h;
    int dr[26] = {-1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1};
    int dc[26] = {0, 0, -1, -1, -1, 1, 1, 1, 0, 0, 0, -1, -1, -1, 1, 1, 1, 0, 0, 0, -1 - 1 - 1, 1, 1, 1};
    int dh[26] = {0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    bool reach_end = false;
    cspace[goalx][goaly][goalz] = 2;

    for (int i = (obs1x - ((edge1 / 2) + 1)); i < ((edge1 / 2) + 1) + (obs1x); i++)
    {
        for (int j = (obs1y - ((edge1 / 2) + 1)); j < ((edge1 / 2) + 1) + obs1y; j++)
        {
            for (int k = (obs1z - ((edge1 / 2) + 1)); k < ((edge1 / 2) + 1) + obs1z; k++)
            {

                cspace[i][j][k] = -1;
            }
        }
    }

    for (int i = (obs2x - ((edge1 / 2) + 1)); i < ((edge2 / 2)+1) + obs2x; i++)
    {
        for (int j = ((obs2y) - ((edge2 / 2) + 1)); j < ((edge2 / 2)+1) + obs2x; j++)
        {
            for (int k = (obs2z - ((edge2 / 2) + 1)); k < ((edge2 / 2)+1) + (obs2z); k++)
            {

                cspace[i][j][k] = -1;
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
                    cspace[i][j][k] = -1;
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
                    cspace[i][j][k] = -1;
                }
            }
        }
    }
    cout << "Creating a file 'populatingWorld.txt' with obsticles please wait " << endl;
    ofstream myfile1;
    myfile1.open("populatingWorld.txt");
    for (int a = xlower; a < xupper - 1; a++)
    {
        for (int b = ylower; b < yupper - 1; b++)
        {
            for (int c = zlower; c < zupper - 1; c++)
            {
                myfile1 << cspace[a][b][c] << "  ";
            }
        }
    }
    myfile1.close();
    queue<int> rq;
    queue<int> cq;
    queue<int> hq;
    int rr;
    int cc;
    int hh;
    rq.push(goalx);
    cq.push(goaly);
    hq.push(goalz);
    cout << "generating a wavefront file to avoid obsticles in 'wavefront.txt' " << endl;
    ofstream myfile2;
    myfile2.open("wavefront.txt");
    bool visited = true;
    while (rq.size() > 0)
    {
        r = rq.front();
        rq.pop();
        c = cq.front();
        cq.pop();
        h = hq.front();
        hq.pop();

        for (int i = 0; i < 27; i++)
        {
            rr = r + dr[i];
            cc = c + dc[i];
            hh = h + dh[i];

            if (rr < 0 || cc < 0 || hh < 0)
            {
                continue;
            }
            else if (rr >= xupper || cc >= yupper || hh >= zupper)
            {
                continue;
            }
            else if (cspace[rr][cc][hh] != 0 || cspace[rr][cc][hh] == -1)
            {
                continue;
            }
            else
            {
                cspace[rr][cc][hh] = cspace[r][c][h] + 1;

                rq.push(rr);
                cq.push(cc);
                hq.push(hh);
            }
        }
    }
    for (int a = xlower; a < xupper - 1; a++)
    {
        for (int b = ylower; b < yupper - 1; b++)
        {
            for (int c = zlower; c < zupper - 1; c++)
            {
                myfile2 << cspace[a][b][c] << " ";
            }
        }
        myfile2 << endl;
    }
    myfile2.close();

    cout << "writing to file the 'segment.txt'. please wait..." << endl;
    ofstream myfile;
    myfile.open("segment.txt");
    myfile << startx<<","<<starty<<","<<startz<<endl;
    rq.push(startx);
    cq.push(starty);
    hq.push(startz);
    int smallest;
    cout<<startx<<starty<<startz;
    
    while (rq.size() > 0)
    {

        r = rq.front();
        rq.pop();
        c = cq.front();
        cq.pop();
        h = hq.front();
        hq.pop();
        smallest = cspace[r][c][h];
        for (int i = 0; i < 27; i++)
        {
            rr = r + dr[i];
            cc = c + dc[i];
            hh = h + dh[i];

            if (rr < 0 || cc < 0 || hh < 0)
            {
                continue;
            }
            else if (rr >= xupper || cc >= yupper || hh >= zupper)
            {
                continue;
            }
            else if (cspace[rr][cc][hh] == -1)
            {
                continue;
            }
            else if (smallest > cspace[rr][cc][hh] && rr <goalx && cc<goaly && hh< goaly  )
            {   
                rq.push(rr);
                cq.push(cc);
                hq.push(hh);
                myfile << rr << "," << cc << "," << hh << endl;
                break;
            }
            
        }
        /*if (rr == goalx && cc == goaly && hh == goalz){
            myfile << rr << "," << cc << "," << hh << endl;
        }*/
    }
    myfile << goalx << "," << goaly << "," << goalz << endl;
    myfile.close();
}