#ifndef BOOST_SAFE_FLOAT_POLICY_THROW_ON_FAIL_HPP
#define BOOST_SAFE_FLOAT_POLICY_THROW_ON_FAIL_HPP
#include <boost/safe_float/policy/on_fail_base_policy.hpp>

namespace boost {
namespace safe_float{
namespace policy{

class on_fail_throw : public on_fail_policy {
public:
    virtual void report_failure(const std::string& s){
        throw std::exception();
    }
};

}
}
}
#endif // BOOST_SAFE_FLOAT_POLICY_THROW_ON_FAIL_HPP
