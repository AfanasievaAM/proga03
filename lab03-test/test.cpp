#include "histogramm.h"
#include <cassert>
#include <string.h>

void test_positive()
{
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}
void test1()
{
    double min = 0;
    double max = 0;
    find_minmax({-5, -8, -10}, min, max);
    assert(min == -10);
    assert(max == -5);
}

void test2()
{
    double min = 0;
    double max = 0;
    find_minmax({5, 5, 5}, min, max);
    assert(min == 5);
    assert(max == 5);
}

void test3()
{
    double min = 0;
    double max = 0;
    find_minmax({6}, min, max);
    assert(min == 6);
    assert(max == 6);
}

void test4()
{
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min == 0);
    assert(max == 0);
}
void test5()
{
    vector <size_t> bins={20,5,25,30,24};
    assert(color_bins(bins, 15, bin[0])=="111");
    assert(color_bins(bins, 15, bin[1])=="555");
    assert(color_bins(bins, 15, bin[2])=="444");
    assert(color_bins(bins, 15, bin[3])=="999");
    assert(color_bins(bins, 15, bin[4])=="666");
}

void test6()
{
    vector <size_t> bins={5,10,15};
    assert(color_bins(0, 5, bin[0])=="999");
    assert(color_bins(0, 5, bin[1])=="111");
    assert(color_bins(0, 5, bin[2])=="555");
}

int main()
{
    test_positive();
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
}
