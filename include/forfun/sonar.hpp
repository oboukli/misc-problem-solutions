/// Problem sources:
/// - https://simontoth.substack.com/p/daily-bite-of-c-sonar
/// - https://compiler-explorer.com/z/v4TdoqKc1
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

struct area final {
    int top{};

    int bottom{};

    int left{};

    int right{};
};

struct coord final {
    int x{};

    int y{};
};

class sonar final {
public:
    sonar() = delete;

    sonar(sonar const&) = delete;

    sonar(sonar&& rhs) = delete;

    explicit sonar(std::vector<coord>&& coords) noexcept :
        coords_{std::move(coords)}
    {
    }

    ~sonar() = default;

    auto operator=(sonar const&) -> sonar = delete;

    auto operator=(sonar&&) -> sonar = delete;

    [[nodiscard]] auto ping(area area) const noexcept -> bool;

private:
    std::vector<coord> coords_;
};

[[nodiscard]] auto count_ships(sonar const& sonar, area area) noexcept -> int;

} // namespace forfun::sonar

#endif // FORFUN_SONAR_HPP_
