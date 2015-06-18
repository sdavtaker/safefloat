#ifndef BOOST_SAFE_FLOAT_CHECK_BASE_POLICY_HPP
#define BOOST_SAFE_FLOAT_CHECK_BASE_POLICY_HPP

#include <string>
#include <cmath>

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
    virtual bool pre_subtraction_check(const FP& lhs, const FP& rhs){return true;}
    virtual bool post_subtraction_check(const FP& value){return true;}
    virtual std::string subtraction_failure_message() { return std::string("Failed to subtract");}
    //operator*
    virtual bool pre_multiplication_check(const FP& lhs, const FP& rhs){return true;}
    virtual bool post_multiplication_check(const FP& value){return true;}
    virtual std::string multiplication_failure_message() { return std::string("Failed to multiply");}
    //operator/
    virtual bool pre_division_check(const FP& lhs, const FP& rhs){return true;}
    virtual bool post_division_check(const FP& value){return true;}
    virtual std::string division_failure_message() { return std::string("Failed to divide");}

    virtual ~check_policy(){}
};

} //policy
} //safe_float
} //boost
#endif // BOOST_SAFE_FLOAT_CHECK_BASE_POLICY_HPP
