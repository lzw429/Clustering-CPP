//
// Created by 舒意恒 on 2018/6/25.
//

#include <iostream>
#include <fstream>
#include "../lib/Tuple.h"
#include "../lib/Util.h"
#include "../lib/HCA.h"

using namespace std;

int main() {
    string inFileName;
    string outFileName;
    cout << "Input file name:" << endl;
    cin >> inFileName;
    cout << "Output file name:" << endl;
    cin >> outFileName;
    vector<Tuple<double>> tuples;
    ifstream ifs = openIfs(inFileName);
    ofstream ofs(outFileName);

    string dist_type = getDistType();
    string line;
    auto cnt = 0;
    while (ifs >> line) {
        vector<string> nums;
        split(line, ",", nums);
        line.clear();
        Tuple<double> tuple(nums.size() - 1);
        cnt++; // 元组计数
        for (int i = 0; i < nums.size() - 1; i++) { // string 类型转化为 double 类型
            tuple[i] = stringToDouble(nums[i]);
        }
        tuples.push_back(tuple);
    }
    tuples = normalization(tuples);  // 归一化

    HCA(tuples, dist_type, ofs);
    closeFileStream(ifs, ofs);
    cout << "Hierarchical clustering algorithm completed." << endl;
    return 0;
}