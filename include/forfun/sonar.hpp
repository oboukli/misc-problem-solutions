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

#include <algorithm>
#include <cstdlib>
#include <functional>
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

    sonar(sonar&& other) noexcept = delete;

    explicit sonar(std::vector<coord>&& coords) noexcept :
        coords_{std::move(coords)}
    {
    }

    ~sonar() noexcept = default;

    auto operator=(sonar const&) -> sonar = delete;

    auto operator=(sonar&&) noexcept -> sonar = delete;

    [[nodiscard]] constexpr auto ping(area const area) const noexcept -> bool
    {
        using std::greater_equal;
        using std::less_equal;
        using std::ranges::any_of;

        return any_of(
            coords_, [&area](coord const& coord) constexpr noexcept -> bool {
                return greater_equal{}(coord.x, area.top)
                    and less_equal{}(coord.x, area.bottom)
                    and greater_equal{}(coord.y, area.left)
                    and less_equal{}(coord.y, area.right);
            }
        );
    }

private:
    std::vector<coord> coords_;
};

[[nodiscard]] constexpr auto
count_ships(sonar const& sonar, area const area) noexcept -> int
{
    using std::abs;

    if (not sonar.ping(area))
    {
        return 0;
    }

    int const width{abs(area.right - area.left)};
    int const height{abs(area.bottom - area.top)};

    if ((width + height) == 0) [[unlikely]]
    {
        return 1;
    }

    int const mw0{area.left + (width / 2)};
    int const mw1{mw0 + 1};
    int const mh0{area.top + (height / 2)};
    int const mh1{mh0 + 1};

    // clang-format off
    return (
        count_ships(
            sonar,
            {
                .top = area.top,
                .bottom = mh0,
                .left = area.left,
                .right = mw0,
            }
        ) +
        count_ships(
            sonar,
            {
                .top = area.top,
                .bottom = mh0,
                .left = mw1,
                .right = area.right,
            }
        ) +
        count_ships(
            sonar,
            {
                .top = mh1,
                .bottom = area.bottom,
                .left = area.left,
                .right = mw0,
            }
        ) +
        count_ships(
            sonar,
            {
                .top = mh1,
                .bottom = area.bottom,
                .left = mw1,
                .right = area.right,
            }
        )
    );
    // clang-format on
}

} // namespace forfun::sonar

#endif // FORFUN_SONAR_HPP_
