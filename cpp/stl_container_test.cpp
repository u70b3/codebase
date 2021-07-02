#include <cassert>
#include <cmath>

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>   // std::stringstream
#include <execution> //std::execution::par
#include <thread>
#include <future>     // std::async
#include <filesystem> //std::filesystem
#include <chrono>     //std::chrono
#include <ctime>

using namespace std;

// std::async ，避免使用裸的 std::thread
void TEST_async()
{
    auto foo = []()
    {
        return 1000;
    };
    // create an async task
    // return std::future
    auto handle = std::async(std::launch::async, foo);
    // wait for the result
    auto res = handle.get();
    assert(res == 1000);
}

// std::filesystem
void TEST_filesystem()
{
    const auto bigFilePath{"bigFileToCopy"};
    if (std::filesystem::exists(bigFilePath))
    {
        const auto bigFileSize{std::filesystem::file_size(bigFilePath)};
        std::filesystem::path tmpPath{"/tmp"};
        if (std::filesystem::space(tmpPath).available > bigFileSize)
        {
            std::filesystem::create_directory(tmpPath.append("example"));
            std::filesystem::copy_file(bigFilePath, tmpPath.append("newFile"));
        }
    }
}

// c++11 时间库
void TEST_chrono()
{
    using namespace std::chrono_literals;
    auto now1 = std::chrono::steady_clock::now();

    auto two_hours = 2h;
    auto five_minutes = 5min;
    auto duration = two_hours + five_minutes;
    // 2 * 60 * 60 + 5 * 60
    auto seconds = chrono::duration_cast<chrono::seconds>(duration);
    assert(seconds.count() == 7500);
}

void TEST_all()
{
    TEST_async();
    TEST_filesystem();
    TEST_chrono();
}

int main()
{
    TEST_all();
    cout << "all test cases passed!" << endl;
    return 0;
};

// g++ stl_container_test.cpp -std=c++17 -o test && ./test && rm ./test
