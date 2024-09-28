#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

std::vector<double> gauss(std::vector<std::vector<double>>& m,
                          std::vector<double>& b)
{
    const size_t n = b.size();

    // elimination 
    for(size_t i=0; i<n; i++)
    {
        for(size_t j=i+1; j<n; j++)
        {
            if(m[j][i] == 0) continue;
            double r = m[i][i]/m[j][i];
            b[j] *= r;
            b[j] -= b[i];

            for(size_t k=0; k<n; k++) 
            {
                m[j][k] *= r;
                m[j][k] -= m[i][k];
            }
        }
    }

    // backsubstitution
    b[n-1] /= m[n-1][n-1];
    m[n-1][n-1] /= m[n-1][n-1];

    for(size_t i=n-2; i>=0 && n>1; i--)
    {
        for(size_t j=i+1; j<n; j++)
        {
            if(m[i][j] == 0) continue;
            double r = m[i][j];
            m[i][j] -= r*m[j][j];
            b[i] -= r*b[j];
        }

        b[i] /= m[i][i];
        m[i][i] /= m[i][i];

        // size_t >=0 -> 0-1 > 0 for size_t...
        if(i==0) break;
    }

    return b;
}

template<typename T>
void print(const std::vector<std::vector<T>>& m,
           const std::vector<T>& b) {
    
    const size_t n = b.size();
    for(size_t i=0; i<n; i++) {
        
        for(size_t j=0; j<n; j++) {

            cout << ' ' << m[i][j];

        }

        cout << ' ' << b[i] << '\n';
    }

}

int main(int argc, char** argv) {
    
    size_t n, x;
    cin >> n;

    std::vector<std::vector<double>> m(n);
    std::vector<double> b(n);
    for(size_t i=0; i<n; i++) m[i].resize(n);

    for(size_t i=0; i<n; i++) {
        
        for(size_t j=0; j<n; j++) {

            cin >> m[i][j];

        }

        cin >> b[i];
    }

    const auto sol = gauss(m, b);
    
    cout << "solution X[] = ";

    for(const auto x : sol)
        cout << x << ' ';

    cout << '\n';

    return 0;
}
