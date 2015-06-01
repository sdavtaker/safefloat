#ifndef BOOST_SAFE_FLOAT_POLICY_CHECK_ADDITION_OVERFLOW_HPP
#define BOOST_SAFE_FLOAT_POLICY_CHECK_ADDITION_OVERFLOW_HPP
#include <boost/safe_float/policy/check_base_policy.hpp>

namespace boost {
namespace safe_float{
namespace policy{

template<class FP>
class check_addition_overflow : public check_policy<FP> {
    bool precond=true;
public:
    virtual bool pre_addition_check(const FP& lhs, const FP& rhs){
        precond = std::isinf(lhs) || std::isinf(rhs);
        return true;
    }
    virtual bool post_addition_check(const FP& rhs){
        return !precond && !std::isinf(rhs);
    }
    virtual std::string addition_failure_message(){
        return std::string("Overflow to infinite on addition operation");
    }
};

}
}
}
#endif // BOOST_SAFE_FLOAT_POLICY_CHECK_ADDITION_OVERFLOW_HPP
