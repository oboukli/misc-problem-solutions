/// Problem sources:
/// https://simontoth.substack.com/p/daily-bite-of-c-sonar
/// https://compiler-explorer.com/z/v4TdoqKc1
///
/// Original problem text:
/// You are given access to a ping method on a sonar system.
///
/// As quickly as possible, determine the number of ships in the given
/// area using this method. The method only returns information about
/// presence (whether any ships are in the given area).
///
/// The area includes the borders.

#ifndef FORFUN_SONAR_HPP_
#define FORFUN_SONAR_HPP_

#include <utility>
#include <vector>

namespace forfun::sonar {

struct Area final {
    int top{};
    int bottom{};
    int left{};
    int right{};
};

class Sonar final {
public:
    struct Coord final {
        int x{};
        int y{};
    };

private:
    std::vector<Coord> coords_;

public:
    Sonar(Sonar const&) = delete;

    Sonar(Sonar&& rhs) = delete;

    explicit Sonar(std::vector<Coord>&& coords) noexcept :
        coords_(std::move(coords))
    {
    }

    ~Sonar() = default;

    auto operator=(Sonar const&) -> Sonar = delete;

    auto operator=(Sonar&&) -> Sonar = delete;

    [[nodiscard]] auto ping(Area area) const noexcept -> bool;
};

auto count_ships(Sonar const& sonar, Area area) noexcept -> int;

} // namespace forfun::sonar

#endif // FORFUN_SONAR_HPP_
