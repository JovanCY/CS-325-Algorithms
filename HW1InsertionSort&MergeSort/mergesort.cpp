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

void merge(vector<int> &vec, int start, int middle, int end)
{
    //size of left array and right array
    int left = middle - start + 1;
    int right = end - middle;

    //initialize temp arrays
    int leftAr[left];
    int rightAr[right];

    // copy vector data into temp arrays
    for (int i = 0; i < right; i++)
    {
        rightAr[i] = vec[middle + i + 1];
    }
    for (int i = 0; i < left; i++)
    {
        leftAr[i] = vec[start + i];
    }

    //index of left, right, and merged vectors
    int indexL = 0, indexR = 0, indexM = start;

    while (indexL < left && indexR < right)
    { //actual merging
        if (leftAr[indexL] < rightAr[indexR])
        {
            vec[indexM] = leftAr[indexL];
            indexL++;
        }
        else
        {
            vec[indexM] = rightAr[indexR];
            indexR++;
        }
        indexM++;
    }

    /*
    once one side's vector runs out, there might still be remaining elements in
    the other vector, therefore we need to drain the other vector of its elements
    */

    //if there are elements remaining in the let vector
    while (indexL < left)
    {
        vec[indexM] = leftAr[indexL];
        indexM++;
        indexL++;
    }

    //if there are elements remaining in the right vector
    while (indexR < right)
    {
        vec[indexM] = rightAr[indexR];
        indexM++;
        indexR++;
    }
}

void mergeSort(vector<int> &input, int start, int end)
{
    //for debugging
    // cout<< "merge sort of size"<< end-start<< " entered"<<endl;
    if (start >= end)
        return;

    int middle = (start + end) / 2;
    mergeSort(input, start, middle);
    mergeSort(input, middle + 1, end);
    merge(input, start, middle, end);
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

    // cout<<"outside loop";
    fstream data;
    data.open("data.txt");

    for (int i = 0; i < 1; i++) //to loop for multiple inputs
    {
        getline(data, x);
        // data.close();
        parse(x, ' ', input); //converting string to int vector
        input.erase(input.begin());

        displayVector(input);
        cout << endl;

        mergeSort(input, 0, input.size() - 1);

        displayVector(input);
        cout << endl;

        input.clear();
    }

    data.close();
}

// roadTrip
// {
    
//     while (index <=n)
//     {
//         bool found= false;
        
//         while (found =false)
//         {//loops and refreshes choice until distance exceeds d, therefore chooses mas distance while still being less than d
//             if (x[index]>d&&index==n+1)
//                 found = true;
//                 break;
//             else
//             {
//                 choice = index;
//                 index++;
//             }
//         }
//         print choice;
//     }
// }
