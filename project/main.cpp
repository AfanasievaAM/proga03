#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include<sstream>
#include<curl/curl.h>
#include "histogramm.h"
#include "svg.h"
#include <windows.h>
using namespace std;
const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;


vector<double> input_numbers(size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }
    return result;
}

void make_histogram(const vector<double>& numbers, double max, double min, size_t bin_count, vector <size_t>& bins )
{

    for(double x: numbers)
    {
        size_t bin_index=(x-min)/(max-min)*bin_count;
        if (bin_index==bin_count)
        {
            bin_index--;
        }
        bins[bin_index]++;
    }
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
   printf("Decimal version %u\n", GetVersion()); // десятиричная система
    printf("Hexadecimal version %x\n", GetVersion());// шестнадцатиричная система
    DWORD info = GetVersion();
    DWORD mask = 0x0000ffff;
    DWORD version = info & mask; //побитовое и или логичесоке умножение
    printf("version %u.\n", version);

    DWORD platform = info >> 16;
    DWORD mask_minor = 0x000000ff;
    DWORD mask_major = 0x0000ff00;
    DWORD version_minor = info & mask_minor;
    printf("version minor %u.\n", version_minor);

    DWORD version_major1 = info & mask_major;
    DWORD version_major = version_major1>>8;
    printf("version major %u.\n",version_major);

    if ((info & 0b10000000'00000000'0000000'00000000) == 0) {
    DWORD build = platform;
    printf("build %u.\n",build);
}

    /*size_t number_count;
    cerr << "Enter number count:";
    cin >> number_count;
    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cerr << "Enter bin count:";
    cin >> bin_count;
    vector <size_t> bins(bin_count, 0);
    double left;
    double baseline;

    double min, max;
    find_minmax(numbers, min, max);
    make_histogram ( numbers, max, min, bin_count, bins );
    show_histogram_svg(bins);
*/
    return 0;
}
