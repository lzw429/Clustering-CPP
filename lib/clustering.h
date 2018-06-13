//
// Created by 舒意恒 on 2018/5/29.
//

#ifndef UCI_CPP_MLALGO_CLUSTERING_H
#define UCI_CPP_MLALGO_CLUSTERING_H

#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>
#include <ctime>
#include <iostream>
#include "Matrix.h"

using namespace std;

template<class T>
struct Tuple<T> {
    int type; // 类别标号
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

double getDist(const Tuple<double> &v1, const Tuple<double> &v2, const string &dist_type) const;

int getClusterNum(vector<Tuple<double>> means, Tuple<double> tuple, string dist_type);

Tuple<double> getMeans(const vector<Tuple<double>> &cluster);

double getClusterError(const vector<vector<Tuple<double>>> &cluster, vector<Tuple<double>> means, string dist_type);

vector<Tuple<double>> random_means(vector<Tuple<double>> &tuples, unsigned int k);

void KMeans(vector<Tuple<double>> &tuples, unsigned int k = 2);

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
            res[j] += cluster[i][j];
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

void KMeans(vector<Tuple<double>> &tuples, unsigned int k = 2, ofstream &ofs) {
    vector<vector<Tuple<double>>> clusters; // k个簇
    vector<Tuple<double>> means; // k个聚类中心
    string dist_type; // 距离类型
    int choice = 0; // 用户输入的选择
    // 选取距离类型
    cout << "" << endl;
    cout << "1. Manhattan distance" << endl;
    cout << "2. Euclidean distance" << endl;
    cout << "3. Chebyshev distance" << endl;
    cin >> choice;
    switch (choice) {
        case 1:
            dist_type = "Manhattan";
            break;
        case 2:
            dist_type = "Euclidean";
            break;
        case 3:
            dist_type = "Chebyshev";
            break;
        default:
            break;
    }
    // 生成初始质心
    cout << "Initial centroid input:" << endl;
    cout << "1. Randomly generate." << endl;
    cin >> choice;
    switch (choice) {
        case 1:
            means = random_means(means, k);
            break;
        default:
            break;
    }
    // 根据初始质心给簇赋值
    int label = 0;
    for (int i = 0; i != tuples.size(); i++) {
        label = getClusterNum(means, tuples[i], dist_type);
        clusters[label].push_back(tuples[i]);
    }
    double oldError = -1;
    double newError = getClusterError(clusters, means, dist_type);
    ofs << "The initial sum of the overall error:"  << newError << endl;
    int count = 0; // 迭代计数
    while (abs(newError - oldError) >= 1) {

    }
}

vector<Tuple<double>> random_means(vector<Tuple<double>> &tuples, unsigned int k) { // 随机生成聚类中心
    assert(!tuples.size());
    const int dimen = tuples[0].size(); // 维数
    vector<Tuple<double>> means(k, Tuple(dimen)); // 返回k个随机聚类中心
    Tuple<double> min_bound(dimen);
    Tuple<double> max_bound(dimen);
    for (int i = 0; i < tuples.size(); i++) {
        for (int j = 0; j < dimen; j++) {
            min_bound[j] = min(min_bound[j], tuples[i][j]);
            max_bound[j] = max(max_bound[j], tuples[i][j]);
        }
    }
    srand(static_cast<unsigned int>(time(0)));
    for (Tuple<double> tuple: means) {
        for (int i = 0; i < tuple.size(); i++) {
            double t = rand() % 100 / (double) 101;
            tuple[i] = t * (max_bound[i] - min_bound[i]) + min_bound[i]; // 生成随机数
        }
    }
    return means;
}

#endif //UCI_CPP_MLALGO_CLUSTERING_H
