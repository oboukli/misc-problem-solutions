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

#include <vector>

namespace forfun::sonar {

struct Area {
    int top{};
    int bottom{};
    int left{};
    int right{};
};

class Sonar final {
public:
    struct Coord {
        int x{};
        int y{};
    };

    std::vector<Coord> coords;

    [[nodiscard]] auto ping(Area area) const -> bool;
};

auto count_ships(Sonar const& sonar, Area area) -> int;

} // namespace forfun::sonar

#endif // FORFUN_SONAR_HPP_
