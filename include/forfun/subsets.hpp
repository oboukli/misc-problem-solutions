// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://leetcode.com/problems/subsets/

#ifndef FORFUN_SUBSETS_HPP_
#define FORFUN_SUBSETS_HPP_

#include <array>
#include <concepts>
#include <cstddef>
#include <iterator>
#include <memory_resource>
#include <vector>

namespace forfun::subsets {

/// This class template is obsoleted by C++26's std::inplace_vector
/// (which was not available to the author at the time of writing). This class
/// template was written for the joy of learning by doing.
template <typename ElementType, std::size_t NumElements>
    requires std::copy_constructible<ElementType>
class ElementInPlaceAllocatorFactory {
public:
    using value_type = ElementType;

    using allocator_type = std::pmr::polymorphic_allocator<ElementType>;

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
    ElementInPlaceAllocatorFactory() noexcept = default;

    ElementInPlaceAllocatorFactory(
        ElementInPlaceAllocatorFactory const&
    ) noexcept = delete;

    ElementInPlaceAllocatorFactory(ElementInPlaceAllocatorFactory&&) noexcept
        = delete;

    ~ElementInPlaceAllocatorFactory() noexcept = default;

    auto operator=(ElementInPlaceAllocatorFactory const&) noexcept
        -> ElementInPlaceAllocatorFactory& = delete;

    auto operator=(ElementInPlaceAllocatorFactory&&) noexcept
        -> ElementInPlaceAllocatorFactory& = delete;

    [[nodiscard]] constexpr auto allocator() const noexcept -> allocator_type
    {
        return allocator_;
    }

#ifdef __clang__
    [[nodiscard]] constexpr auto allocator() && noexcept -> allocator_type
        = delete;
#endif // __clang__

private:
    // n * (2 ^ (n - 1))
    static constexpr std::size_t const total_subset_elements{
        NumElements * (1UZ << (NumElements - 1UZ))
    };

    static constexpr std::size_t const element_buffer_size{
        sizeof(ElementType) * total_subset_elements
    };

    alignas(
        ElementType
    ) std::array<std::byte, element_buffer_size> element_buffer;

    std::pmr::monotonic_buffer_resource element_mem_rsc{
        element_buffer.data(), element_buffer.size()
    };

    allocator_type allocator_{&element_mem_rsc};
};

/// This class template is obsoleted by C++26's std::inplace_vector
/// (which was not available to the author at the time of writing). This class
/// template was written for the joy of learning by doing.
template <
    typename ElementType,
    typename ElementAllocator,
    std::size_t NumElements>
    requires std::copy_constructible<ElementType>
class SubsetInPlaceAllocatorFactory {
public:
    using value_type = std::vector<ElementType, ElementAllocator>;

    using allocator_type = std::pmr::polymorphic_allocator<value_type>;

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
    SubsetInPlaceAllocatorFactory() noexcept = default;

    SubsetInPlaceAllocatorFactory(SubsetInPlaceAllocatorFactory const&) noexcept
        = delete;

    SubsetInPlaceAllocatorFactory(SubsetInPlaceAllocatorFactory&&) noexcept
        = delete;

    ~SubsetInPlaceAllocatorFactory() noexcept = default;

    auto operator=(SubsetInPlaceAllocatorFactory const&) noexcept
        -> SubsetInPlaceAllocatorFactory& = delete;

    auto operator=(SubsetInPlaceAllocatorFactory&&) noexcept
        -> SubsetInPlaceAllocatorFactory& = delete;

    [[nodiscard]] constexpr auto allocator() const noexcept -> allocator_type
    {
        return allocator_;
    }

#ifdef __clang__
    [[nodiscard]] constexpr auto allocator() && noexcept -> allocator_type
        = delete;
#endif // __clang__

private:
    // 2 ^ n
    static constexpr std::size_t const total_subsets{1UZ << NumElements};

    static constexpr std::size_t const subset_buffer_size{
        sizeof(value_type) * total_subsets
    };

    alignas(value_type) std::array<std::byte, subset_buffer_size> subset_buffer;

    std::pmr::monotonic_buffer_resource subset_mem_rsc{
        subset_buffer.data(), subset_buffer.size()
    };

    allocator_type allocator_{&subset_mem_rsc};
};

namespace iterative {

// (Placeholder)

} // namespace iterative

namespace recursive {

namespace detail {

template <
    typename ConstIter,
    typename Sentinel,
    typename Container,
    typename ElementAllocator>
    requires std::forward_iterator<ConstIter>
    and std::sized_sentinel_for<ConstIter, Sentinel>
constexpr auto do_explode_subsets(
    std::vector<std::iter_value_t<ConstIter>, ElementAllocator> const& subset,
    ConstIter const& first,
    Sentinel const& last,
    Container& subsets,
    ElementAllocator const& element_allocator
) -> void
{
    if (first == last) [[unlikely]]
    {
        subsets.emplace_back(subset);
        return;
    }

    std::vector<std::iter_value_t<ConstIter>, ElementAllocator> current_subset{
        element_allocator
    };
    current_subset.reserve(subset.size() + 1UZ);

    current_subset.assign(subset.cbegin(), subset.cend());

    auto const next{std::next(first)};

    do_explode_subsets(current_subset, next, last, subsets, element_allocator);

    current_subset.emplace_back(*first);
    do_explode_subsets(current_subset, next, last, subsets, element_allocator);
}

} // namespace detail

/// While using std::vector is not optimal, the decision to utilize
/// std::vector was for learning about PMR allocators.
template <
    typename ConstIter,
    typename Sentinel,
    typename ElementAllocator = std::vector<int>::allocator_type,
    typename SubsetAllocator
    = std::vector<std::vector<int, ElementAllocator>>::allocator_type>
    requires std::contiguous_iterator<ConstIter>
    and std::sized_sentinel_for<ConstIter, Sentinel>
[[nodiscard]] constexpr auto explode_subsets(
    ConstIter const& first,
    Sentinel const& last,
    SubsetAllocator subset_allocator
    = std::vector<std::vector<int>>::allocator_type{},
    ElementAllocator element_allocator = std::vector<int>::allocator_type{}
) -> std::vector<std::vector<int, ElementAllocator>, SubsetAllocator>
{
    std::vector<std::vector<int, ElementAllocator>, SubsetAllocator> subsets{
        subset_allocator
    };
    subsets.reserve(
        1UZ << static_cast<std::size_t>(std::abs(std::distance(first, last)))
    );

    std::vector<int, ElementAllocator> const empty_subset{element_allocator};

    detail::do_explode_subsets(
        empty_subset, first, last, subsets, element_allocator
    );

    return subsets;
}

} // namespace recursive

} // namespace forfun::subsets

#endif // FORFUN_SUBSETS_HPP_
