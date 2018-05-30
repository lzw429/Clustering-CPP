//
// Created by 舒意恒 on 2018/5/29.
//

#ifndef UCI_CPP_MLALGO_CLUSTERING_H
#define UCI_CPP_MLALGO_CLUSTERING_H

#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>
#include "Matrix.h"

using namespace std;

template<class T>
struct Tuple<T> {
    int type;
    vector<T> v;

    Tuple(unsigned int size) {
        type = 0;
        v.resize(size, 0);
    }

    int size() const {
        return v.size();
    }

    T operator[](unsigned int index) const {
        if (index >= v.size()) {
            throw out_of_range("Index exceeds vector length.");
        }
        return v[index];
    };
};

// 计算两元组间距离
double getDist(const Tuple<double> &v1, const Tuple<double> &v2, const string &dist_type) const {
    double res = 0;
    if (v1.size() != v2.size())
        throw length_error("The length of the two tuples should be the same.");
    if (dist_type == "Manhattan") { // 曼哈顿距离
        for (int i = 0; i < v1.size(); i++)
            res += abs(v1[i] - v2[i]);
    } else if (dist_type == "Euclidean") { // 欧几里得距离
        for (int i = 0; i < v1.size(); i++)
            res += (v1[i] - v2[i]) * (v1[i] - v2[i]);
        res = sqrt(res);
    } else if (dist_type == "Chebyshev") { // 切比雪夫距离
        if (v1.size() < 3) // 向量维度至少为3
            throw length_error("Calculating Chebyshev distance needs tuple dimension greater than or equal to 3.");
        for (int i = 0; i < v1.size(); i++)
            res = max(res, abs(v1[i] - v2[i]));
    }
    return res;
}

// 根据质心，判断当前元组属于哪个簇
int getClusterNum(vector<Tuple<double>> means, Tuple<double> tuple, string dist_type) {
    double dist = getDist(means[0], tuple, dist_type);
    int label = 0; // 簇编号，从0开始
    for (int i = 1; i < means.size(); i++) {
        double tmp = getDist(means[i], tuple, dist_type);
        if (tmp < dist) {
            dist = tmp;
            label = i;
        }
    }
    return label;
}

// 获取当前簇的质心
Tuple<double> getMeans(const vector<Tuple<double>> &cluster) {
    const int m = cluster.size(); // 样本数
    if (!m)
        throw length_error("There is no sample for calculation.");
    const int n = cluster[0].size(); // 维数
    Tuple<double> res((unsigned int) n);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            res[j] += cluster.mat[i][j];
    for (int j = 0; j < n; j++)
        res[j] /= m;
    return res;
}

// 获得给定簇集的误差
double getClusterError(const vector<vector<Tuple<double>>> &cluster, vector<Tuple<double>> means, string dist_type) {
    double res = 0;
    for (int i = 0; i < means.size(); i++) {
        vector<Tuple<double >> type = cluster[i];
        for (int j = 0; j < type.size(); j++)
            res += getDist(type[j], means[i], dist_type);
    }
    return res;
}

void KMeans(vector<Tuple<double>> &tuples, int k = 2) {
    vector<vector<Tuple<double>>> clusters; // k个簇
    vector<Tuple<double>> means; // k个聚类中心
    for (int i = 0; i < k; i++) {

    }
}

#endif //UCI_CPP_MLALGO_CLUSTERING_H
