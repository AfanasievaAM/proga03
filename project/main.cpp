#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <string>
#include "histogramm.h"
#include "svg.h"
#include <curl/curl.h>

using namespace std;
const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;


vector<double>
input_numbers(istream& in, size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
    return result;
}

Input
read_input(istream& in, bool prompt )
{
    Input data;
    size_t number_count;

    if (prompt)
    {
        cerr << "Enter number count: ";
        in >> number_count;

        cerr << "Enter numbers: ";
        data.numbers = input_numbers(in, number_count);

        cerr << "Enter bin count: ";
        in >> data.bin_count;
    }
    else
    {
        in >> number_count;
        data.numbers = input_numbers(in, number_count);
        in >> data.bin_count;
    }
    return data;
}

size_t
write_data(void* items, size_t item_size, size_t item_count, void* ctx) {
    const size_t data_size = item_size * item_count;
    const char* new_items = reinterpret_cast<const char*>(items);
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write(new_items, data_size);
    return data_size;
}

Input
download(const string& address) {
    stringstream buffer;
curl_global_init(CURL_GLOBAL_ALL);
 CURL *curl = curl_easy_init();
 if(curl)
    {
CURLcode res;
curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
 res = curl_easy_perform(curl);
  if (res != CURLE_OK)
  {
     cout << curl_easy_strerror(res) << endl;
     exit(1);
  }
  curl_easy_cleanup(curl);
  }
 return read_input(buffer, false);
 }
vector<size_t> make_histogram(const Input& data)
{
    vector<size_t> result(data.bin_count,0);
    double min=0;
    double max=0;
    find_minmax(data.numbers, min, max);
    for (double number : data.numbers)
    {
        size_t bin = (size_t)((number - min) / (max - min) * data.bin_count);
        if (bin == data.bin_count)
        {
            bin--;
        }
        result[bin]++;
    }
    return result;
}

void show_histogram_text(vector <size_t> bins)
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

int
main(int argc, char* argv[])
{
    Input input;
    char* format;
    int poz;

    for (int i=0; i< argc; i++)
    {
        if (strcmp(argv[i], "-format")==0)
        {
            if (i!=argc-1)
            {
                format = argv[i+1];
            }
            poz=i+1;
            break;
        }
    }
    if (((strcmp(format, "text")!=0)&&(strcmp(format, "svg")!=0)) ||(poz==argc)) /*Если после format нет txt или svg, то подсказка*/
    {
        cout << "Необходимо ввести 'format text' или 'format svg'";
        exit(1);
    }
    if (argc > 1)
      {

    if (poz==2)

    {
        input = download(argv[3]);
    }
    else
    {
        input = download(argv[1]);
    }
}
    else
    {
        input = read_input(cin, true);
    }
    const auto bins = make_histogram(input);
    if (strcmp(format,"text")==0)
    {
    show_histogram_text(bins);
    }
    else
    {
    show_histogram_svg(bins);
    }
    return 0;
}
