#ifndef BOOST_SAFE_FLOAT_HPP
#define BOOST_SAFE_FLOAT_HPP
#include <boost/safe_float/convenience.hpp>
#include <boost/safe_float/policy/check_addition_overflow.hpp>
#include <boost/safe_float/policy/on_fail_throw.hpp>

namespace boost {
namespace safe_float{

//forward declaration
//namespace policy {
//template <class T>
//class check_addition_overflow;

//class on_fail_throw;
//class cast_none;

//}


template<class FP,
         template <class T> class CHECK=policy::check_addition_overflow,
         class ERROR_HANDLING=policy::on_fail_throw,
         template <class T> class CAST=policy::cast_none>
class safe_float : private CHECK<FP>, ERROR_HANDLING {
FP number;
public:
    safe_float(FP f){
        static_assert(std::is_floating_point<FP>::value, "First template parameter in safe_float has to be floating point data type");
        number = f;
    }

    //Access to internal representation
    FP get_stored_value(){
        return number;
    }

    // unary operators implementation
    safe_float<FP, CHECK, ERROR_HANDLING, CAST>&
    operator+=(const safe_float<FP, CHECK, ERROR_HANDLING, CAST>& rhs)
     {
       this->pre_addition_check(number, rhs.number);
       number += rhs.number;
       if (!this->post_addition_check(number)) this->report_failure(this->addition_failure_message());
       return *this;
     }

    //TODO: implement check policies for operator- and tests
    safe_float<FP, CHECK, ERROR_HANDLING, CAST> operator-() const{
        return safe_float<FP, CHECK, ERROR_HANDLING, CAST>(-number);
    }
};

//binary operators
template<class FP,
         template<class T> class CHECK,
         class ERROR_HANDLING,
         template<class T> class CAST>
inline safe_float<FP, CHECK, ERROR_HANDLING, CAST>
operator+(safe_float<FP, CHECK, ERROR_HANDLING, CAST> lhs,
          const safe_float<FP, CHECK, ERROR_HANDLING, CAST>& rhs)
{
  lhs += rhs;
  return lhs;
}

} //safe_float
} //boost



//Numeric limits specialization
namespace std {

template<class FP,
         template <class T> class CHECK,
         class ERROR_HANDLING,
         template <class T> class CAST>
class numeric_limits <boost::safe_float::safe_float<FP, CHECK, ERROR_HANDLING, CAST>>
{
    using number_type = boost::safe_float::safe_float<FP, CHECK, ERROR_HANDLING, CAST>;
public:
   static constexpr bool is_specialized = true;
   static constexpr int digits = std::numeric_limits<FP>::digits;
   static constexpr int digits10 = std::numeric_limits<FP>::digits10;
   static constexpr int max_digits10 = std::numeric_limits<FP>::max_digits10;
   static constexpr bool is_signed = std::numeric_limits<FP>::is_signed;
   static constexpr bool is_integer = std::numeric_limits<FP>::is_integer;
   static constexpr int radix = std::numeric_limits<FP>::radix;
   static constexpr int min_exponent = std::numeric_limits<FP>::min_exponent;
   static constexpr int min_exponent10 = std::numeric_limits<FP>::min_exponent10;
   static constexpr int max_exponent = std::numeric_limits<FP>::max_exponent;
   static constexpr int max_exponent10 = std::numeric_limits<FP>::max_exponent10;
   static constexpr bool has_infinity = std::numeric_limits<FP>::has_infinity;
   static constexpr float_denorm_style has_denorm = std::numeric_limits<FP>::has_denorm;
   static constexpr bool has_denorm_loss = std::numeric_limits<FP>::has_denorm_loss;
   static constexpr bool is_iec559 = std::numeric_limits<FP>::is_iec559;
   static constexpr bool is_bounded = std::numeric_limits<FP>::is_bounded;
   static constexpr bool is_modulo = std::numeric_limits<FP>::is_modulo;
   static constexpr bool traps = std::numeric_limits<FP>::traps;
   static constexpr bool tinyness_before = std::numeric_limits<FP>::tinyness_before;

   static constexpr bool is_exact = std::numeric_limits<FP>::is_exact; //TODO: check for inexact policies
   static constexpr bool has_quiet_NaN = std::numeric_limits<FP>::has_quiet_NaN; //TODO: check policies for nan
   static constexpr bool has_signaling_NaN = std::numeric_limits<FP>::has_signaling_NaN; //TODO: check policies for nan
   static constexpr float_round_style round_style = std::numeric_limits<FP>::round_style; //TODO: check inexact policies

   static constexpr number_type min() noexcept(std::numeric_limits<FP>::min()) {
       return boost::safe_float::safe_float<FP, CHECK, ERROR_HANDLING, CAST>(
               std::numeric_limits<FP>::min());
   }
   static constexpr number_type max() noexcept(std::numeric_limits<FP>::max()) {
       return boost::safe_float::safe_float<FP, CHECK, ERROR_HANDLING, CAST>(
               std::numeric_limits<FP>::max());
   }
   static constexpr number_type lowest() noexcept(max) {
       return -(max)();
   }
   static constexpr number_type epsilon() noexcept(std::numeric_limits<FP>::epsilon()){
       return  boost::safe_float::safe_float<FP, CHECK, ERROR_HANDLING, CAST>(
                   std::numeric_limits<FP>::epsilon());
   }
   static constexpr number_type round_error() noexcept(std::numeric_limits<FP>::round_error()){ //TODO: check for inexact policies
       return  boost::safe_float::safe_float<FP, CHECK, ERROR_HANDLING, CAST>(
                   std::numeric_limits<FP>::round_error());
   }
   static constexpr number_type infinity() noexcept(std::numeric_limits<FP>::infinity()){
       return  boost::safe_float::safe_float<FP, CHECK, ERROR_HANDLING, CAST>(
                   std::numeric_limits<FP>::infinity());
   }
   static constexpr number_type quiet_NaN() noexcept(std::numeric_limits<FP>::quiet_NaN()){
       return  boost::safe_float::safe_float<FP, CHECK, ERROR_HANDLING, CAST>(
                   std::numeric_limits<FP>::quiet_NaN());
   }
   static constexpr number_type signaling_NaN() noexcept(std::numeric_limits<FP>::signaling_NaN()){
       return  boost::safe_float::safe_float<FP, CHECK, ERROR_HANDLING, CAST>(
                   std::numeric_limits<FP>::signaling_NaN());
   }
   static number_type denorm_min() noexcept(std::numeric_limits<FP>::denorm_min()){
       return  boost::safe_float::safe_float<FP, CHECK, ERROR_HANDLING, CAST>(
                   std::numeric_limits<FP>::denorm_min());
   }
};

} //std


#endif // BOOST_SAFE_FLOAT_HPP
