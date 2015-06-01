#ifndef BOOST_SAFE_FLOAT_CHECK_BASE_POLICY_HPP
#define BOOST_SAFE_FLOAT_CHECK_BASE_POLICY_HPP

#include <type_traits>

namespace boost {
namespace safe_float{
namespace policy{

/**
 * Base policy for check
 */
template<class FP>
class check_policy {
public:
    //operator+
    virtual bool pre_addition_check(const FP& lhs, const FP& rhs){return true;}
    virtual bool post_addition_check(const FP& value){return true;}
    virtual std::string addition_failure_message() { return std::string("Failed to add");}
    //operator-
    //operator/
    //...
    virtual ~check_policy(){}
};

/**
 * compose_check_policy creates a new policy combining the policies received by parameter
 */
template<class FP, class... POLICIES>
class compose_check_policy : public check_policy<FP> {
//TODO: NOT IMPLEMENTED
};

} //policy
} //safe_float
} //boost
#endif // BOOST_SAFE_FLOAT_CHECK_BASE_POLICY_HPP
