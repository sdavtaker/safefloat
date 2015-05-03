#ifndef BOOST_SAFE_FLOAT_POLICY_CHECK_ADDITION_OVERFLOW_HPP
#define BOOST_SAFE_FLOAT_POLICY_CHECK_ADDITION_OVERFLOW_HPP
namespace boost {
namespace safe_float{
namespace policy{

template<class FP>
class check_addition_overflow {
    bool precond=true;
public:
    virtual bool pre_addition_check(const FP& lhs, const FP& rhs){
        precond = std::isinf(lhs) || std::isinf(rhs);
        return true;
    }
    virtual bool post_addition_check(const FP& rhs){
        return !precond && !std::isinf(rhs);
    }

};

}
}
}
#endif // BOOST_SAFE_FLOAT_POLICY_CHECK_ADDITION_OVERFLOW_HPP
