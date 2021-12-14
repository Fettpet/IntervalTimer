#include <Interval.h>
#include <IntervalFromJson.h>
#include <IntervalToJson.h>
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

TEST(Interval, toJson) {
    auto interval = Interval{std::chrono::seconds{10}, "Hello World"};
    auto json = IntervalToJson::transform(interval);
    EXPECT_EQ(json["description"], "Hello World");
    EXPECT_EQ(json["durationMilliseconds"], 10000);
}

TEST(Interval, fromJson) {
    auto interval = Interval{std::chrono::seconds{10}, "Hello World"};
    auto json = IntervalToJson::transform(interval);
    auto transformedInterval = IntervalFromJson::transform(json);

    EXPECT_EQ(interval.getDescripton(), transformedInterval.getDescripton());
    EXPECT_EQ(interval.getDuration<std::chrono::seconds>(), transformedInterval.getDuration<std::chrono::seconds>());
}
