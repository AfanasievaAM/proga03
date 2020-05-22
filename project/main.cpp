#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include "histogramm.h"
#include "svg.h"

using namespace std;
const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

struct Input {
    vector<double> numbers;
    size_t bin_count;
};


vector<double>
input_numbers(istream& in, size_t count) {
   vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
}

Input
read_input(istream& in) {
    Input data;

    cerr << "Enter number count: ";
    size_t number_count;
    cin >> number_count;

    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    cerr << "Enter bin count: ";
    cin >> data.bin_count;

    return data;
}

vector<size_t> make_histogram(const vector<double>& numbers, const size_t count )
{
    vector<size_t> result(count);
    double min;
    double max;
   find_minmax(numbers, min, max);
    for (double number : numbers) {
        size_t bin = (size_t)((number - min) / (max - min) * count);
        if (bin == count) {
            bin--;
        }
        result[bin]++;
    }
    return result;
}

void show_histogram_text(vector <size_t>& bins)
{
    size_t max_bin = bins[0];
    for (size_t bin:bins)
    {
        if (bin > max_bin)
        {
            max_bin=bin;
        }
    }
    if (max_bin > MAX_ASTERISK)
    {
        double factor = MAX_ASTERISK/static_cast<double>(max_bin);
        for (size_t bin:bins)
        {
            if (bin <100)
            {
                cout <<" ";
                if (bin < 10)
                {
                    cout <<" ";
                }
            }
            cout <<bin <<"|";
            size_t height = bin*factor;
            for(int i=0; i<height; i++)
            {
                cout<< "*";
            }
            cout<<endl;
        }
    }

    else
    {
        for (size_t bin:bins)
        {
            if (bin <100)
            {
                cout <<" ";
                if (bin < 10)
                {
                    cout <<" ";
                }
            }
            cout <<bin <<"|";
            for (int i = 0; i < bin; i++)
            {
                cout << "*";
            }
            cout<<endl;
        }
    }
}

int main()
{
    size_t number_count;
    cerr << "Enter number count:";
    cin >> number_count;
    Input data = read_input(cin);
    const auto numbers = input_numbers(cin, number_count);

    size_t bin_count;
    cerr << "Enter bin count:";
    cin >> bin_count;

    const auto bins = make_histogram(numbers, bin_count);
    show_histogram_svg(bins);

    return 0;
}
