#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/protect.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/list.hpp>


#include <cmath>
#include <boost/safe_float.hpp>
#include <boost/safe_float/convenience.hpp>
#include <boost/safe_float/policy/check_subtraction_overflow.hpp>
#include <boost/safe_float/policy/check_subtraction_underflow.hpp>
#include <boost/safe_float/policy/check_subtraction_inexact.hpp>
#include <boost/safe_float/policy/check_subtraction_invalid_result.hpp>

//types to be tested
using test_types=boost::mpl::list<
    float, double, long double
>;

using namespace boost::safe_float;

/**
  This test suite checks different policies on subtraction operations using default parameters for the other policies.
  */
BOOST_AUTO_TEST_SUITE( safe_float_subtraction_test_suite )

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_subtraction_throws_on_overflow, FPT, test_types){
    // define two FPT numbers suppose to positive overflow
    FPT a = std::numeric_limits<FPT>::max();
    FPT b = std::numeric_limits<FPT>::lowest();
    // check FPT overflows to inf after subtract
    BOOST_CHECK(isinf(a-b));

    // construct safe_float version of the same two numbers
    safe_float<FPT, policy::check_subtraction_overflow> c(std::numeric_limits<FPT>::max());
    safe_float<FPT, policy::check_subtraction_overflow> d(std::numeric_limits<FPT>::lowest());

    // check the subtraction throws
    BOOST_CHECK_THROW(c-d, std::exception);

    // define two FPT numbers suppose to negative overflow
    FPT e = std::numeric_limits<FPT>::lowest();
    FPT f = std::numeric_limits<FPT>::max();
    // check FPT overflows to inf after add
    BOOST_CHECK(isinf(e-f));

    // construct safe_float version of the same two numbers
    safe_float<FPT, policy::check_subtraction_overflow> g(std::numeric_limits<FPT>::lowest());
    safe_float<FPT, policy::check_subtraction_overflow> h(std::numeric_limits<FPT>::max());

    // check the subtraction throws
    BOOST_CHECK_THROW(g-h, std::exception);
}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_subtraction_inexact_rounding, FPT, test_types){
    // define two FPT numbers suppose to round the result inexactly
    FPT a = std::numeric_limits<FPT>::min();
    FPT b = pow(2, std::numeric_limits<FPT>::digits);

    // check substracting a from b is a new value.
    BOOST_CHECK(b-a == b);

    // construct safe_float version of the same two numbers
    safe_float<FPT, policy::check_subtraction_inexact> c(std::numeric_limits<FPT>::min());
    safe_float<FPT, policy::check_subtraction_inexact> d(pow(2, std::numeric_limits<FPT>::digits));

    // check the subtraction throws
    BOOST_CHECK_THROW(d-c, std::exception);
}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_subtraction_underflow, FPT, test_types){
    // define two FPT numbers suppose to underflow
    FPT a, b, c;
    if (std::is_same<FPT, double>()) {
        a =  2.2250738585072019e-308;
        b =  2.2250738585072014e-308;
        //check the subtraction produces an denormal result (considered underflow)
        c = a - b;
        BOOST_CHECK( std::fpclassify( c ) == FP_SUBNORMAL ) ;

        // construct safe_float version of the same two numbers
        safe_float<FPT, policy::check_subtraction_underflow> d(2.2250738585072019e-308);
        safe_float<FPT, policy::check_subtraction_underflow> e(2.2250738585072014e-308);

        // check the subtraction throws
        BOOST_CHECK_THROW(d-e, std::exception);
    } else {
        BOOST_ERROR("underflow test only implemented for double so far");
    }
}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_subtraction_invalid_result, FPT, test_types){
    // define two FPT numbers suppose to produce a NAN
    FPT a = std::numeric_limits<FPT>::infinity();
    FPT b = std::numeric_limits<FPT>::infinity();

    // check adding produced NaN
    BOOST_CHECK(isnan(a-b));

    // construct safe_float version of the same two numbers
    safe_float<FPT, policy::check_subtraction_invalid_result> c(std::numeric_limits<FPT>::infinity());
    safe_float<FPT, policy::check_subtraction_invalid_result> d((std::numeric_limits<FPT>::infinity()));

    // check the subtraction throws
    BOOST_CHECK_THROW(c-d, std::exception);
}


BOOST_AUTO_TEST_SUITE_END()


