struct Matrix {

    int rows, columns;
    ll **mat;

    Matrix(int n) {
        *this = identity(n);
    }

    Matrix(int r, int c) {
        rows = r, columns = c;
        mat = new ll*[r];
        F0R(i, r) {
            mat[i] = new ll[c];
            memset(mat[i], 0, c * sizeof(ll));
        }
    }

    Matrix identity(int n) {
        Matrix m(n, n);
        F0R(i, n) m.mat[i][i] = 1;
        return m;
    }

    Matrix operator +(Matrix b) {
        if(b.rows != rows || b.columns != columns) return Matrix(0, 0);
        Matrix m(rows, columns);
        F0R(r, rows) F0R(c, columns) m.mat[r][c] = mat[r][c] + b.mat[r][c] % MOD;
        return m;
    }

    Matrix operator *(Matrix b) {
        if(columns != b.rows) return Matrix(0, 0);
        Matrix m(rows, b.columns);
        F0R(r, rows) F0R(c, b.columns) {
            m.mat[r][c] = 0;
            F0R(i, columns) {
                m.mat[r][c] += mat[r][i] * b.mat[i][c] % MOD;
                m.mat[r][c] %= MOD;
            }
        }
        return m;
    }

    Matrix operator ^(ll p) {
        if(columns != rows) return Matrix(0, 0);
        if(p == 0) return identity(rows);
        if(p % 2 == 1) return ((*this ^ (p - 1)) * (*this));
        Matrix sqrt = (*this ^ (p >> 1));
        return (sqrt * sqrt);
    }

    void operator +=(Matrix b) {
        *this = *this + b;
    }

    void operator *=(Matrix b) {
        *this = *this * b;
    }

    void operator ^=(ll p) {
        *this = *this ^ p;
    }

};
