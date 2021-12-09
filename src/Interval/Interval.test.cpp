#include <Interval.h>
#include <gtest/gtest.h>

TEST(Interval, duration) {
    auto interval = Interval{};
    interval.setDuration(std::chrono::seconds{10});

    EXPECT_EQ(interval.getDuration<std::chrono::milliseconds>(), std::chrono::milliseconds{10000});
}

TEST(Interval, description) {
    auto interval = Interval{};
    interval.setDescripton("Hello World");

    EXPECT_EQ(interval.getDescripton(), std::string{"Hello World"});
}
