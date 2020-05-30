#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream> /*библиотека, отвечающа€ за ввод и вывод строк*/
#include "svg.h"
#include <windows.h>

using namespace std;

string print_name ()
{
stringstream buffer;
    DWORD info = GetVersion();
    DWORD mask = 0x0000ffff;
    DWORD version = info & mask;

    DWORD platform = info >> 16;
    DWORD mask_minor = 0x000000ff;
    DWORD mask_major = 0x0000ff00;
    DWORD version_minor = info & mask_minor;

    DWORD version_major1 = info & mask_major;
    DWORD version_major = version_major1>>8;

    if ((info & 0b10000000'00000000'0000000'00000000) == 0)
        {
    DWORD build = platform;
    buffer << "Windows v" << version_minor << "." << version_major << " (build" << build << ")\n";
}
char system [MAX_COMPUTERNAME_LENGTH + 1];
DWORD Size =sizeof (system);
 GetComputerNameA(system, &Size);
  buffer << "Name of computer"<<system<<"\n";
 return buffer.str();
}

void svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end()
{
    cout << "</svg>\n";
}

void svg_text(double left, double baseline, size_t text)
{
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text <<"</text>";
}

void svg_rect(double x, double y, double width, double height, string stroke, string fill)
{
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "' />";
}

size_t find_max(const vector<size_t>& bins)/*определ€ем максимальную длину столбца */
{
    size_t max = bins[0];
    for (const auto& bin : bins)
    {
        if (bin > max)
        {
            max = bin;
        }
    }
    return max;
}

size_t find_min(const vector<size_t>& bins)/*определ€ем минимальную длину столбца */
{
    size_t min = bins[0];
    for (const auto& bin : bins)
    {
        if (bin < min)
        {
            min = bin;
        }
    }
    return min;
}

string color_bins(const vector<size_t>& bins, size_t max_count, size_t bin) /*функци€, мен€юща€ насыщенность заливки*/
{
    ostringstream tipe; /*используем дл€ записи в стоку*/
    size_t a;
    size_t min = find_min(bins);
    size_t max = find_max(bins);
    if (bin == min)
    {
        a = 9;
    }
    else if (bin == max)
    {
        a = 1;
    }
    else
    {
        a =10 - (bin * 9) / max_count; /*используем дл€ расчета цвета i-го столбца bins[i]*/
    }
    tipe << a; /*содержимое строки a */
    string colors = tipe.str(); /*содержимое а записываетс€ в строку colors*/
    colors = colors + colors + colors;
    return colors;
}

void show_histogram_svg(const vector<size_t>& bins)
{
    const auto IMAGE_WIDTH = 500;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    const size_t MAX_ASTERISK = IMAGE_WIDTH - TEXT_LEFT - TEXT_WIDTH;
    size_t max_count = 0;
    for (size_t b : bins)
        {
        if (b > max_count)
        {
            max_count = b;
        }
    }
    const bool need_scaling = max_count * BLOCK_WIDTH > MAX_ASTERISK;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    for (size_t bin : bins)
        {
        string colors = color_bins(bins, max_count, bin);
        cout << colors << endl;
        size_t height = bin;
        if (need_scaling)
            {
            const double scal = (double)MAX_ASTERISK / (max_count * BLOCK_WIDTH);
            height = (size_t)(bin * scal);
        }
        const double bin_width = BLOCK_WIDTH * height;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, bin);
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT , "green", "#" + colors);
        top += BIN_HEIGHT;
    }
    cout << "<text x='" << TEXT_LEFT << "' y='" << BIN_HEIGHT+top << "'>" << print_name() <<"</text>";
    svg_end();
}
