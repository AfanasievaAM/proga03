#include "../project/histogramm.h"
#include "../project/svg.h"
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
    assert(color_bins(bins, 30, bins[0])=="444");
    assert(color_bins(bins, 30, bins[1])=="999");
    assert(color_bins(bins, 30, bins[2])=="333");
    assert(color_bins(bins, 30, bins[3])=="111");
    assert(color_bins(bins, 30, bins[4])=="333");
}

void test6()
{
    vector <size_t> bins={5,10,15};
    assert(color_bins({}, 15, bins[0])=="000");
    assert(color_bins({}, 15, bins[1])=="000");
    assert(color_bins({}, 15, bins[2])=="000");
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
