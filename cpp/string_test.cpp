#include "string.h"
#include <iostream>
#include <utility>
#include <vector>

using namespace kid;

void foo(String x) {}

void bar(const String &x) {}

String baz()
{
    String res("world");
    return res;
}
String baz1(String &&s)
{
    //The std::move function converts the lvalue other to an rvalue.
    String res = std::move(s);
    return res;
}

int main()
{
    std::cout << "==start main==" << std::endl;
    String s0;          //default-ctor
    String s1("hello"); //(const char*)-ctor
    String s2(s0);      //copy-ctor
    String s3(s1);      //copy-ctor
    s2 = s1;            //copy-ctor|copy-assignment-operator|dtor
    s3 = s3;            //copy-ctor|copy-assignment-operator|dtor
    s1 = "awesome";     //(const char*)-ctor|copy-assignment-operator|dtor

    foo(s1);             //copy-ctor|dtor
    bar(s1);             //
    foo("temp");         //(const char*)-ctor|dtor
    bar("temp");         //(const char*)-ctor|dtor
    String s4 = baz();   //(const char*)-ctor
    s4 = baz();          //(const char*)-ctor|copy-assignment-operator|dtor
    baz1(String("kid")); //(const char*)-ctor|move-ctor|dtor

    std::cout << "=start vector test=" << std::endl;

    std::vector<String> svec;
    svec.push_back(s0);         //copy-ctor
    svec.push_back(s1);         //copy-ctor
    svec.push_back("good job"); //(const char*)-ctor|move-ctor|dtor

    std::cout << "=end vector test=" << std::endl;

    std::cout << "==end main==" << std::endl;
    return 0;
}

// 命令：g++ -O0 -g -Wall -o test string_test.cpp && ./test
