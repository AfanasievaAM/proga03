#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream> /*����������, ���������� �� ���� � ����� �����*/
#include "svg.h"

using namespace std;

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

size_t find_max(const vector<size_t>& bins)/*���������� ������������ ����� ������� */
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

size_t find_min(const vector<size_t>& bins)/*���������� ����������� ����� ������� */
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

string color_bins(const vector<size_t>& bins, size_t max_count, size_t bin) /*�������, �������� ������������ �������*/
{
    ostringstream tipe; /*���������� ��� ������ � �����*/
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
        a =10 - (bin * 9) / max_count; /*���������� ��� ������� ����� i-�� ������� bins[i]*/
    }
    tipe << a; /*���������� ������ a */
    string colors = tipe.str(); /*���������� � ������������ � ������ colors*/
    colors = colors + colors + colors;
    return colors;
}

void show_histogram_svg(const vector<size_t>& bins)
{
    const auto IMAGE_WIDTH = 400;
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
    svg_end();
}
