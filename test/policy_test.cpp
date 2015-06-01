#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/protect.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/list.hpp>


#include <cmath>

#include <boost/safe_float/policy/check_addition_overflow.hpp>

//types to be tested
using test_types=boost::mpl::list<
    float, double, long double
>;

using namespace boost::safe_float;

/**
  This test suite checks the methods of each policy and their composition.
  */

BOOST_AUTO_TEST_SUITE( safe_float_policy_test_suite )
BOOST_AUTO_TEST_SUITE( safe_float_check_policy_test_suite )

BOOST_AUTO_TEST_SUITE( safe_float_check_addition_policy_test_suite )
BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_check_addition_overflow, FPT, test_types){
    //define policy
    policy::check_addition_overflow<FPT> check;
    //invalid precheck returns true on both checks
    BOOST_CHECK(check.pre_addition_check(std::numeric_limits<FPT>::infinity(), (FPT) 1));
    BOOST_CHECK(check.post_addition_check(std::numeric_limits<FPT>::infinity()));
    BOOST_CHECK(check.post_addition_check((FPT) 1));

    BOOST_CHECK(check.pre_addition_check((FPT) 1, std::numeric_limits<FPT>::infinity()));
    BOOST_CHECK(check.post_addition_check(std::numeric_limits<FPT>::infinity()));
    BOOST_CHECK(check.post_addition_check((FPT) 1));

    BOOST_CHECK(check.pre_addition_check(std::numeric_limits<FPT>::infinity(), std::numeric_limits<FPT>::infinity()));
    BOOST_CHECK(check.post_addition_check(std::numeric_limits<FPT>::infinity()));
    BOOST_CHECK(check.post_addition_check((FPT) 1));

    //accept precheck & fail postcheck returns false on post check
    BOOST_CHECK(check.pre_addition_check((FPT) 1, (FPT) 1));
    BOOST_CHECK(! check.post_addition_check(std::numeric_limits<FPT>::infinity()));

    //accept precheck & accept postcheck
    BOOST_CHECK(check.pre_addition_check((FPT) 1, (FPT) 1));
    BOOST_CHECK(check.post_addition_check((FPT) 2));

    //check error message
    BOOST_CHECK_EQUAL(check.addition_failure_message(), std::string("Overflow to infinite on addition operation"));
}

BOOST_AUTO_TEST_SUITE_END() //check addition policy

BOOST_AUTO_TEST_SUITE_END() //check policy

BOOST_AUTO_TEST_SUITE_END() // policy


