#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <math.h>
#include <cmath>

using namespace std;

void parse(std::string const &str, const char delim,
           std::vector<int> &out)
{ // retrieved from https://www.techiedelight.com/split-string-cpp-using-delimiter/, with some modifications
    // construct a stream from the string
    std::stringstream ss(str);

    std::string s;

    while (std::getline(ss, s, delim))
    {
        out.push_back(stoi(s));
    }
}

struct coor
{
    int x;
    int y;
};

int getLength(vector<coor> coordinateArray, int vertex1, int vertex2)
{
    int x1 = coordinateArray.at(vertex1).x;
    int y1 = coordinateArray.at(vertex1).y;
    int x2 = coordinateArray.at(vertex2).x;
    int y2 = coordinateArray.at(vertex2).y;

    int addx = x1 - x2;
    int squarex = addx * addx;
    int addy = y1 - y2;
    int squarey = addy * addy;

    float number = sqrt(squarex + squarey);

    int result = nearbyint(number);

    return result;
}

int main()
{
    string x;

    fstream data;
    data.open("graph.txt");

    getline(data, x);

    int testcases = stoi(x);

    for (int i = 1; i <= testcases; i++)
    {
        getline(data, x);

        vector<coor> coordinates;
        coordinates.clear();

        int vertices = stoi(x);

        // processing input
        for (int j = 0; j < vertices; j++)
        {
            vector<int> input;
            getline(data, x);

            parse(x, ' ', input);

            coor temp;

            temp.x = input[0];
            temp.y = input[1];

            coordinates.push_back(temp);

        } // end vertex

        // make adjacency matrix
        int matrix[vertices][vertices];

        for (int j = 0; j < vertices; j++)
        {
            for (int k = 0; k < vertices; k++)
            {
                matrix[j][k] = getLength(coordinates, j, k);
            }
        }

        // initialize lists
        bool discovered[vertices];
        discovered[0] = false;

        for (int j = 0; j < vertices; j++)
        {
            discovered[i] = false;
        } // mark all vertices as undiscovered

        // resulting weight of graph
        int counter = 0;

        // first lowest edge, nothing is discovered

        // look for lowest length edge while taking note which edge it is/ which vertices they are connected to
        int lowestEdge = 10000;
        int vertex1 = -1, vertex2 = -1;

        for (int k = 0; k < vertices; k++)
        {
            for (int l = 0; l < vertices; l++)
            {
                int test = matrix[k][l];

                if (matrix[k][l] < lowestEdge && matrix[k][l] != 0)
                {
                    // updates new vertices to find lowest edge, and vertices associated with it
                    lowestEdge = matrix[k][l];
                    vertex1 = k;
                    vertex2 = l;
                }
            }
        } // end search

        // add length to counter, discover edges
        counter += lowestEdge;
        discovered[vertex1] = true;
        discovered[vertex2] = true;

        // find edge loop

        // actual lowest edge loop
        for (int j = 1; j < vertices - 1; j++)
        {
            // look for lowest length edge while taking note which edge it is/ which vertices they are connected to
            int lowestEdge = 10000;
            int vertex1 = -1, vertex2 = -1;

            for (int k = 0; k < vertices; k++)
            {
                if (discovered[k] == false)
                    continue;
                for (int l = 0; l < vertices; l++)
                {
                    if (discovered[l] == true)
                        continue;

                    int test = matrix[k][l];

                    if (matrix[k][l] < lowestEdge && matrix[k][l] != 0)
                    {
                        // updates new vertices to find lowest edge, and vertices associated with it
                        lowestEdge = matrix[k][l];
                        vertex1 = k;
                        vertex2 = l;
                    }
                }
            } // end search

            // add length to counter, discover edges
            counter += lowestEdge;
            discovered[vertex1] = true;
            discovered[vertex2] = true;


        } // find edge loop

        //
        cout << "Test Case " << i << ": MST weight " << counter << endl;

    } // end testcase

    data.close();


    return 1;
}