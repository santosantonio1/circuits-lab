#include <iostream>
#include <array>
#include <algorithm>
#include <complex>
#include <regex>
#include <stdexcept>
#include <sstream>
using namespace std;

// GPT THE GOAT
std::complex<double> parse(const std::string& str) {
    // Handle case with both real and imaginary parts (i/j)
    std::regex pattern(R"(([-+]?\d*\.?\d+)?([+-]?\d*\.?\d+)([ij]))");
    std::smatch match;

    // Matching complex numbers with both real and imaginary parts
    if (std::regex_match(str, match, pattern)) {
        double real = match[1].str().empty() ? 0.0 : std::stod(match[1].str());
        double imag = std::stod(match[2].str());

        return std::complex<double>(real, imag);
    } 
    // Handle purely imaginary numbers (e.g. "3j" or "-5j")
    else if (std::regex_match(str, match, std::regex(R"([+-]?\d+[ij])"))) {
        double imag = std::stod(str.substr(0, str.size() - 1));  // Remove 'j' or 'i'
        return std::complex<double>(0.0, imag);
    } 
    // Handle pure real numbers (e.g. "4" or "-2")
    else if (std::regex_match(str, match, std::regex(R"([+-]?\d*\.?\d+)"))) {
        double real = std::stod(str);
        return std::complex<double>(real, 0.0);
    } 
    // Handle cases where only "j" or "i" is provided (including negative j or i)
    else if (str == "j" || str == "i") {
        return std::complex<double>(0.0, 1.0); // Purely imaginary number
    }
    else if (str == "-j" || str == "-i") {
        return std::complex<double>(0.0, -1.0); // Purely imaginary number with negative sign
    }
    // Handle invalid format
    else {
        throw std::invalid_argument("(!) Error: Invalid complex number format. Try it a+bi or a+bj form\n");
    }
}

auto DY(const array<complex<double>, 3>& abc) -> array<complex<double>, 3> {
     const complex<double> sum = abc[0] + abc[1] + abc[2]; 
     return {
        (abc[1]*abc[2])/sum,
        (abc[0]*abc[2])/sum,
        (abc[0]*abc[1])/sum
     };
}

int main(int argc, char** argv) {
    cout << "---------------------------------------------\n";
    cout << "\tDELTA -> STAR TRANSFORMATION\n";
    cout << "            c             3\n";
    cout << "           / \\            |\n";
    cout << "          /   \\    ->    / \\\n";
    cout << "         a-----b        1   2\n\n";
    
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

        cout << "> [DELTA] (Za, Zb, Zc) = (";
        cout << abc[0] << ", ";
        cout << abc[1] << ", ";
        cout << abc[2] << ")\n";

        cout << "\n...\n\n";

        const auto res = DY(abc);

        cout << "> [STAR] (Z1, Z2, Z3) = (";
        cout << res[0] << ", ";
        cout << res[1] << ", ";
        cout << res[2] << ")\n";
        cout << "\n\n---------------------------------------------\n";
    }
    catch (const exception& e) {
        cerr << e.what() << "\n\n---------------------------------------------\n";
    }

    return 0;
}
