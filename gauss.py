import sys

def gauss(m, b):
    n = len(b)
    # elimination
    for i in range(n):
        for j in range(i + 1, n):
            if m[j][i] == 0:
                continue
            r = m[i][i] / m[j][i]
            b[j] *= r
            b[j] -= b[i]
            for k in range(n):
                m[j][k] *= r
                m[j][k] -= m[i][k]

    # backsubstitution
    b[n-1] /= m[n-1][n-1]
    m[n-1][n-1] /= m[n-1][n-1]

    for i in range(n-2, -1, -1):
        for j in range(i+1, n):
            if m[i][j] == 0:
                continue
            r = m[i][j]
            m[i][j] -= r * m[j][j]
            b[i] -= r * b[j]

        b[i] /= m[i][i]
        m[i][i] /= m[i][i]

    return b

def print_matrix(m, b):
    n = len(b)
    for i in range(n):
        for j in range(n):
            print(f'{m[i][j]:.4f}', end=' ')
        print(f'| {b[i]:.4f}')

def main():
    # Reading input from sys.stdin
    input_stream = sys.stdin.read()
    lines = input_stream.splitlines()
    
    n = int(lines[0])
    
    m = []
    b = []
    
    for i in range(1, n+1):
        row = list(map(float, lines[i].split()))
        m.append(row[:-1])
        b.append(row[-1])
    
    solution = gauss(m, b)
    
    print("solution X[] = ", ' '.join(f'{x:.4f}' for x in solution))

if __name__ == "__main__":
    main()
