//
// Created by 舒意恒 on 2018/6/25.
//

#ifndef UCI_CPP_MLALGO_HCA_H
#define UCI_CPP_MLALGO_HCA_H

#include <climits>
#include <vector>
#include <iostream>
#include <fstream>
#include "Tuple.h"
#include "Clustering.h"

struct Model {
    int i;
    int j;
    double dist = 0;
};

vector<vector<double>> &getDistMat(vector<Tuple> &data, string &dist_type) {
    const int size = data.size();
    vector<vector<double>> distMat(size, vector<double>(size));
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            distMat[i][j] = getDist(data[i], data[j], dist_type);
        }
    }
    return distMat;
}

Model &findClosestClusters(vector<vector<double>> &distMat) {
    Model model;
    double minDist = INT_MAX;
    for (int i = 0; i < distMat.size(); i++) {
        for (int j = i + 1; j < distMat.size(); j++) {
            if (distMat[i][j] < minDist && distMat[i][j] != 0) {
                minDist = distMat[i][j];
                model.i = i;
                model.j = j;
                model.dist = distMat[i][j];
            }
        }
    }
    return model;
}

void HCA(vector<Tuple> &data, string &dist_type, ofstream &ofs) {
    vector<vector<double>> distMat = getDistMat(data, dist_type);
    const int size = data.size();
    Model minModel;
    auto cnt = 0;
    while (true) {
        cnt++;
        ofs << "No." << cnt << " iteration" << endl;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                ofs << distMat[i][j] << " ";
            }
            cout << endl;
        }
        minModel = findClosestClusters(data);
        if (minModel.dist == 0) // 找不到距离最近的两个簇时，迭代结束
            break;
        ofs << "Combine cluster " << (minModel.i + 1) << " and " << (minModel.j + 1) << endl;
        ofs << "The distance is " << minModel.dist << endl;
        distMat[minModel.i][minModel.j] = 0; // 更新矩阵
        for (int i = 0; i < size; i++) {
            // 如果合并点p1 与 p2，则只保留 p1、p2 其中之一与其他点的距离，取较小值
            if (distMat[i][minModel.i] <= distMat[i][minModel.j])
                distMat[i][minModel.j] = 0;
            else
                distMat[i][minModel.i] = 0;
            if (distMat[minModel.i][i] <= distMat[minModel.j][i])
                distMat[minModel.j][i] = 0;
            else
                distMat[minModel.i][i] = 0;
        }
    }
}


#endif //UCI_CPP_MLALGO_HCA_H
