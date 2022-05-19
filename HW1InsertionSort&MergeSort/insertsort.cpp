#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

void parse(std::string const &str, const char delim,
           std::vector<int> &out)
{ //retrieved from https://www.techiedelight.com/split-string-cpp-using-delimiter/, with some modifications
    // construct a stream from the string
    stringstream ss(str);

    std::string s;

    while (std::getline(ss, s, delim))
    {
        out.push_back(stoi(s));
    }
}

void convertFromString(vector<string> &in, vector<int> &out)
{
    int size;
    size = in.size();
    for (int i = 0; i < size; i++)
    {
        out[i] = stoi(in[i]);
    }
}

void vSwap(vector<int> &vec, int x, int y)
{
    int temp;
    temp = vec[x];
    vec[x] = vec[y];
    vec[y] = temp;
}

void insertionSort(vector<int> &input)
{
    for (int i = 0; i < ((input.size())); i++)
    { // i is the key
        int key = input[i];
        int search = i - 1;
        while (search >= 0 && input[search] > key)
        {
            input[search + 1] = input[search];
            search--;
        }
        input[search + 1] = key;
    }
}

void displayVector(vector<int> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }
}


int main()
{

    string x;
    vector<int> input;

    fstream data;
    data.open("data.txt");

    for (int i = 0; i < 7; i++)
    {
        getline(data, x);
        // data.close();
        parse(x, ' ', input); //converting text file to int vector
        input.erase(input.begin());

        vector<int> output;
        vector<int>::iterator point;

        point = input.begin();
        // point = point+2;
        // input.insert(point,1);

        insertionSort(input);

        displayVector(input);

        cout << endl;

        input.clear();
    }
}