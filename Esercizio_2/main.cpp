#include <iostream>
#include <chrono>
#include <unistd.h>
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>
#include "SortingAlgorithm.hpp"

using namespace std;


template <typename T>
void CreateVector(vector<T>& v,
                  unsigned int& dimension,
                  unsigned int& mode)
{
    //random vector
    if (mode == 1)
    {
        if (typeid(v[0]) == typeid(int))
            for (unsigned int k = 0; k < dimension; k++)
                v[k] = std::rand()%3001;

        else if (typeid(v[0]) == typeid(double))
        {
            uniform_real_distribution<double> unif(0., 300.);
            default_random_engine re;
            for (unsigned int k = 0; k < dimension; k++)
            {
                v[k] = unif(re);
            }
        }
    }

    //decreasing order
    else if (mode == 2)
    {
        T n = dimension;
        generate(v.begin(), v.end(), [&n] () {return n--;});
    }

    //already ordered
    else if (mode == 3)
    {
        T n = 0;
        generate(v.begin(), v.end(), [&n] () {return n++;});
    }
}

template <typename T>
void SortCompare(vector<T> v, unsigned int& sumMerge, unsigned int& sumBubble)
{
    vector<T> v1 = v;
    vector<T> v2 = v;
    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    SortLibrary::MergeSort(v1);
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    SortLibrary::BubbleSort(v2);
    std::chrono::steady_clock::time_point t3 = std::chrono::steady_clock::now();


    unsigned int duration_MergeSort = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    //cout << "MergeSort duration: " << duration_MergeSort << endl;
    sumMerge += duration_MergeSort;

    unsigned int duration_BubbleSort = std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2).count();
    //cout << "BubbleSort duration: " << duration_BubbleSort << endl;
    sumBubble += duration_BubbleSort;
}

int main(int argc, char *argv[])
//int main()
{
    unsigned int iter = 15;
    unsigned int sumMerge = 0;
    unsigned int sumBubble = 0;
    unsigned int dimension = 0;

    for (int i = 1; i < argc; i++)
    {
        dimension = stoi(argv[i]);
        cout << "************************************************" << endl;
        cout << "* Vector dimension: " << dimension << endl;
        cout << "************************************************" << endl;
        for (unsigned int mode = 1; mode < 4; mode++)
        {
            if (mode == 1)
                cout << "Randomly generated vectors\n" << endl;
            else if (mode == 2)
                cout << "Decreasing order vectors\n" << endl;
            else
                cout << "Already ordered vectors\n" << endl;


            sumMerge = 0;
            sumBubble = 0;


            cout << "Integer vector\n" << endl;
            vector<int> vInt(dimension);
            if (mode == 1)
            {
                for (unsigned int j = 0; j < iter; j++)
                {
                    CreateVector(vInt, dimension, mode);
                    SortCompare(vInt, sumMerge, sumBubble);
                }
                sumMerge = sumMerge/iter;
                sumBubble = sumBubble/iter;
                cout << "Average computed on " << iter << " randomic vectors" << endl;
            }
            else
            {
                CreateVector(vInt, dimension, mode);
                SortCompare(vInt, sumMerge, sumBubble);
            }
            cout << "Duration Mergesort: " << sumMerge << " microseconds" << endl;
            cout << "Duration Bubblesort: " << sumBubble << " microseconds" << endl;
            //comparing durations
            if (sumMerge < sumBubble)
                cout << "MergeSort faster than BubbleSort\n" << endl;
            else if (sumMerge > sumBubble)
                cout << "BubbleSort faster than MergeSort\n" << endl;
            else
                cout << "Same duration\n" << endl;


            cout << "Double vector\n" << endl;
            vector<double> vDouble(dimension);
            if (mode == 1)
            {
                for (unsigned int j = 0; j < iter; j++)
                {
                    CreateVector(vDouble, dimension, mode);
                    SortCompare(vDouble, sumMerge, sumBubble);
                }
                sumMerge = sumMerge/iter;
                sumBubble = sumBubble/iter;
                cout << "Average computed on " << iter << " randomic vectors" << endl;
            }
            else
            {
                CreateVector(vDouble, dimension, mode);
                SortCompare(vInt, sumMerge, sumBubble);
            }
            cout << "Duration Mergesort: " << sumMerge << " microseconds" << endl;
            cout << "Duration Bubblesort: " << sumBubble << " microseconds" << endl;
            //comparing durations
            if (sumMerge < sumBubble)
                cout << "MergeSort faster than BubbleSort\n" << endl;
            else if (sumMerge > sumBubble)
                cout << "BubbleSort faster than MergeSort\n" << endl;
            else
                cout << "Same duration\n" << endl;

            cout << "-----------------------------------------------" << endl;
        }
    }
    return 0;
}

