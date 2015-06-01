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
#include <boost/safe_float/policy/check_addition_overflow.hpp>
#include <boost/safe_float/policy/check_addition_inexact.hpp>

//types to be tested
using test_types=boost::mpl::list<
    float, double, long double
>;

using namespace boost::safe_float;

/**
  This test suite checks different policies on addition operations using default parameters for the other policies.
  */
BOOST_AUTO_TEST_SUITE( safe_float_addition_test_suite )
BOOST_AUTO_TEST_SUITE( safe_float_addition_overflow_test_suite )

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_addition_throws_on_overflow, FPT, test_types){
    // define two FPT numbers suppose to positive overflow
    FPT a = std::numeric_limits<FPT>::max();
    FPT b = std::numeric_limits<FPT>::max();
    // check FPT overflows to inf after add
    BOOST_CHECK(isinf(a+b));

    // construct safe_float version of the same two numbers
    safe_float<FPT, policy::check_addition_overflow> c(std::numeric_limits<FPT>::max());
    safe_float<FPT, policy::check_addition_overflow> d(std::numeric_limits<FPT>::max());

    // check the addition throws
    BOOST_CHECK_THROW(c+d, std::exception);

    // define two FPT numbers suppose to negative overflow
    FPT e = std::numeric_limits<FPT>::lowest();
    FPT f = std::numeric_limits<FPT>::lowest();
    // check FPT overflows to inf after add
    BOOST_CHECK(isinf(e+f));

    // construct safe_float version of the same two numbers
    safe_float<FPT, policy::check_addition_overflow> g(std::numeric_limits<FPT>::lowest());
    safe_float<FPT, policy::check_addition_overflow> h(std::numeric_limits<FPT>::lowest());

    // check the addition throws
    BOOST_CHECK_THROW(g+h, std::exception);

}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_addition_inexact, FPT, test_types){
    // define two FPT numbers suppose to overflow
    FPT a = 1;
    FPT b = pow(2, std::numeric_limits<FPT>::digits);

    // check adding and substracting b does not obtain a again.
    BOOST_CHECK(a+b-b != a);

    // construct safe_float version of the same two numbers
    safe_float<FPT, policy::check_addition_inexact> c(1);
    safe_float<FPT, policy::check_addition_inexact> d(pow(2, std::numeric_limits<FPT>::digits));

    // check the addition throws
    BOOST_CHECK_THROW(c+d, std::exception);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()


