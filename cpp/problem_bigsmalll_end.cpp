#include <iostream>

using namespace std;

int main()
{
    union
    {
        short s;
        char c[sizeof(short)];
    } un;
    un.s = 0x0102;
    if (sizeof(short) == 2)
    {
        if (un.c[0] == 1 && un.c[1] == 2)
        {
            cout << "大端" << endl;
        }
        else if (un.c[1] == 1 && un.c[0] == 2)
        {
            cout << "小端" << endl;
        }
        else
        {
            cout << "unknown" << endl;
        }
    }
    else
    {
        cout << "sizeof(short)=" << sizeof(short) << endl;
    }
    return 0;
}
