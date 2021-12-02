#pragma once
#include <gtest/gtest.h>
#include <intervall/intervall.h>

TEST(Intervall, duration) {
    auto intervall = Intervall{};
    intervall.setDuration(std::chrono::seconds{10});

    EXPECT_EQ(intervall.getDuration<std::chrono::milliseconds>(), std::chrono::milliseconds{10000});
}

TEST(Intervall, description) {
    auto intervall = Intervall{};
    intervall.setDescripton("Hello World");

    EXPECT_EQ(intervall.getDescripton(), std::string{"Hello World"});
}
