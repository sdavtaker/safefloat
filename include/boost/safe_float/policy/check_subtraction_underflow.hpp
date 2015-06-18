#ifndef BOOST_SAFE_FLOAT_POLICY_CHECK_SUBTRACTION_UNDERFLOW_HPP
#define BOOST_SAFE_FLOAT_POLICY_CHECK_SUBTRACTION_UNDERFLOW_HPP

#include <boost/safe_float/policy/check_base_policy.hpp>

#ifdef FENV_AVAILABLE
#pragma STDC FENV_ACCESS ON
#include <fenv.h>
#endif

namespace boost {
namespace safe_float{
namespace policy{

template<class FP>
class check_subtraction_underflow : public check_policy<FP> {
public:
    virtual bool pre_subtraction_check(const FP& lhs, const FP& rhs){
#ifndef FENV_AVAILABLE
        return true;
#else
        return ! std::feclearexcept(FE_UNDERFLOW);
#endif
    }

    virtual bool post_subtraction_check(const FP& rhs){
#ifndef FENV_AVAILABLE
        return std::fpclassify( rhs ) != FP_SUBNORMAL;
#else
        return ! std::fetestexcept(FE_UNDERFLOW);
#endif
    }

    virtual std::string subtraction_failure_message(){
        return std::string("Underflow from operation");
    }
};

}
}
}

#endif // BOOST_SAFE_FLOAT_POLICY_CHECK_SUBTRACTION_UNDERFLOW_HPP

