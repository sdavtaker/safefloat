/**
 * Copyright (c) 2013-2015, Damian Vicino
 * Carleton University, Universite de Nice-Sophia Antipolis
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


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
    // define two FPT numbers suppose to overflow
    FPT a = std::numeric_limits<FPT>::max();
    FPT b = std::numeric_limits<FPT>::max();
    // check FPT overflows to inf after add
    BOOST_CHECK(isinf(a+b));

    // construct safe_float version of the same two numbers
    safe_float<FPT, policy::check_addition_overflow> c(std::numeric_limits<FPT>::max());
    safe_float<FPT, policy::check_addition_overflow> d(std::numeric_limits<FPT>::max());

    // check the addition throws
    BOOST_CHECK_THROW(c+d, std::exception);
}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_addition_reversible, FPT, test_types){
    // define two FPT numbers suppose to overflow
    FPT a = 1;
    FPT b = pow(2, std::numeric_limits<FPT>::digits);

    // check adding and substracting b does not obtain a again.
    BOOST_CHECK(a+b-b != a);

    // construct safe_float version of the same two numbers
    safe_float<FPT, policy::check_addition_reversible> c(1);
    safe_float<FPT, policy::check_addition_reversible> d(pow(2, std::numeric_limits<FPT>::digits));

    // check the addition throws
    BOOST_CHECK_THROW(c+d, std::exception);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()


