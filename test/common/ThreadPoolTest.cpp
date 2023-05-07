#include "gtest/gtest.h"
#include "common/ThreadPool.h"

namespace
{
    int add(int a, int b)
    {
        return a + b;
    }

    TEST(ThreadPool, BasicThreadPoolTest)
    {
        std::srand(std::time(nullptr));
        int a = std::rand();
        int b = std::rand();
        int expected = add(a, b);

        Common::ThreadPool pool(1);

        std::function<int(int,int)> wrapped = add;

        std::future<int> result = pool.submit(wrapped, a, b);

        auto actual = result.get();

        std::cout << "A: " << a 
                  << " B: " << b 
                  << " Actual Result: " << actual
                  << "\n";

        EXPECT_EQ(actual, expected);
    }
}