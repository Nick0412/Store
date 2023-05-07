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

        std::future<int> result = pool.submit(add(a, b));

        EXPECT_EQ(result.get(), expected);
    }
}