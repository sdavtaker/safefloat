#include <boost/safe_float.hpp>
#include <iostream>
#include <limits>

using namespace boost::safe_float;
using namespace std;

int main(){
    double large = numeric_limits<double>::max();
    double small = numeric_limits<double>::min();
    //when dividing a small number by a large number, float can underflow to zero
    double uf = small / large;
    //this is done silently, even when this number is reused as a divisor
    double r = 5/uf;
    //producing an unexpected "infinity result"
    cout << "Without safe_float, 5 / (small/large) = " << r << endl;

    //safe float can be used for catching these unexpected behaviors and others
    safe_float<double> sf_large = numeric_limits<double>::max();
    safe_float<double> sf_small = numeric_limits<double>::min();
    try {
        safe_float<double> sf_uf = sf_small / sf_large;
    } catch (const std::exception& e) {
        cout << "sf_small / sf_large produced an exception because of the underflow to zero" << endl;
    }
    //setting sf_uf to zero
    safe_float<double> sf_uf = 0.0f;
    try {
        safe_float<double> sf_r = safe_float<double>(5.0f) / sf_uf;
    } catch (const std::exception& e) {
        cout << "5 / 0 produced an exception because of division by zero" << endl;
    }

    return 0;
}
