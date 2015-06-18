#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/protect.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/list.hpp>


#include <cmath>
#include <limits>


#include <boost/safe_float.hpp>
#include <boost/safe_float/convenience.hpp>

//types to be tested
using test_types=boost::mpl::list<
    float, double, long double
>;

using namespace boost::safe_float;

/**
  This test suite checks the methods providing casting.
  */

BOOST_AUTO_TEST_SUITE( safe_float_casting_test_suite )

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_get_stored_value, FPT, test_types){
    //set initial values
    FPT a = std::numeric_limits<FPT>::max();
    FPT b = std::numeric_limits<FPT>::min();
    FPT c = std::numeric_limits<FPT>::infinity();
    FPT d = 0;
    FPT e = 1;
    //create safe version of the values
    safe_float<FPT> sa(std::numeric_limits<FPT>::max());
    safe_float<FPT> sb(std::numeric_limits<FPT>::min());
    safe_float<FPT> sc(std::numeric_limits<FPT>::infinity());
    safe_float<FPT> sd(0);
    safe_float<FPT> se(1);
    //check the values match when obtaining the stored value
    BOOST_CHECK_EQUAL(a, sa.get_stored_value());
    BOOST_CHECK_EQUAL(b, sb.get_stored_value());
    BOOST_CHECK_EQUAL(c, sc.get_stored_value());
    BOOST_CHECK_EQUAL(d, sd.get_stored_value());
    BOOST_CHECK_EQUAL(e, se.get_stored_value());
}

BOOST_AUTO_TEST_SUITE_END()


