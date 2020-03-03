#pragma once

namespace Comparators
{
template <typename LhsMap, typename RhsMap>
bool mapComparator(const LhsMap& lhs, const RhsMap& rhs)
{
    return lhs.size() == rhs.size()
            and std::is_permutation(lhs.begin(),
                                    lhs.end(),
                                    rhs.begin(),
                                    [](const auto a, const auto b){return a.first == b.first
                                                                      and a.second == b.second;});
}
}//Comparators
