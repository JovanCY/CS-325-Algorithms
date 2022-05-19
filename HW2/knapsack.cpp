#include <iostream>
#include <time.h>
#include <chrono>

using namespace std;

int max(int a, int b)
{
    if (a >= b)
        return a;
    else
        return b;
}

int knapsackRecursive(int price_array[], int weightAr[], int weight, int number)
{ // weight = sack capacity, number = number of items

    if (number == 0 || weight == 0)
    {
        return 0;
    }

    if (weightAr[number] > weight)
    {

        return knapsackRecursive(price_array, weightAr, weight, number - 1);
    }
    else
    {
        int price_value = (price_array[number]);
        int wight_number = weightAr[number];
        int knapsackRecursive_value_1st = knapsackRecursive(price_array, weightAr, (weight - weightAr[number]), number - 1);
        int knapsackRescursive_value_2nd = knapsackRecursive(price_array, weightAr, weight, (number - 1));
        return max(price_value + knapsackRecursive_value_1st, knapsackRescursive_value_2nd);
    }
}

int knapsackDP(int priceAr[], int weightAr[], int maxWeight, int numberItems)
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
            int a = priceAr[i] + value[i - 1][w - weightAr[i]]; // current price + value of current weight-weight of item
            if ((w - weightAr[i]) < 0)
                a = 0;
            int b = value[i - 1][w]; // take the one above

            if (weightAr[i] <= maxWeight)
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

int main()
{

    int max_weight = 100;

    int n = 5;

    int tempMaxRec;

    for (int j = 1; j <= 8; j++)
    {
        n = 20;
        max_weight = 10 * j;

        // price and weight would change in size as n grows
        int price[n + 1];
        int weight[n + 1];

        // first slot to be 0
        //  price[0] = 0;
        //  weight[0] = 0;

        // initialize items
        for (int i = 0; i < n + 1; i++)
        {
            price[i] = rand() % (max_weight / 3);
            weight[i] = rand() % (max_weight / 10);
        }

        // running algorithms and measuring time
        auto timeStartrec = chrono::high_resolution_clock::now();
        int recResult = knapsackRecursive(price, weight, max_weight, n);
        auto timeEndrec = chrono::high_resolution_clock::now();

        auto durationRec = chrono::duration_cast<chrono::microseconds>(timeEndrec - timeStartrec);

        auto timeStartDP = chrono::high_resolution_clock::now();
        int dpResult = knapsackDP(price, weight, max_weight, n);
        auto timeEndDP = chrono::high_resolution_clock::now();

        auto durationDP = chrono::duration_cast<chrono::microseconds>(timeEndDP - timeStartDP);

        // outputs
        cout << "n = " << n;
        cout << " W = " << max_weight;

        cout << " Rec Time = " << durationRec.count() << " ms";
        cout << " DP Time = " << durationDP.count() << " ms";

        cout << " Max Rec = " << recResult;
        cout << " Max DP = " << dpResult << endl;
    }

    for (int j = 1; j <= 8; j++)
    {
        n = 4 * j;

        // price and weight would change in size as n grows
        int price[n + 1];
        int weight[n + 1];

        // first slot to be 0
        price[0] = 0;
        weight[0] = 0;

        // initialize items
        for (int i = 1; i < n + 1; i++)
        {
            price[i] = rand() % (max_weight / 3);
            weight[i] = rand() % (max_weight / 10);
        }

        // running algorithms and measuring time
        auto timeStartrec = chrono::high_resolution_clock::now();
        int recResult = knapsackRecursive(price, weight, max_weight, n);
        auto timeEndrec = chrono::high_resolution_clock::now();

        auto durationRec = chrono::duration_cast<chrono::microseconds>(timeEndrec - timeStartrec);

        auto timeStartDP = chrono::high_resolution_clock::now();
        int dpResult = knapsackDP(price, weight, max_weight, n);
        auto timeEndDP = chrono::high_resolution_clock::now();

        auto durationDP = chrono::duration_cast<chrono::microseconds>(timeEndDP - timeStartDP);

        // outputs
        cout << "n = " << n;
        cout << " W = " << max_weight;

        cout << " Rec Time = " << durationRec.count() << " ms";
        cout << " DP Time = " << durationDP.count() << " ms";

        cout << " Max Rec = " << recResult;
        cout << " Max DP = " << dpResult << endl;
    }

    return 0;
}