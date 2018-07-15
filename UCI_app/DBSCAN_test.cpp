//
// Created by 舒意恒 on 2018/6/21.
//
#include <iostream>
#include <fstream>
#include "../lib/DBSCAN.h"
#include "../lib/Util.h"

using namespace std;

int main() {
    string inFileName;
    string outFileName;
    cout << "Input file name:" << endl;
    cin >> inFileName;
    cout << "Output file name:" << endl;
    cin >> outFileName;
    vector<Point<double>> points;
    ifstream ifs = openIfs(inFileName);
    ofstream ofs(outFileName);

    string dist_type = getDistType();

    auto minPts = 3;
    auto Epsilon = 0.14;
    cout << "Enter the minPts and the Epsilon:" << endl;
    cin >> minPts >> Epsilon;

    string line;
    auto cnt = 0;
    while (ifs >> line) {
        vector<string> nums;
        split(line, ",", nums);
        line.clear();
        Point<double> point(nums.size() - 1);
        cnt++; // 元组计数
        for (int i = 0; i < nums.size() - 1; i++) { // string 类型转化为 double 类型
            point[i] = stringToDouble(nums[i]);
        }
        point.label = stoi(nums[nums.size() - 1]);
        point.cluster = cnt;
        points.push_back(point);
    }
    points = normalization(points);  // 归一化
    DBSCAN(points, ofs, Epsilon, minPts, dist_type); // 执行 DBSCAN 算法

    closeFileStream(ifs, ofs);
    cout << "DBSCAN completed." << endl;
    return 0;
}