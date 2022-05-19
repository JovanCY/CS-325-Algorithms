#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct activity
{
    int number;
    int start;
    int end;
};

void parse(std::string const &str, const char delim,
           std::vector<int> &out)
{ // retrieved from https://www.techiedelight.com/split-string-cpp-using-delimiter/, with some modifications
    // construct a stream from the string
    stringstream ss(str);

    std::string s;

    while (std::getline(ss, s, delim))
    {
        out.push_back(stoi(s));
    }
}

void greedyAct(vector<activity> actList, int n)
{
    int amount = 0;
    int result[n];

    for (int i = 0; i < n; i++)
    {
        result[i] = 0;
    }

    // last to start
    while (actList.size() > 0)
    {
        // search for highest start value
        int highestStart = 0;
        int highestNum = 0;
        int highestIndex = 0;

        for (int i = 0; i < actList.size(); i++)
        {
            if (actList.at(i).start > highestStart)
            {
                highestStart = actList.at(i).start;
                highestNum = actList.at(i).number;
                highestIndex = i;
            }
        }

        // add number to result array, add amount counter
        result[amount] = actList.at(highestIndex).number;
        amount++;

        // clear any activities that don't match
        for (int i = actList.size() - 1; i >= 0; i--)
        {
            if (actList[i].end > highestStart)
            {
                actList.erase(actList.begin() + i);
            }
        }
    }
    // print message
    cout << "Maximum number of activities = " << amount << endl;

    for (int i = amount - 1; i >= 0; i--)
    {
        cout << result[i] << " ";
    }
}

int main()
{
    string x;

    fstream data;
    data.open("act.txt");

    int set = 3;

    for (int s = 0; s < set; s++)
    {

        vector<int> input;
        cout << endl
             << "Set " << s + 1 << endl;

        getline(data, x);
        int n = stoi(x);

        vector<activity> actList;
        actList.clear();

        // input loop
        for (int i = 0; i < n; i++)
        {
            getline(data, x);
            parse(x, ' ', input);

            activity act;
            act.number = input[3 * i];
            act.start = input[3 * i + 1];
            act.end = input[3 * i + 2];

            actList.push_back(act);
        }

        greedyAct(actList, n);
    }
}