// Uses https://github.com/walnutwaldo/Programming_Contests/blob/master/Implementations/Data%20Structures/Math/Matrix.cpp
// Has a huge constant but is asymptotically faster than standard multiplication
// The constant is why this is not used in Matrix.cpp
Matrix operator *(Matrix b) {
        if(columns != b.rows) return Matrix();
        if(min(rows, min(columns, b.columns)) <= 100) {
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
        if((rows & (rows - 1)) || (columns & (columns - 1)) || (b.columns & (b.columns - 1))) {
            Matrix A(1 << (32 - __builtin_clz(rows - 1)), 1 << (32 - __builtin_clz(columns - 1)));
            Matrix B(1 << (32 - __builtin_clz(columns - 1)), 1 << (32 - __builtin_clz(b.columns - 1)));
            F0R(r, rows) F0R(c, columns) A.mat[r][c] = mat[r][c];
            F0R(r, columns) F0R(c, b.columns) B.mat[r][c] = b.mat[r][c];
            Matrix m = A * B;
            Matrix res(rows, b.columns);
            F0R(r, rows) F0R(c, b.columns) res.mat[r][c] = m.mat[r][c];
            return res;
        }
        Matrix A[2][2], B[2][2];
        F0R(i, 2) F0R(j, 2) {
            A[i][j] = Matrix(rows / 2, columns / 2);
            F0R(r, rows / 2) F0R(c, columns / 2) if(i * rows / 2 + r < rows && j * columns / 2 + c < columns)
                A[i][j].mat[r][c] = mat[i * rows / 2 + r][j * columns / 2 + c];
            B[i][j] = Matrix(b.rows / 2, b.columns / 2);
            F0R(r, b.rows / 2) F0R(c, b.columns / 2) if(i * b.rows / 2 + r < b.rows && j * b.columns / 2 + c < b.columns)
                B[i][j].mat[r][c] = b.mat[i * b.rows / 2 + r][j * b.columns / 2 + c];
        }
        Matrix P[7];
        P[0] = A[0][0] * (B[0][1] - B[1][1]);
        P[1] = (A[0][0] + A[0][1]) * B[1][1];
        P[2] = (A[1][0] + A[1][1]) * B[0][0];
        P[3] = A[1][1] * (B[1][0] - B[0][0]);
        P[4] = (A[0][0] + A[1][1]) * (B[0][0] + B[1][1]);
        P[5] = (A[0][1] - A[1][1]) * (B[1][0] + B[1][1]);
        P[6] = (A[0][0] - A[1][0]) * (B[0][0] + B[0][1]);
        Matrix C[2][2];
        C[0][0] = P[4] + P[3] - P[1] + P[5];
        C[0][1] = P[0] + P[1];
        C[1][0] = P[2] + P[3];
        C[1][1] = P[4] + P[0] - P[2] - P[6];
        Matrix res(rows, b.columns);
        F0R(r, rows) F0R(c, b.columns) res.mat[r][c] = C[2 * r / rows][2 * c / b.columns].mat[r % (rows / 2)][c % (b.columns / 2)];
        return res;
    }
