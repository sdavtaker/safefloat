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
  This test suite checks the numeric limits are the same as the wrapped type unless required.
  */

BOOST_AUTO_TEST_SUITE( safe_float_numeric_limits_suite )
BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_numeric_limits_basic_fp_types, FPT, test_types){
    //define a safe_float with base policies
    using number_type = safe_float<FPT>;

    //check the specialization equal methods and attributes
    BOOST_CHECK(std::numeric_limits<number_type>::is_specialized == std::numeric_limits<FPT>::is_specialized);
    BOOST_CHECK(std::numeric_limits<number_type>::digits == std::numeric_limits<FPT>::digits);
    BOOST_CHECK(std::numeric_limits<number_type>::digits10 == std::numeric_limits<FPT>::digits10);
    BOOST_CHECK(std::numeric_limits<number_type>::max_digits10 == std::numeric_limits<FPT>::max_digits10);
    BOOST_CHECK(std::numeric_limits<number_type>::is_signed == std::numeric_limits<FPT>::is_signed);
    BOOST_CHECK(std::numeric_limits<number_type>::is_integer == std::numeric_limits<FPT>::is_integer);
    BOOST_CHECK(std::numeric_limits<number_type>::radix == std::numeric_limits<FPT>::radix);
    BOOST_CHECK(std::numeric_limits<number_type>::min_exponent == std::numeric_limits<FPT>::min_exponent);
    BOOST_CHECK(std::numeric_limits<number_type>::min_exponent10 == std::numeric_limits<FPT>::min_exponent10);
    BOOST_CHECK(std::numeric_limits<number_type>::max_exponent == std::numeric_limits<FPT>::max_exponent);
    BOOST_CHECK(std::numeric_limits<number_type>::max_exponent10 == std::numeric_limits<FPT>::max_exponent10);
    BOOST_CHECK(std::numeric_limits<number_type>::has_infinity == std::numeric_limits<FPT>::has_infinity);
    BOOST_CHECK(std::numeric_limits<number_type>::has_denorm == std::numeric_limits<FPT>::has_denorm);
    BOOST_CHECK(std::numeric_limits<number_type>::has_denorm_loss == std::numeric_limits<FPT>::has_denorm_loss);
    BOOST_CHECK(std::numeric_limits<number_type>::is_iec559 == std::numeric_limits<FPT>::is_iec559);
    BOOST_CHECK(std::numeric_limits<number_type>::is_bounded == std::numeric_limits<FPT>::is_bounded);
    BOOST_CHECK(std::numeric_limits<number_type>::is_modulo == std::numeric_limits<FPT>::is_modulo);
    BOOST_CHECK(std::numeric_limits<number_type>::traps == std::numeric_limits<FPT>::traps);
    BOOST_CHECK(std::numeric_limits<number_type>::tinyness_before == std::numeric_limits<FPT>::tinyness_before);

    //check for methods that need more thinking before shipping
    BOOST_CHECK(std::numeric_limits<number_type>::is_exact == std::numeric_limits<FPT>::is_exact);
    BOOST_ERROR("MISSED IMPLEMENTATION OF PROPER TEST FOR IS_EXACT");
    BOOST_CHECK(std::numeric_limits<number_type>::has_quiet_NaN == std::numeric_limits<FPT>::has_quiet_NaN);
    BOOST_ERROR("MISSED IMPLEMENTATION OF PROPER TEST FOR HAS_QUIET_NAN");
    BOOST_CHECK(std::numeric_limits<number_type>::has_signaling_NaN == std::numeric_limits<FPT>::has_signaling_NaN);
    BOOST_ERROR("MISSED IMPLEMENTATION OF PROPER TEST FOR HAS_SIGNALING_NAN");
    BOOST_CHECK(std::numeric_limits<number_type>::round_style == std::numeric_limits<FPT>::round_style);
    BOOST_ERROR("MISSED IMPLEMENTATION OF PROPER TEST FOR ROUND_STYLE");
    BOOST_CHECK(std::numeric_limits<number_type>::round_error().get_stored_value() == std::numeric_limits<FPT>::round_error());
    BOOST_ERROR("MISSED IMPLEMENTATION OF PROPER TEST FOR ROUND_ERROR");

    //check the special methods and attributes that are wrapped are internally the same values
    BOOST_CHECK(std::numeric_limits<number_type>::min().get_stored_value() == std::numeric_limits<FPT>::min());
    BOOST_CHECK(std::numeric_limits<number_type>::max().get_stored_value() == std::numeric_limits<FPT>::max());
    BOOST_CHECK(std::numeric_limits<number_type>::lowest().get_stored_value() == std::numeric_limits<FPT>::lowest());
    BOOST_CHECK(std::numeric_limits<number_type>::epsilon().get_stored_value() == std::numeric_limits<FPT>::epsilon());
    BOOST_CHECK(std::numeric_limits<number_type>::infinity().get_stored_value() == std::numeric_limits<FPT>::infinity());
    BOOST_CHECK(std::numeric_limits<number_type>::quiet_NaN().get_stored_value() == std::numeric_limits<FPT>::quiet_NaN());
    BOOST_CHECK(std::numeric_limits<number_type>::signaling_NaN().get_stored_value() == std::numeric_limits<FPT>::signaling_NaN());
    BOOST_CHECK(std::numeric_limits<number_type>::denorm_min().get_stored_value() == std::numeric_limits<FPT>::denorm_min());
}

BOOST_AUTO_TEST_SUITE_END() // policy



