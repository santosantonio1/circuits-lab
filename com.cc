#include <iostream>
#include <complex>
#include <array>

using namespace std;

auto par2(const complex<double>& a, 
          const complex<double>& b) -> complex<double> {
    
        return (a*b)/(a+b);
}

/*           c            3
 *          /\            | 
 *         /  \    ->    / \
 *        a----b        1   2
 */
auto DY(const array<complex<double>, 3>& abc) -> array<complex<double>, 3> {
    cout << "Delta (Za, Zb, Zc) = \n";
    cout << abc[0] << ", ";
    cout << abc[1] << ", ";
    cout << abc[2] << ")\n";

    array<complex<double>, 3> res;
    complex<double> sum = abc[0] + abc[1] + abc[2];

    cout << "\n...\n\n";

    res[0] = (abc[1]*abc[2])/sum;
    res[1] = (abc[0]*abc[2])/sum;
    res[2] = (abc[0]*abc[1])/sum;

    cout << "Star: (Z1, Z2, Z3) = (";
    cout << res[0] << ", ";
    cout << res[1] << ", ";
    cout << res[2] << ")\n";

    return res;
}

auto init(const pair<double, double>& a,
          const pair<double, double>& b,
          const pair<double, double>& c) -> array<complex<double>, 3> {

    return array<complex<double>, 3> {
        complex<double>(a.first, a.second),
        complex<double>(b.first, b.second),
        complex<double>(c.first, c.second)
    };
}

int main() {
    complex<double> a(9.75,-2.82), b(6.35,-5.52);

    cout << par2(a,b) << '\n';

    auto abc = init({0,-3}, {0,4}, {8,5});
    DY(abc);
}
