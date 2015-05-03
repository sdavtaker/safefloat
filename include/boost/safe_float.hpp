#ifndef BOOST_SAFE_FLOAT_HPP
#define BOOST_SAFE_FLOAT_HPP

namespace boost {
namespace safe_float{

//forward declaration
namespace policy {
template <class T>
class check_addition_overflow;

class throw_on_fail;
class cast_none;
}

template<class FP,
         template <class T> class CHECK=policy::check_addition_overflow,
         class ERROR_HANDLING=policy::throw_on_fail,
         class CAST=policy::cast_none>
class safe_float : private CHECK<FP>, ERROR_HANDLING {
FP number;
public:
    safe_float(FP f){
        static_assert(std::is_floating_point<FP>::value, "First template parameter in safe_float has to be floating point data type");
        number = f;
    }

    safe_float<FP, CHECK, ERROR_HANDLING, CAST>&
    operator+=(const safe_float<FP, CHECK, ERROR_HANDLING, CAST>& rhs)
     {
       this->pre_addition_check(number, rhs.number);
       number += rhs.number;
       if (!this->post_addition_check(number)) this->report_failure();
       return *this;
     }
};

//binary operators
template<class FP,
         template<class T> class CHECK,
         class ERROR_HANDLING,
         class CAST>
inline safe_float<FP, CHECK, ERROR_HANDLING, CAST>
operator+(safe_float<FP, CHECK, ERROR_HANDLING, CAST> lhs,
          const safe_float<FP, CHECK, ERROR_HANDLING, CAST>& rhs)
{
  lhs += rhs;
  return lhs;
}

}
}
#endif // BOOST_SAFE_FLOAT_HPP
