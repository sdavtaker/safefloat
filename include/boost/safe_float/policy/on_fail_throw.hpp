#ifndef BOOST_SAFE_FLOAT_POLICY_THROW_ON_FAIL_HPP
#define BOOST_SAFE_FLOAT_POLICY_THROW_ON_FAIL_HPP
namespace boost {
namespace safe_float{
namespace policy{

class on_fail_throw {
public:
    virtual void report_failure(){
        throw std::exception();
    }
};

}
}
}
#endif // BOOST_SAFE_FLOAT_POLICY_THROW_ON_FAIL_HPP
