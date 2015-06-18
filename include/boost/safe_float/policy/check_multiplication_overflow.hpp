#ifndef BOOST_SAFE_FLOAT_POLICY_CHECK_MULTIPLICATION_OVERFLOW_HPP
#define BOOST_SAFE_FLOAT_POLICY_CHECK_MULTIPLICATION_OVERFLOW_HPP

#include <boost/safe_float/policy/check_base_policy.hpp>

#ifdef FENV_AVAILABLE
#pragma STDC FENV_ACCESS ON
#include <fenv.h>
#endif

namespace boost {
namespace safe_float{
namespace policy{

template<class FP>
class check_multiplication_overflow : public check_policy<FP> {
    bool precond=true;
public:
    virtual bool pre_multiplication_check(const FP& lhs, const FP& rhs){
#ifndef FENV_AVAILABLE
        precond = std::isinf(lhs) || std::isinf(rhs);
        return true;
#else
        return ! std::feclearexcept(FE_OVERFLOW);
#endif
    }
    virtual bool post_multiplication_check(const FP& rhs){
#ifndef FENV_AVAILABLE
        return precond || ! std::isinf(rhs);
#else
        return ! std::fetestexcept(FE_OVERFLOW);
#endif
    }
    virtual std::string multiplication_failure_message(){
        return std::string("Overflow to infinite on multiplication operation");
    }
};

}
}
}

#endif // BOOST_SAFE_FLOAT_POLICY_CHECK_MULTIPLICATION_OVERFLOW_HPP

