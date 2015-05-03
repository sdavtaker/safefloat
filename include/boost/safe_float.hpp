#ifndef BOOST_SAFE_FLOAT_HPP
#define BOOST_SAFE_FLOAT_HPP
namespace boost {
namespace safe_float{

//forward declaration
namespace policy {
class check_addition_overflow;
class throw_on_fail;
class cast_none;
}

template<class FP,
         class CHECK=policy::check_addition_overflow,
         class ERROR_HANDLING=policy::throw_on_fail,
         class CAST=policy::cast_none>
class safe_float {
FP number;
public:
    safe_float(FP f){
        number = f;
    }

    safe_float<FP, CHECK, ERROR_HANDLING, CAST>&
    operator+=(const safe_float<FP, CHECK, ERROR_HANDLING, CAST>& rhs)
     {
       // actual addition of rhs to *this
       return *this;
     }
};

//binary operators
template<class FP,
         class CHECK,
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
