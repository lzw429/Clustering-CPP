//
// Created by 舒意恒 on 2018/6/21.
//
#include <iostream>
#include <fstream>
#include "../lib/Util.h"
#include "../lib/DBSCAN.h"

#define Epsilon 0.1
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

    int choice = 0;
    string dist_type;
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
    auto minPts = 3;
    cout << "Enter the minPts:" << endl;
    cin >> minPts;

    string line;
    auto cnt = 0;
    while (ifs >> line) {
        vector<string> nums;
        split(line, ",", nums);
        line.clear();
        Point<double> point(nums.size() - 1);
        cnt++; // 元组计数
        for (unsigned int i = 0; i < nums.size() - 1; i++) { // string 类型转化为 double 类型
            point[i] = stringToDouble(nums[i]);
        }
        point.cluster = cnt;
        points.push_back(point);
    }
    points = normalization(points);  // 归一化
    DBSCAN(points, ofs, Epsilon, minPts, dist_type); // 执行 KMeans 算法
    closeFileStream(ifs, ofs);
    cout << "DBSCAN completed." << endl;
    return 0;
}