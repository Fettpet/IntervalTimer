#include <QSignalSpy>
#include <Timer.h>
#include <chrono>
#include <gtest/gtest.h>
#include <memory>

TEST(Timer, timeout) {
    auto timer = std::make_unique<Timer>();
    QSignalSpy spy(timer.get(), &Timer::timeout);

    EXPECT_EQ(spy.count(), 0);
    timer->start(std::chrono::milliseconds{1});

    EXPECT_TRUE(spy.wait(10));
}
