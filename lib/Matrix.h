//
// Created by 舒意恒 on 2018/5/15.
// 实现矩阵的基本变换。
//

#ifndef ACM_CPP_TEMPLATE_MATRIX_H
#define ACM_CPP_TEMPLATE_MATRIX_H

#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

template<class T>
struct Matrix {
    int n, m; // 矩阵大小
    long long mod; // 用于模运算
    vector<vector<T>> mat; // 矩阵内容

    void clear();

    // 构造方法
    Matrix();

    Matrix(int, int);

    Matrix(int); // 单位矩阵

    // 运算符
    Matrix<T> operator+(const Matrix &b) const;

    Matrix<T> operator-(const Matrix &b) const;

    Matrix<T> operator*(const Matrix &b) const;

    Matrix<T> operator*=(const Matrix &b);

    Matrix<T> operator*(const T) const; // 数乘

    Matrix<T> operator*=(const T); // 数乘

    vector<T> operator[](unsigned int);

    Matrix<T> pow(long long) const; // 矩阵快速幂

};

template<class T>
Matrix<T>::Matrix() {
    this->n = 0;
    this->m = 0;
    this->mod = 0x3f3f3f3f;
}

template<class T>
Matrix<T>::Matrix(int n, int m) {
    this->n = n;
    this->m = m;
    this->mod = 0x3f3f3f3f;
    mat.resize(n, vector<T>(m));
}

template<class T>
Matrix<T>::Matrix(int n) {
    this->n = this->m = n;
    this->mod = 0x3f3f3f3f;
    mat.resize(n, vector<T>(n));
    for (int i = 0; i < n; i++)
        mat[i][i] = 1;
}

template<class T>
void Matrix<T>::clear() {
    n = m = 0;
    mat.clear();
}

template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix &b) const {
    assert(this->m == b.m && this->n == b.n);
    Matrix<T> res(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            res.mat[i][j] = this->mat[i][j] + b.mat[i][j];
        }
    }
    return res;
}

template<class T>
Matrix<T> Matrix<T>::operator-(const Matrix &b) const {
    assert(this->m == b.m && this->n == b.n);
    Matrix<T> res(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            res.mat[i][j] = this->mat[i][j] - b.mat[i][j];
        }
    }
    return res;
}

template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix &b) const {
    assert(this->m == b.n);
    Matrix<T> res(this->n, b.m);
    res.mod = this->mod;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < b.m; j++)
            for (int k = 0; k < this->m; k++)
                res.mat[i][j] = (res.mat[i][j] + this->mat[i][k] * b.mat[k][j]) % (T) this->mod;
    return res;
}

template<class T>
Matrix<T> Matrix<T>::operator*=(const Matrix &b) {
    return *this = *this * b;
}

template<class T>
Matrix<T> Matrix<T>::operator*(const T num) const {
    for (int i = 0; i < this->n; i++) {
        for (int j = 0; j < this->m; j++) {
            mat[i][j] = (mat[i][j] * num) % (T) mod;
        }
    }
    return *this;
}

template<class T>
vector<T> Matrix<T>::operator[](unsigned int index) {
    if (index >= this->n)
        throw exception();
    return this->mat[index];
}

template<class T>
Matrix<T> Matrix<T>::operator*=(const T num) {
    return mat = mat * num;
}

template<class T>
Matrix<T> Matrix<T>::pow(long long n) const {
    assert(this->n == this->m); // 必须是方阵
    Matrix<T> res(this->n); // 单位矩阵
    res.mod = this->mod;
    Matrix<T> a = *this;
    // 矩阵快速幂 计算 a^n
    while (n) {
        if (n & 1)
            res *= a;
        a *= a;
        n >>= 1;
    }
    return res;
}


#endif //ACM_CPP_TEMPLATE_MATRIX_H
