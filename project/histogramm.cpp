#include "histogramm.h"
using namespace std;

void find_minmax(const vector<double>& numbers, double& min, double& max)
{
    if (numbers.size()>0)
    {
    min = numbers[0];
    max = numbers[0];

    for(double x: numbers)
    {
        if(min>x)
            min=x;
        if(max<x)
            max=x;
    }
    }
}
