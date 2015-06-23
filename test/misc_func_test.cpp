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
#include <sstream>
#include <boost/safe_float.hpp>
#include <boost/safe_float/convenience.hpp>
#include <boost/safe_float/policy/check_addition_overflow.hpp>
#include <boost/safe_float/policy/check_addition_underflow.hpp>
#include <boost/safe_float/policy/check_addition_inexact.hpp>
#include <boost/safe_float/policy/check_addition_invalid_result.hpp>

//types to be tested
using test_types=boost::mpl::list<
    float, double, long double
>;

using namespace boost::safe_float;

/**
  This test suite checks different policies on addition operations using default parameters for the other policies.
  */
BOOST_AUTO_TEST_SUITE( safe_float_misc_functions_test_suite )

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_istream, FPT, test_types){
    FPT f = std::numeric_limits<FPT>::max();
    safe_float<FPT> sf;

    std::stringstream ssfp;
    ssfp.precision(std::numeric_limits<FPT>::digits10);
    ssfp << f;
    ssfp >> sf;

    BOOST_CHECK_EQUAL(sf.get_stored_value(), f);
    BOOST_ERROR("THIS TEST IS FAILING BECAUSE INFORMATION IS LOST IN THE STREAM, CHECK THE STREAM");
}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_ostream, FPT, test_types){
    FPT f = std::numeric_limits<FPT>::max();
    safe_float<FPT> sf = std::numeric_limits<FPT>::max();
    std::stringstream ssfp, sfp;
    ssfp << sf;
    sfp << f;
    BOOST_CHECK_EQUAL(ssfp.str(), sfp.str());
}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_comparison_operations, FPT, test_types){
    //comparison operations are not expected to require any policy check
    //comparison is expected to behave as the internal type behaves
    safe_float<FPT> zero = 0.0f;
    safe_float<FPT> max = std::numeric_limits<FPT>::max();
    safe_float<FPT> min = std::numeric_limits<FPT>::min();

    BOOST_CHECK( min <  max);
    BOOST_CHECK( zero <= min);
    BOOST_CHECK( min > zero);
    BOOST_CHECK( max >=  zero);
    BOOST_CHECK( zero ==  zero);
    BOOST_CHECK( min !=  max);
}


BOOST_AUTO_TEST_SUITE_END()

