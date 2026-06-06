// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>
#include <string_view>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/permutation_in_string.hpp"

TEMPLATE_TEST_CASE_SIG(
    "Permutation in string",
    "[permutation_in_string]",
    (auto check_inclusion, check_inclusion),
    forfun::permutation_in_string::check_inclusion,
    forfun::permutation_in_string::experimental::check_inclusion
)
{
    SECTION("One character needle which exists")
    {
        static constexpr std::string_view const needle{"h"};
        static constexpr std::string_view const haystack{"h"};

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE(check_inclusion(needle, haystack));
    }

    SECTION("One character needle which does not exist")
    {
        static constexpr std::string_view const needle{"g"};
        static constexpr std::string_view const haystack{"h"};

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE_FALSE(check_inclusion(needle, haystack));
    }

    SECTION("Two-characters needle (case 1)")
    {
        static constexpr std::string_view const needle{"ee"};
        static constexpr std::string_view const haystack{"ee"};

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE(check_inclusion(needle, haystack));
    }

    SECTION("Two-characters needle (case 2)")
    {
        static constexpr std::string_view const needle{"ee"};
        static constexpr std::string_view const haystack{"az"};

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE_FALSE(check_inclusion(needle, haystack));
    }

    SECTION("Two-characters needle (case 3)")
    {
        static constexpr std::string_view const needle{"az"};
        static constexpr std::string_view const haystack{"za"};

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE(check_inclusion(needle, haystack));
    }

    SECTION("Two-characters needle (case 4)")
    {
        static constexpr std::string_view const needle{"az"};
        static constexpr std::string_view const haystack{"xa"};

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE_FALSE(check_inclusion(needle, haystack));
    }

    SECTION("Two-characters needle (case 5)")
    {
        static constexpr std::string_view const needle{"az"};
        static constexpr std::string_view const haystack{"zxa"};

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE_FALSE(check_inclusion(needle, haystack));
    }

    SECTION("Two-characters needle (case 6)")
    {
        static constexpr std::string_view const needle{"at"};
        static constexpr std::string_view const haystack{"cat"};

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE(check_inclusion(needle, haystack));
    }

    SECTION("Two-characters needle (case 7)")
    {
        static constexpr std::string_view const needle{"be"};
        static constexpr std::string_view const haystack{"bbee"};

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE(check_inclusion(needle, haystack));
    }

    SECTION("Two-characters needle (case 8)")
    {
        static constexpr std::string_view const needle{"az"};
        static constexpr std::string_view const haystack{"abcdwxyz"};

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE_FALSE(check_inclusion(needle, haystack));
    }

    SECTION("Two-characters needle (case 9)")
    {
        static constexpr std::string_view const needle{"xy"};
        static constexpr std::string_view const haystack{"yyyyyyx"};

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE(check_inclusion(needle, haystack));
    }

    SECTION("Two-characters needle (case 10)")
    {
        static constexpr std::string_view const needle{"xy"};
        static constexpr std::string_view const haystack{"yyyyyx"};

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE(check_inclusion(needle, haystack));
    }

    SECTION("Three-characters needle (case 1)")
    {
        static constexpr std::string_view const needle{"xyz"};
        static constexpr std::string_view const haystack{"aaxybbyxcczyxddd"};

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE(check_inclusion(needle, haystack));
    }

    SECTION("Three-characters needle (case 2)")
    {
        static constexpr std::string_view const needle{"zxy"};
        static constexpr std::string_view const haystack{"aaxybbyxcczyxddd"};

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE(check_inclusion(needle, haystack));
    }

    SECTION("Three-characters needle (case 3)")
    {
        static constexpr std::string_view const needle{"xyz"};
        static constexpr std::string_view const haystack{"aaxybbyxcczzyxxddd"};

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE(check_inclusion(needle, haystack));
    }

    SECTION("Three-characters needle (case 4)")
    {
        static constexpr std::string_view const needle{"xyz"};
        static constexpr std::string_view const haystack{"xxyzzzzz"};

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE(check_inclusion(needle, haystack));
    }

    SECTION("Three-characters needle (case 4)")
    {
        static constexpr std::string_view const needle{"xyz"};
        static constexpr std::string_view const haystack{"aaxybbyxcczyyxddd"};

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE_FALSE(check_inclusion(needle, haystack));
    }

    SECTION("Three-characters needle (case 5)")
    {
        static constexpr std::string_view const needle{"yxx"};
        static constexpr std::string_view const haystack{"hdkxyxmm"};

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE(check_inclusion(needle, haystack));
    }

    SECTION("Three-characters needle (case 6)")
    {
        static constexpr std::string_view const needle{"abc"};
        static constexpr std::string_view const haystack{"abc"};

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE(check_inclusion(needle, haystack));
    }

    SECTION("Three-characters needle (case 7)")
    {
        static constexpr std::string_view const needle{"zyx"};
        static constexpr std::string_view const haystack{"yyyyyyyyxzzz"};

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE(check_inclusion(needle, haystack));
    }

    SECTION("Three-characters needle (case 8)")
    {
        static constexpr std::string_view const needle{"zyx"};
        static constexpr std::string_view const haystack{"yyyyyyyyxxxxzzzz"};

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE_FALSE(check_inclusion(needle, haystack));
    }

    SECTION("Three-characters needle (case 9)")
    {
        static constexpr std::string_view const needle{"dfd"};
        static constexpr std::string_view const haystack{
            "dddfaaaaaaaaaaaacama"
        };

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE(check_inclusion(needle, haystack));
    }

    SECTION("Four-character needle")
    {
        static constexpr std::string_view const needle{"aaaz"};
        static constexpr std::string_view const haystack{"aaaaaz"};

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE(check_inclusion(needle, haystack));
    }

    SECTION("Six-character needle")
    {
        static constexpr std::string_view const needle{"addyhr"};
        static constexpr std::string_view const haystack{"daddyhr"};

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE(check_inclusion(needle, haystack));
    }

    SECTION("All except one lower case letters (case 1)")
    {
        static constexpr std::string_view const needle{
            "abcdefghijklmnopqrstuvwxy"
        };
        static constexpr std::string_view const haystack{
            "abcdefghijklmnopqrstuvwxyz"
        };

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE(check_inclusion(needle, haystack));
    }

    SECTION("All except one lower case letters (case 2)")
    {
        static constexpr std::string_view const needle{
            "bcdefghijklmnopqrstuvwxyz"
        };
        static constexpr std::string_view const haystack{
            "abcdefghijklmnopqrstuvwxyz"
        };

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE(check_inclusion(needle, haystack));
    }

    SECTION("All except one lower case letters (case 3)")
    {
        static constexpr std::string_view const needle{
            "abcdefghijklmnopqrstuvwxy"
        };
        static constexpr std::string_view const haystack{
            "abcdefghijklmnopqrsuvwxyz"
        };

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE_FALSE(check_inclusion(needle, haystack));
    }

    SECTION("Identical strings")
    {
        static constexpr std::string_view const needle{
            "abcdefghijklmnopqrstuvwxyz"
        };
        static constexpr std::string_view const haystack{
            "abcdefghijklmnopqrstuvwxyz"
        };

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE(check_inclusion(needle, haystack));
    }

    SECTION("Permetated identical strings")
    {
        static constexpr std::string_view const needle{
            "abcdefghijklmnopqrstuvwxyz"
        };
        static constexpr std::string_view const haystack{
            "ypbkmzonidjvsxecuwahrgltqf"
        };

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE(check_inclusion(needle, haystack));
    }

    SECTION("benchmark case")
    {
        static constexpr std::string_view const needle{"cdeo"};
        static constexpr std::string_view const haystack{
            "abcdefghijklmnopqrstuvwxyz"
            "abcdefghijklmnopqrstuvwxyz"
            "abcdefghijklmnopqrstuvwxyz"
            "abcdefghijklmnopqrstuvwxyz"
            "abcdefghijklmnopqrstcode"
        };

        static_assert(haystack.size() == std::size_t{128});

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE(check_inclusion(needle, haystack));
    }

    SECTION("NeetCode case 1")
    {
        static constexpr std::string_view const needle{"abc"};
        static constexpr std::string_view const haystack{"lecabee"};

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE(check_inclusion(needle, haystack));
    }

    SECTION("NeetCode case 2")
    {
        static constexpr std::string_view const needle{"abc"};
        static constexpr std::string_view const haystack{"lecaabee"};

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE_FALSE(check_inclusion(needle, haystack));
    }

    SECTION("LeetCode case 1")
    {
        static constexpr std::string_view const needle{"ab"};
        static constexpr std::string_view const haystack{"eidbaooo"};

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE(check_inclusion(needle, haystack));
    }

    SECTION("LeetCode case 2")
    {
        static constexpr std::string_view const needle{"ab"};
        static constexpr std::string_view const haystack{"eidboaoo"};

        CAPTURE(needle);
        CAPTURE(haystack);

        REQUIRE_FALSE(check_inclusion(needle, haystack));
    }
}
