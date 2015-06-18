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
#include <boost/safe_float.hpp>

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

BOOST_AUTO_TEST_SUITE( safe_float_check_combined_policies_test_suite ) //check composed policies
BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_check_all_overflows_combined, FPT, test_types){
    safe_float<FPT, policy::check_overflow> max = std::numeric_limits<FPT>::max(); //max+max -> OV
    safe_float<FPT, policy::check_overflow> min = std::numeric_limits<FPT>::min();  // max/min  -> OV
    safe_float<FPT, policy::check_overflow> lowest = std::numeric_limits<FPT>::lowest();  // max-lowest  -> OV

    BOOST_CHECK_THROW(max+max, std::exception);
    BOOST_CHECK_THROW(max-lowest, std::exception);
    BOOST_CHECK_THROW(max*max, std::exception);
    BOOST_CHECK_THROW(max/min, std::exception);
}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_check_all_underflows_combined, FPT, test_types){
    if (std::is_same<FPT, double>()) {
        FPT a =  2.2250738585072019e-308;
        FPT b = -2.2250738585072014e-308;
        //check the addition produces an denormal result (considered underflow)
        FPT c = a + b;
        BOOST_CHECK( std::fpclassify( c ) == FP_SUBNORMAL ) ;

        // construct safe_float version of the same two numbers
        safe_float<FPT, policy::check_underflow> d(2.2250738585072019e-308);
        safe_float<FPT, policy::check_underflow> e(-2.2250738585072014e-308);
        safe_float<FPT, policy::check_underflow> ne(2.2250738585072014e-308);

        // check the addition throws
        BOOST_CHECK_THROW(d+e, std::exception);

        //check subtraction throws
        BOOST_CHECK_THROW(d-ne, std::exception);

        //check multiplication underflow throws
        BOOST_ERROR("underflow test not implemented for multiplication yet");

        //check division underflow to zero
        safe_float<FPT, policy::check_underflow> max = std::numeric_limits<FPT>::max(); // min/max -> UF
        safe_float<FPT, policy::check_underflow> min = std::numeric_limits<FPT>::min();  // min/max  -> UF
        BOOST_CHECK_THROW(min/max, std::exception);

    } else {
        BOOST_ERROR("underflow test only implemented for double so far");
    }
}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_check_all_inexactity_combined, FPT, test_types){
    //addition check
    safe_float<FPT, policy::check_inexact_rounding> a(1);
    safe_float<FPT, policy::check_inexact_rounding> b(pow(2, std::numeric_limits<FPT>::digits));
    BOOST_CHECK_THROW(a+b, std::exception);
    //subtraction check
    safe_float<FPT, policy::check_inexact_rounding> c(std::numeric_limits<FPT>::min());
    safe_float<FPT, policy::check_inexact_rounding> d(pow(2, std::numeric_limits<FPT>::digits));
    BOOST_CHECK_THROW(d-c, std::exception);
    BOOST_ERROR("TEST NOT IMPLEMENTED FOR MULTIPLICATION");
    BOOST_ERROR("TEST NOT IMPLEMENTED FOR DIVISION");
}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_check_all_invality_combined, FPT, test_types){
    //addition check
    safe_float<FPT, policy::check_invalid_result> a(std::numeric_limits<FPT>::infinity());
    safe_float<FPT, policy::check_invalid_result> b(-(std::numeric_limits<FPT>::infinity()));
    BOOST_CHECK_THROW(a+b, std::exception);
    //subtraction check
    safe_float<FPT, policy::check_invalid_result> c(std::numeric_limits<FPT>::infinity());
    safe_float<FPT, policy::check_invalid_result> d((std::numeric_limits<FPT>::infinity()));
    BOOST_CHECK_THROW(c-d, std::exception);
    //multiplication check
    safe_float<FPT, policy::check_invalid_result> e(std::numeric_limits<FPT>::infinity());
    safe_float<FPT, policy::check_invalid_result> f(0);
    BOOST_CHECK_THROW(e*f, std::exception);
    //division check
    safe_float<FPT, policy::check_invalid_result> g(std::numeric_limits<FPT>::infinity());
    safe_float<FPT, policy::check_invalid_result> h(std::numeric_limits<FPT>::infinity());
    BOOST_CHECK_THROW(g/h, std::exception);
}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_check_bothflows_combined, FPT, test_types){
    safe_float<FPT, policy::check_bothflow> max = std::numeric_limits<FPT>::max(); //max+max -> OV
    safe_float<FPT, policy::check_bothflow> min = std::numeric_limits<FPT>::min();  // max/min  -> OV
    safe_float<FPT, policy::check_bothflow> lowest = std::numeric_limits<FPT>::lowest();  // max-lowest  -> OV

    BOOST_CHECK_THROW(max+max, std::exception);
    BOOST_CHECK_THROW(max-lowest, std::exception);
    BOOST_CHECK_THROW(max*max, std::exception);
    BOOST_CHECK_THROW(max/min, std::exception);

    if (std::is_same<FPT, double>()) {
        FPT a =  2.2250738585072019e-308;
        FPT b = -2.2250738585072014e-308;
        //check the addition produces an denormal result (considered underflow)
        FPT c = a + b;
        BOOST_CHECK( std::fpclassify( c ) == FP_SUBNORMAL ) ;

        // construct safe_float version of the same two numbers
        safe_float<FPT, policy::check_underflow> d(2.2250738585072019e-308);
        safe_float<FPT, policy::check_underflow> e(-2.2250738585072014e-308);
        safe_float<FPT, policy::check_underflow> ne(2.2250738585072014e-308);

        // check the addition throws
        BOOST_CHECK_THROW(d+e, std::exception);

        //check subtraction throws
        BOOST_CHECK_THROW(d-ne, std::exception);
    } else {
        BOOST_ERROR("underflow test only implemented for double so far");
    }
}


BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_check_all_combined, FPT, test_types){
    //addition overflow
    safe_float<FPT, policy::check_all> max = std::numeric_limits<FPT>::max(); //max+max -> OV
    BOOST_CHECK_THROW(max+max, std::exception);
    //subtraction inexact result
    safe_float<FPT, policy::check_all> a(std::numeric_limits<FPT>::min());
    safe_float<FPT, policy::check_all> b(pow(2, std::numeric_limits<FPT>::digits));
    BOOST_CHECK_THROW(a-b, std::exception);
    //multiplication invalid result
    safe_float<FPT, policy::check_all> c(std::numeric_limits<FPT>::infinity());
    safe_float<FPT, policy::check_all> d(0);
    BOOST_CHECK_THROW(c*d, std::exception);
    //division by zero
    // construct safe_float producing divide by zero
    safe_float<FPT, policy::check_all> e(1);
    safe_float<FPT, policy::check_all> f(0);
    // check the division throws
    BOOST_CHECK_THROW(e/f, std::exception);
}

BOOST_AUTO_TEST_SUITE_END() //check composed policies

BOOST_AUTO_TEST_SUITE_END() //check policy

BOOST_AUTO_TEST_SUITE_END() // policy


