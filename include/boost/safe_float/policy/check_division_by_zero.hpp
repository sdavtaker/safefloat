#ifndef BOOST_SAFE_FLOAT_POLICY_CHECK_DIVISION_BY_ZERO_HPP
#define BOOST_SAFE_FLOAT_POLICY_CHECK_DIVISION_BY_ZERO_HPP

#include <boost/safe_float/policy/check_base_policy.hpp>

#ifdef FENV_AVAILABLE
#pragma STDC FENV_ACCESS ON
#include <fenv.h>
#endif

namespace boost {
namespace safe_float{
namespace policy{

template<class FP>
class check_division_by_zero : public check_policy<FP> {
public:
    virtual bool pre_division_check(const FP& lhs, const FP& rhs){
#ifndef FENV_AVAILABLE
        return (rhs!=0);
#else
        return ! std::feclearexcept(FE_DIVBYZERO);
#endif
    }

    virtual bool post_division_check(const FP& rhs){
#ifndef FENV_AVAILABLE
        return true;
#else
        return ! std::fetestexcept(FE_DIVBYZERO);
#endif
    }

    virtual std::string division_failure_message(){
        return std::string("Division by zero");
    }

};

}
}
}

#endif // BOOST_SAFE_FLOAT_POLICY_CHECK_DIVISION_BY_ZERO_HPP

