// 测试使用
#include <iostream>
#include <sstream>
#include <string>

#include "lru.h"

using namespace std;

int main()
{
    auto lru = LRUCache<string, int>::getInstance();
    for (int i = 0; i < 100000; i++)
    {
        string s = to_string(i);
        lru->set(s, i);
    }
    for (int i = 0; i < 100000; i++)
    {
        string s = to_string(i);
        if (lru->exist(s))
        {
            cout << "|key|" << s << "|val|" << lru->get(s) << endl;
        }
    }
    return 0;
}
// g++ lru_test.cpp -std=c++17 -o test && ./test && rm ./test
