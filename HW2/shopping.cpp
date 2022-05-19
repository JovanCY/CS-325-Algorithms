#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

int reduceAboveZero(int a, int b)
{
    int result;
    result = a - b;

    if (result < 0)
        result = 0;

    return result;
}

struct item
{
    int price;
    int weight;
    int number;

    item()
    {
        price = 0;
        weight = 0;
        number = 0;
    }
};

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

int knapsackDP(vector<item> stuff, int maxWeight, int numberItems)
{
    int value[numberItems + 1][maxWeight + 1];

    for (int w = 0; w <= maxWeight; w++)
    {
        value[0][w] = 0;
    }

    for (int i = 1; i <= numberItems; i++)
    {
        value[i][0] = 0;

        for (int w = 1; w <= maxWeight; w++)
        {
            int a = stuff[i].price + value[i - 1][reduceAboveZero(w, stuff[i].weight)]; // current price + value of current weight-weight of item
            if ((w - stuff[i].weight) < 0)
                a = 0;
            int b = value[i - 1][w]; // take the one above

            if (stuff[i].weight <= maxWeight)
            { // if this item is heavier than sack, skip

                if (a > b)
                {
                    value[i][w] = a;
                }
                else
                {
                    value[i][w] = b;
                }
            }
            else
            {
                value[i][w] = b;
            }
        }
    }

    return value[numberItems][maxWeight];
}

void printKnapsackDP(vector<item> stuff, int maxWeight, int numberItems)
{
    int value[numberItems + 1][maxWeight + 1];

    for (int w = 0; w <= maxWeight; w++)
    {
        value[0][w] = 0;
    }

    for (int i = 1; i <= numberItems; i++)
    {
        value[i][0] = 0;

        for (int w = 1; w <= maxWeight; w++)
        {
            int a = stuff[i].price + value[i - 1][reduceAboveZero(w, stuff[i].weight)]; // current price + value of current weight-weight of item
            if ((w - stuff[i].weight) < 0)
                a = 0;
            int b = value[i - 1][w]; // take the one above

            if (stuff[i].weight <= maxWeight)
            { // if this item is heavier than sack, skip

                if (a > b)
                {
                    value[i][w] = a;
                }
                else
                {
                    value[i][w] = b;
                }
            }
            else
            {
                value[i][w] = b;
            }
        }
    }

    int i = numberItems;
    int j = maxWeight;
    // after table is built,print statements
    /*acquired from https://www.youtube.com/watch?v=zRza99HPvkQ&list=PLDN4rrl48XKpZkf03iYFl-O29szjTrs_O&index=55 */

    vector<int> printSave;
    int printI = 0;

    while (i > 0 && j > 0)
    {
        if (!(value[i][j] == value[i - 1][j]) && value[i][j] != 0)
        {
            printSave.push_back(i);
            j = j - stuff[i].weight;
            i--;
            printI++;
        }
        else
            i--;
    }

    printI--;
    while (printI >= 0)
    {
        cout << printSave[printI] << " ";
        printI--;
    }
}

int main()
{
    string x; // placeholder for lines in the form of a string
    // vector<int> input; //vector to store int variables from parse()
    fstream data;
    // vector<item> itemList; //to store items
    // itemList.clear();

    data.open("shopping.txt");

    getline(data, x);
    int T = stoi(x);

    for (int testCase = 1; testCase <= T; testCase++)
    { // test case starts
        vector<item> itemList;
        cout << "Test Case " << testCase << endl;
        getline(data, x);
        int n = stoi(x); // n = number of items available to buy

        item zero;
        itemList.push_back(zero);
        for (int j = 0; j < n; j++)
        {
            // getting the input, and placing the into structures
            vector<int> input;
            item placeholder; // item: price, weight, number

            getline(data, x);
            parse(x, ' ', input);
            // input will hold the price of the item in index 0
            // and the weight in index 1

            placeholder.price = input[0];
            placeholder.weight = input[1];
            placeholder.number = j + 1;

            itemList.push_back(placeholder); // places item into an array of items
            placeholder;
        } // good

        getline(data, x); // number of people in the family

        int familySize = stoi(x);
        int familyPrice = 0;

        int memberWeight[familySize];

        for (int f = 0; f < familySize; f++)
        {                     // collecting each member weight capacity, adding to family price
            getline(data, x); // weight capacity for each family member

            memberWeight[f] = stoi(x);

            int a = knapsackDP(itemList, memberWeight[f], n); // messed up

            familyPrice += a;
        }

        cout << "Total Price " << familyPrice << endl;

        for (int f = 0; f < familySize; f++)
        {
            cout << f + 1 << ": ";
            printKnapsackDP(itemList, memberWeight[f], n);
            cout << endl;
        }

        // itemList.clear();
    }
}
