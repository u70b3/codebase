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

using namespace std;

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

void TEST_all()
{
    TEST_async();
    TEST_filesystem();
}

int main()
{
    TEST_all();
    return 0;
};

// g++ stl_container_test.cpp -std=c++17 -o test && ./test && rm ./test
