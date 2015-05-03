#ifndef BOOST_SAFE_FLOAT_POLICY_CHECK_ADDITION_REVERSIBLE_HPP
#define BOOST_SAFE_FLOAT_POLICY_CHECK_ADDITION_REVERSIBLE_HPP
namespace boost {
namespace safe_float{
namespace policy{

template<class FP>
class check_addition_reversible {
    FP prev_l=0;
    FP prev_r=0;
public:
    virtual bool pre_addition_check(const FP& lhs, const FP& rhs){
        prev_l = lhs;
        prev_r = rhs;
        return true;
    }

    virtual bool post_addition_check(const FP& rhs){
        return (rhs - prev_r) == prev_l;
    }

};

}
}
}
#endif // BOOST_SAFE_FLOAT_POLICY_CHECK_ADDITION_REVERSIBLE_HPP
