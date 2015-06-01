#ifndef BOOST_SAFE_FLOAT_POLICY_CHECK_ADDITION_INEXACT_HPP
#define BOOST_SAFE_FLOAT_POLICY_CHECK_ADDITION_INEXACT_HPP
#include <boost/safe_float/policy/check_base_policy.hpp>

namespace boost {
namespace safe_float{
namespace policy{

template<class FP>
class check_addition_inexact : public check_policy<FP> {
    FP prev_l=0;
    FP prev_r=0;
public:
    virtual bool pre_addition_check(const FP& lhs, const FP& rhs){
        prev_l = lhs;
        prev_r = rhs;
        return true;
    }

    virtual bool post_addition_check(const FP& rhs){
        return (rhs - prev_r) == prev_l;
    }

    virtual std::string addition_failure_message(){
        return std::string("Non reversible addition applied");
    }

};

}
}
}
#endif // BOOST_SAFE_FLOAT_POLICY_CHECK_ADDITION_INEXACT_HPP
