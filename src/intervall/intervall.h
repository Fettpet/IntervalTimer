#pragma once
#include <chrono>
#include <string>

struct Intervall {
public:
    Intervall();
    Intervall(std::chrono::milliseconds const&, std::string const&);
    Intervall(Intervall const&) = default;
    Intervall(Intervall&&) = default;

    Intervall& operator=(Intervall const&) = default;
    Intervall& operator=(Intervall&&) = default;

    auto operator==(Intervall const&) const -> bool = default;
    void setDuration(std::chrono::milliseconds const& dur);

    template<typename Duration>
    Duration getDuration() const {
        return std::chrono::duration_cast<Duration>(duration);
    }

    void setDescripton(std::string const&);
    std::string getDescripton() const;

protected:
    std::chrono::milliseconds duration{0};
    std::string description;
};
