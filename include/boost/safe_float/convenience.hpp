#ifndef BOOST_SAFE_FLOAT_CONVENIENCE_HPP
#define BOOST_SAFE_FLOAT_CONVENIENCE_HPP

//check policies
#include <boost/safe_float/policy/check_base_policy.hpp>

//error handling policies
#include <boost/safe_float/policy/on_fail_base_policy.hpp>

//cast policies
#include <boost/safe_float/policy/cast_base_policy.hpp>

//composed policies
#include <boost/safe_float/policy/policy_composers.hpp>

#include <boost/safe_float/policy/check_addition_overflow.hpp>
#include <boost/safe_float/policy/check_subtraction_overflow.hpp>
#include <boost/safe_float/policy/check_multiplication_overflow.hpp>
#include <boost/safe_float/policy/check_division_overflow.hpp>

#include <boost/safe_float/policy/check_addition_underflow.hpp>
#include <boost/safe_float/policy/check_subtraction_underflow.hpp>
#include <boost/safe_float/policy/check_multiplication_underflow.hpp>
#include <boost/safe_float/policy/check_division_underflow.hpp>

#include <boost/safe_float/policy/check_addition_inexact.hpp>
#include <boost/safe_float/policy/check_subtraction_inexact.hpp>
#include <boost/safe_float/policy/check_multiplication_inexact.hpp>
#include <boost/safe_float/policy/check_division_inexact.hpp>

#include <boost/safe_float/policy/check_addition_invalid_result.hpp>
#include <boost/safe_float/policy/check_subtraction_invalid_result.hpp>
#include <boost/safe_float/policy/check_multiplication_invalid_result.hpp>
#include <boost/safe_float/policy/check_division_invalid_result.hpp>

#include <boost/safe_float/policy/check_division_by_zero.hpp>

namespace boost {
namespace safe_float{
namespace policy{

template<class FP>
using placeholder=check_policy<FP>;  //remove when other depend on the right compositions

template<class FP>
using check_overflow = compose_check<FP,
                                    check_addition_overflow,
                                    check_subtraction_overflow,
                                    check_division_overflow,
                                    check_multiplication_overflow>;

template<class FP>
using check_underflow = compose_check<FP,
                                    check_addition_underflow,
                                    check_subtraction_underflow,
                                    check_division_underflow,
                                    check_multiplication_underflow>;

template<class FP>
using check_invalid_result = compose_check<FP,
                                check_addition_invalid_result,
                                check_subtraction_invalid_result,
                                check_division_invalid_result,
                                check_multiplication_invalid_result>;

template<class FP>
using check_inexact_rounding = compose_check<FP,
                                            check_addition_inexact,
                                            check_subtraction_inexact,
                                            check_division_inexact,
                                            check_multiplication_inexact>;

template<class FP>
using check_bothflow = compose_check<FP, check_overflow, check_underflow>;

template<class FP>
using check_all = compose_check<FP,
                                check_overflow,
                                check_underflow,
                                check_inexact_rounding,
                                check_invalid_result,
                                check_division_by_zero>;
}
}
}

#endif // BOOST_SAFE_FLOAT_CONVENIENCE_HPP
