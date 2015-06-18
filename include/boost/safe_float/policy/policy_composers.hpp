#ifndef BOOST_SAFE_FLOAT_POLICY_CHECK_COMPOSERS_HPP
#define BOOST_SAFE_FLOAT_POLICY_CHECK_COMPOSERS_HPP

#include<algorithm>

#include <boost/safe_float/policy/check_base_policy.hpp>
//this file define composers for policies

namespace boost {
namespace safe_float{
namespace policy{

//check_composer
template<class FP, template<class> class A, template<class> class... As>
class compose_check : public check_policy<FP>, private A<FP>, private As<FP>...
{
                //TODO add static check for As to be va;id check Policies.
public:
    //operator+
    virtual bool pre_addition_check(const FP& lhs, const FP& rhs){
        using expand = int[];
        expand e = { true, ( As<FP>::pre_addition_check(lhs, rhs) )... };
        return A<FP>::pre_addition_check(lhs, rhs) &&
                std::all_of(std::begin(e), std::end(e), [](bool i){ return i; });
    }

    virtual bool post_addition_check(const FP& value){
        using expand = int[];
        expand e = { true, ( As<FP>::post_addition_check(value) )... };
        return A<FP>::post_addition_check(value) &&
                std::all_of(std::begin(e), std::end(e), [](bool i){ return i; });
    }

    virtual std::string addition_failure_message() {
        //TODO: find out the message from the policy broken
        return std::string("Policy broken when adding");
    }

    //operator-
    virtual bool pre_subtraction_check(const FP& lhs, const FP& rhs){
        using expand = int[];
        expand e = { true, ( As<FP>::pre_subtraction_check(lhs, rhs) )... };
        return A<FP>::pre_subtraction_check(lhs, rhs) &&
                std::all_of(std::begin(e), std::end(e), [](bool i){ return i; });
    }

    virtual bool post_subtraction_check(const FP& value){
        using expand = int[];
        expand e = { true, ( As<FP>::post_subtraction_check(value) )... };
        return A<FP>::post_subtraction_check(value) &&
                std::all_of(std::begin(e), std::end(e), [](bool i){ return i; });
    }

    virtual std::string subtraction_failure_message() {
        //TODO: find out the message from the policy broken
        return std::string("Policy broken when subtracting");
    }

    //operator*
    virtual bool pre_multiplication_check(const FP& lhs, const FP& rhs){
        using expand = int[];
        expand e = { true, ( As<FP>::pre_multiplication_check(lhs, rhs) )... };
        return A<FP>::pre_multiplication_check(lhs, rhs) &&
                std::all_of(std::begin(e), std::end(e), [](bool i){ return i; });
    }

    virtual bool post_multiplication_check(const FP& value){
        using expand = int[];
        expand e = { true, ( As<FP>::post_multiplication_check(value) )... };
        return A<FP>::post_multiplication_check(value) &&
                std::all_of(std::begin(e), std::end(e), [](bool i){ return i; });
    }

    virtual std::string multiplication_failure_message() {
        //TODO: find out the message from the policy broken
        return std::string("Policy broken when multiplying");
    }

    //operator/
    virtual bool pre_division_check(const FP& lhs, const FP& rhs){
        using expand = int[];
        expand e = { true, ( As<FP>::pre_division_check(lhs, rhs) )... };
        return A<FP>::pre_division_check(lhs, rhs) &&
                std::all_of(std::begin(e), std::end(e), [](bool i){ return i; });
    }

    virtual bool post_division_check(const FP& value){
        using expand = int[];
        expand e = { true, ( As<FP>::post_division_check(value) )... };
        return A<FP>::post_division_check(value) &&
                std::all_of(std::begin(e), std::end(e), [](bool i){ return i; });
    }

    virtual std::string division_failure_message() {
        //TODO: find out the message from the policy broken
        return std::string("Policy broken when dividing");
    }

};

//on_fail_composer

//cast_composer

}
}
}




template<class FP>
class check_policy {
public:
    //operator+
    virtual bool pre_addition_check(const FP& lhs, const FP& rhs){return true;}
    virtual bool post_addition_check(const FP& value){return true;}
    virtual std::string addition_failure_message() { return std::string("Failed to add");}
    //operator-
    virtual bool pre_subtraction_check(const FP& lhs, const FP& rhs){return true;}
    virtual bool post_subtraction_check(const FP& value){return true;}
    virtual std::string subtraction_failure_message() { return std::string("Failed to subtract");}
    //operator*
    virtual bool pre_multiplication_check(const FP& lhs, const FP& rhs){return true;}
    virtual bool post_multiplication_check(const FP& value){return true;}
    virtual std::string multiplication_failure_message() { return std::string("Failed to multiply");}
    //operator/
    virtual bool pre_division_check(const FP& lhs, const FP& rhs){return true;}
    virtual bool post_division_check(const FP& value){return true;}
    virtual std::string division_failure_message() { return std::string("Failed to divide");}

    virtual ~check_policy(){}
};

#endif // BOOST_SAFE_FLOAT_POLICY_CHECK_COMPOSERS_HPP

