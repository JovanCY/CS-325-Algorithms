#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
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
    vector<int> input;

    for (int i = 0; i < 10; i++)
    {
        int n = (i + 1) * 5000;
        
        for (int j = 0; j < n; j++)
        {
            input.push_back(rand() % n);
        }

        auto timeStart = chrono::high_resolution_clock::now();
        insertionSort(input);
        auto timeStop = chrono::high_resolution_clock::now();

        auto duration = chrono::duration_cast<chrono::microseconds>(timeStop - timeStart);

        cout << "n = " << n << "        duration = " << duration.count() << " ms" << endl;
    }
}