/// Problem sources:
/// https://simontoth.substack.com/p/daily-bite-of-c-sonar
/// https://compiler-explorer.com/z/v4TdoqKc1

#include <cstdlib>
#include <vector>

struct Area {
    int top;
    int bottom;
    int left;
    int right;
};

struct Sonar {
    struct Coord {
        int x;
        int y;
    };

    std::vector<Coord> coords;
    bool ping(Area area) const;
};

/// Problem:
///
/// You are given access to a ping method on a sonar system.
///
/// As quickly as possible, determine the number of ships in the given
/// area using this method. The method only returns information about
/// presence (whether any ships are in the given area).
///
/// The area includes the borders.

int count_ships(Sonar const& sonar, const Area area) {
    if (!sonar.ping(area)) {
        return 0;
    }

    int const width{std::abs(area.right - area.left)};
    int const height{std::abs(area.bottom - area.top)};

    if ((width + height) == 0) {
        return 1;
    }

    int const mw0{area.left + (width / 2)};
    int const mw1{mw0 + 1};
    int const mh0{area.top + (height / 2)};
    int const mh1{mh0 + 1};

    return count_ships(
               sonar,
               {
                   area.top,
                   mh0,
                   area.left,
                   mw0,
               })
        + count_ships(
               sonar,
               {
                   area.top,
                   mh0,
                   mw1,
                   area.right,
               })
        + count_ships(
               sonar,
               {
                   mh1,
                   area.bottom,
                   area.left,
                   mw0,
               })
        + count_ships(
               sonar,
               {
                   mh1,
                   area.bottom,
                   mw1,
                   area.right,
               });
}

#include <algorithm>
#include <cassert>
#include <iostream>

int main() {
    {
        [[maybe_unused]] int num_ships;
        Sonar s{{{0, 0}}};

        num_ships = count_ships(s, {0, 0, 0, 0});
        assert(num_ships == 1);

        num_ships = count_ships(s, {0, 0, 1, 3});
        assert(num_ships == 0);

        num_ships = count_ships(s, {0, 5, 0, 7});
        assert(num_ships == 1);

        num_ships = count_ships(s, {0, 0, 0, 7});
        assert(num_ships == 1);
    }

    {
        [[maybe_unused]] int num_ships;
        Sonar s{{{0, 7}, {2, 5}, {3, 3}, {4, 6}, {5, 2}}};

        num_ships = count_ships(s, {0, 0, 7, 7});
        assert(num_ships == 1);

        num_ships = count_ships(s, {0, 5, 1, 5});
        assert(num_ships == 3);

        num_ships = count_ships(s, {0, 5, 2, 7});
        assert(num_ships == 5);

        num_ships = count_ships(s, {1, 3, 0, 2});
        assert(num_ships == 0);
    }

    {
        [[maybe_unused]] int num_ships;
        Sonar t1{{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}}};

        num_ships = count_ships(t1, {1, 1, 1, 1});
        assert(num_ships == 1);

        num_ships = count_ships(t1, {1, 2, 1, 2});
        assert(num_ships == 2);

        num_ships = count_ships(t1, {1, 5, 1, 5});
        assert(num_ships == 5);

        Sonar t2{{{345, 456}}};

        num_ships = count_ships(t2, {1, 1000, 1, 1000});
        assert(num_ships == 1);

        Sonar t3 = {{{102, 430}, {488, 821}, {863, 875}, {820, 684}, {453, 603},
                     {99, 476},  {516, 730}, {582, 54},  {349, 987}, {541, 437},
                     {572, 947}, {189, 21},  {6, 533},   {99, 229},  {694, 675},
                     {816, 1},   {669, 555}, {753, 916}, {602, 260}, {194, 708},
                     {371, 886}, {461, 562}, {106, 781}, {379, 509}, {38, 255},
                     {337, 427}, {991, 482}, {161, 11},  {125, 802}, {818, 813},
                     {377, 644}, {185, 336}, {185, 114}, {567, 627}, {800, 891},
                     {734, 55},  {4, 906},   {490, 175}, {622, 509}, {797, 839},
                     {876, 511}, {130, 609}, {362, 783}, {333, 865}, {563, 913},
                     {217, 18},  {311, 913}, {420, 397}, {383, 438}, {289, 741},
                     {338, 231}, {113, 564}, {421, 588}, {108, 788}, {283, 829},
                     {37, 204},  {558, 800}, {64, 693},  {248, 399}, {142, 217},
                     {160, 603}, {771, 62},  {19, 905},  {393, 383}, {709, 484},
                     {376, 246}, {51, 769},  {895, 597}, {78, 776},  {209, 461},
                     {414, 361}, {213, 57},  {199, 721}, {343, 305}, {628, 921},
                     {8, 535},   {594, 958}, {918, 539}, {652, 370}, {258, 811},
                     {780, 977}, {812, 994}, {811, 684}, {586, 201}, {550, 721},
                     {62, 448},  {709, 875}, {127, 106}, {965, 881}, {886, 989},
                     {718, 115}, {239, 140}, {397, 965}, {464, 598}, {684, 609},
                     {228, 766}, {886, 944}, {14, 64},   {143, 956}}};
        num_ships = count_ships(t3, {1, 1000, 1, 1000});
        assert(num_ships == 99);
    }
}

bool Sonar::ping(Area area) const {
    return std::ranges::any_of(coords, [&area](Coord const& coord) {
        return coord.x >= area.top && coord.x <= area.bottom
            && coord.y >= area.left && coord.y <= area.right;
    });
}
