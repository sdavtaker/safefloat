#ifndef BOOST_SAFE_FLOAT_POLICY_CHECK_ADDITION_INVALID_RESULT_HPP
#define BOOST_SAFE_FLOAT_POLICY_CHECK_ADDITION_INVALID_RESULT_HPP

#include <boost/safe_float/policy/check_base_policy.hpp>

#ifdef FENV_AVAILABLE
#pragma STDC FENV_ACCESS ON
#include <fenv.h>
#else
#include <cmath>
#endif

namespace boost {
namespace safe_float{
namespace policy{

template<class FP>
class check_addition_invalid_result : public check_policy<FP> {
public:
    virtual bool pre_addition_check(const FP& lhs, const FP& rhs){
#ifndef FENV_AVAILABLE
        return true;
#else
        return ! std::feclearexcept(FE_INVALID);
#endif
    }
    virtual bool post_addition_check(const FP& rhs){
#ifndef FENV_AVAILABLE
        return !isnan(rhs);
#else
        return ! std::fetestexcept(FE_INVALID);
#endif
    }
    virtual std::string addition_failure_message(){
        return std::string("Invalid result from arithmetic operation obtained");
    }
};

}
}
}

#endif // BOOST_SAFE_FLOAT_POLICY_CHECK_ADDITION_INVALID_RESULT_HPP

