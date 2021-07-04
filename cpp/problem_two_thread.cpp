#include <iostream>
#include <thread>
#include <atomic>

#include "unistd.h"

using namespace std;

// 0: t1_writeable, 1: t1_writing, 2: t2_writeable, 3: t2_writing
atomic<int> state;

// ps: compare_exchange_weak/strong both ok in x86, strong use in ARM or xx

void f1()
{
    for (int i = 0; i < 10; i++)
    {
        // spinlock with state
        while (true)
        {
            int expected = 0;
            if (state.compare_exchange_weak(expected, 1))
                break;
            // for performance
            usleep(1);
        }
        cout << i + 1 << " ";
        state = 2;
    }
}

void f2()
{
    for (int i = 0; i < 10; i++)
    {
        // spinlock with state
        while (true)
        {
            int expected = 2;
            if (state.compare_exchange_weak(expected, 3))
                break;
            // for performance
            usleep(1);
        }
        cout << char(i + 'a') << " ";
        state = 0;
    }
}

int main()
{
    state = 0;
    thread t1(f1), t2(f2);
    t1.join();
    t2.join();
    return 0;
}
// g++ problem_two_thread.cpp -std=c++17 -o test && ./test && rm ./test
