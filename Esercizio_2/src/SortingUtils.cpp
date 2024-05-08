#include "SortingUtils.hpp"
#include "iostream"
#include <chrono>
#include <random>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include "SortingAlgorithm.hpp"
#include <cstdlib>

using namespace std;



template <typename T>
void RandomVector(vector<T>& v,
                  unsigned int& size,
                  unsigned int& mode)
{
    //random vector
    if (mode == 1)
    {
        cout << "Randomly generated vector" << endl;
        if (typeid(v[0]) == typeid(int))
            for (unsigned int i = 0; i < size; i++)
                v[i] = std::rand()%size;

        else if (typeid(v[0]) == typeid(double))
        {
            uniform_real_distribution<double> unif(0.0, double(size));
            default_random_engine re;
            for (unsigned int i = 0; i < size; i++)
            {
                v[i] = unif(re);
            }
        }
    }

    //decreasing order
    else if (mode == 2)
    {
        cout << "Decreasing order vector" << endl;
        T n = size;
        generate(v.begin(), v.end(), [&n] () {return n--;});
    }

    //already ordered
    else if (mode == 3)
    {
        cout << "Already ordered vector" << endl;
        T n = 0;
        generate(v.begin(), v.end(), [&n] () {return n++;});
    }
}

template <typename T>
void SortCompare(vector<T> v)
{
    vector<T> v1 = v;
    vector<T> v2 = v;
    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    SortLibrary::MergeSort(v1);
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    SortLibrary::BubbleSort(v2);
    std::chrono::steady_clock::time_point t3 = std::chrono::steady_clock::now();
    double duration_MergeSort = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    cout << "MergeSort duration: " << duration_MergeSort << endl;
    double duration_BubbleSort = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count();
    cout << "BubbleSort duration: " << duration_BubbleSort << endl;

    //comparing durations
    if (duration_MergeSort < duration_BubbleSort)
        cout << "MergeSort faster than BubbleSort" << endl;
    else if (duration_MergeSort > duration_BubbleSort)
        cout << "BubbleSort faster than MergeSort" << endl;
    else
        cout << "Same duration" << endl;
}
