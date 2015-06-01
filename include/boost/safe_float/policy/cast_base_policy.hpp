#ifndef BOOST_SAFE_FLOAT_CAST_BASE_POLICY_HPP
#define BOOST_SAFE_FLOAT_CAST_BASE_POLICY_HPP

#include <type_traits>

namespace boost {
namespace safe_float{
namespace policy{

/**
 * @brief Base policy for cast
 */
template<class FP>
struct cast_policy{};

template<class FP>
struct cast_none{};

/**
 * @brief compose_cast_policy creates a new policy combining the policies received by parameter
 * Cast policies passed by parameter should implement non overlaping casting methods
 */
template<class FP, template<class> class... POLICIES>
class compose_cast_policy : public POLICIES<FP>... {
//TODO: NOT IMPLEMENTED
    //check all POLICIES inherit from cast_policy
};

} //policy
} //safe_float
} //boost
#endif // BOOST_SAFE_FLOAT_CHECK_BASE_POLICY_HPP

