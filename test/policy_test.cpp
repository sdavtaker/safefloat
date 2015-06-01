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
BOOST_AUTO_TEST_SUITE( safe_float_policy_addition_overflow_test_suite )

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_addition_throws_on_overflow, FPT, test_types){

    //define policy

    //fail precheck

    //fail postcheck
    BOOST_FAIL("UNIMPLEMENTED TEST");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()


