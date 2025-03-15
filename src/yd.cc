#include <iostream>
#include <array>
#include <complex>
#include <regex>
#include <stdexcept>
#include <cmath>
#include <numbers>
using namespace std;

#define __PI__ std::numbers::pi

auto parse(const string& str) -> complex<double> {
    std::smatch match;
    return 
        regex_match(str, match, regex(R"(([-+]?\d*\.?\d+)?([+-]?\d*\.?\d+)([ij]))")) ? complex<double> {
            match[1].str().empty() ? 0.0 : stod(match[1].str()),
            std::stod(match[2].str())
        } :
        regex_match(str, match, regex(R"([+-]?\d+[ij])")) ? complex<double> {
            0.0,
            stod(str.substr(0, str.size() - 1))
        } :
        regex_match(str, match, regex(R"([+-]?\d*\.?\d+)")) ? complex<double> {
            stod(str),
            0.0
        } :
        (str == "j" || str == "i") ? complex<double> {
            0.0,
            1.0
        } : 
        (str == "-j" || str == "-i") ? complex<double> {
            0.0,
            -1.0
        } :
        throw invalid_argument("(!) Error: Invalid complex number format. Try it a+bi or a+bj form\n");
}

auto YD(const array<complex<double>, 3>& abc) -> array<complex<double>, 3> {
    const complex<double> prod = abc[0]*abc[1]+abc[1]*abc[2]+abc[0]*abc[2];
    return {
        prod/abc[0],
        prod/abc[1],
        prod/abc[2]
    };
}

auto polar(const complex<double> &z) -> complex<double> {
    const double phase = atan(abs(z.imag()/z.real()));
    auto deg = [=](const double x) {
        return (x*180)/__PI__;
    };
    return {
        hypot(z.real(), z.imag()),
        deg (
            (z.real() > 0 && z.imag() > 0) ?  phase : 
            (z.real() > 0 && z.imag() < 0) ? -phase :
            (z.real() < 0 && z.imag() > 0) ? __PI__ - phase : __PI__ + phase
        )
    };
}

int main(int argc, char** argv) {
    cout << "---------------------------------------------\n";
    cout << "\tSTAR -> DELTA TRANSFORMATION\n";
    cout << "           3                c\n"; 
    cout << "           |               / \\\n";              
    cout << "          / \\      ->     /   \\\n";
    cout << "         1   2           a-----b";

    if (argc != 4) {
        cerr << "(!) ERROR: you must give 3 impedances\n\n---------------------------------------------\n";
        return 1;
    }

    try {
        const array<complex<double>, 3> abc = {
            parse(argv[1]),
            parse(argv[2]),
            parse(argv[3])
        };

        cout << "> [STAR] (Za, Zb, Zc) = (";
        cout << abc[0] << ", ";
        cout << abc[1] << ", ";
        cout << abc[2] << ")\n";

        cout << "\n...\n\n";

        const auto res = YD(abc);

        cout << "> [DELTA] (Z1, Z2, Z3) = (";
        cout << res[0] << ", ";
        cout << res[1] << ", ";
        cout << res[2] << ")\n";

        cout << "\n> [POLAR] : ";
        cout << polar(res[0]) << ' ';
        cout << polar(res[1]) << ' ';
        cout << polar(res[2]) << '\n';
        cout << "\n\n---------------------------------------------\n";
    }
    catch (const exception& e) {
        cerr << e.what() << "\n\n---------------------------------------------\n";
    }

    return 0;
}