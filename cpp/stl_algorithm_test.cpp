#include <cassert>
#include <cmath>

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>   // std::stringstream
#include <execution> //std::execution::par

using namespace std;

// min_element一样
void TEST_max_element()
{
    vector<int> v{3, -1, 2, -100, -20, -20, -20};

    auto res1 = max_element(v.begin(), v.end());
    auto pos1 = distance(v.begin(), res1);
    assert(pos1 == 0);

    auto res2 = max_element(v.begin(), v.end(), [](int lhs, int rhs)
                            { return (abs(lhs) < abs(rhs)); });
    auto pos2 = distance(v.begin(), res2);
    assert(pos2 == 3);
}

void TEST_for_each()
{
    vector<int> v{3, -1, 2, -100, -20, -20, -20};

    for_each(v.begin(), v.end(), [](int i) {});
}

void TEST_find()
{
    vector<int> v{3, -1, 2, -100, -20, -20, -20};

    auto res1 = find(v.begin(), v.end(), -20);
    auto pos1 = distance(v.begin(), res1);
    assert(pos1 == 4);

    auto res2 = find_if(v.begin(), v.end(), [](int i)
                        { return i < -50; });
    auto pos2 = distance(v.begin(), res2);
    assert(pos2 == 3);
}
void TEST_count()
{
    vector<int> v{3, -1, 2, -100, -20, -20, -20};

    auto res1 = count(v.begin(), v.end(), -20);
    // -20 出现 3 次
    assert(res1 == 3);

    auto res2 = count_if(v.begin(), v.end(), [](int i)
                         { return i < 0; });
    // 小于 0 的有 5 个
    assert(res2 == 5);
}
void TEST_remove()
{
    std::string str1 = "kid;and;u70b3;and;lbs";
    str1.erase(std::remove(str1.begin(), str1.end(), ';'),
               str1.end());
    assert(str1 == string("kidandu70b3andlbs"));

    std::string str2 = "kid\n and\u70b3 \t  and\n\nlbs";
    str2.erase(std::remove_if(str2.begin(),
                              str2.end(),
                              [](unsigned char x)
                              { return std::isspace(x); }),
               str2.end());
    assert(str1 == string("kidandu70b3andlbs"));
}
void TEST_copy()
{
    // copy
    // copy_n
    // copy_if
}

void TEST_split()
{
    string line = "kid and u70b3 and lbs";

    // Vector of string to save tokens
    vector<string> tokens;

    // stringstream class check1
    stringstream check1(line);

    string intermediate;

    // Tokenizing w.r.t. space ' '
    while (getline(check1, intermediate, ' '))
    {
        tokens.push_back(intermediate);
    }

    // Printing the token vector
    // for (int i = 0; i < tokens.size(); i++)
    //     cout << tokens[i] << '\n';
    assert(tokens[2] == string("u70b3"));
}

void TEST_parallel()
{
    vector<int> longVector;
    for (size_t i = 0; i < 1e6; i++)
    {
        longVector.push_back(i);
    }
    // Find element using parallel execution policy
    auto result1 = find(execution::par, begin(longVector), end(longVector), 2333);
    // Sort elements using sequential execution policy
    sort(execution::seq, begin(longVector), end(longVector));
}

void TEST_topk()
{
    vector<int> v{3, -1, 2, -100, -20, -20, -20};

    // 3th partation, abs
    std::nth_element(v.begin(), v.begin() + 3, v.end(), [](int lhs, int rhs)
                     { return std::abs(lhs) < std::abs(rhs); });
    assert(v[2] == 3);
}

void TEST_permutation()
{
    std::string str = "acdbe";
    sort(str.begin(), str.end());
    vector<string> res;
    do
    {
        res.push_back(str);
    } while (next_permutation(str.begin(), str.end()));
    assert(res[1] == string("abced"));
    assert(res.back() == string("edcba"));
}

void TEST_all()
{
    TEST_max_element();
    TEST_for_each();
    TEST_find();
    TEST_count();
    TEST_remove();
    TEST_copy();
    TEST_split();
    TEST_parallel();
    TEST_topk();
    TEST_permutation();
}

int main()
{
    TEST_all();
    cout << "all test cases passed!" << endl;
};

// g++ stl_algorithm_test.cpp -std=c++17 -o test && ./test && rm ./test
