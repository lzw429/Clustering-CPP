#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "../lib/KMeans.h"
#include "../lib/Util.h"

using namespace std;

int main() {
    string inFileName;
    string outFileName;
    cout << "Input file name:" << endl;
    cin >> inFileName;
    cout << "Output file name:" << endl;
    cin >> outFileName;

    ifstream ifs = openIfs(inFileName);
    ofstream ofs(outFileName);

    int choice = 0;
    string dist_type;
    vector<Tuple<double>> tuples;
    int k = 2;
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
    cout << "Enter the number of clusters:" << endl;
    cin >> k;

    string line;
    auto cnt = 0;
    while (ifs >> line) {
        vector<string> nums;
        split(line, ",", nums);
        line.clear();
        Tuple<double> tuple(nums.size() - 1);
        cnt++; // 元组计数
        if (cnt <= 59) {
            tuple.type = 1;
        } else if (cnt <= 130) {
            tuple.type = 2;
        } else {
            tuple.type = 3;
        }
        for (unsigned int i = 0; i < nums.size() - 1; i++) { // string 类型转化为 double 类型
            tuple[i] = stringToDouble(nums[i]);
        }
        tuples.push_back(tuple);
    }
    tuples = normalization(tuples);  // 归一化
    vector<Tuple<double>> means; // k个聚类中心
    // 生成初始质心
    cout << "Initial centroid input:" << endl;
    cout << "1. Randomly generate." << endl;
    cin >> choice;
    switch (choice) {
        case 1:
            means = random_means(tuples, k);
            break;
        default:
            break;
    }
    KMeans(tuples, means, ofs, dist_type, k); // 执行 KMeans 算法
    closeFileStream(ifs, ofs);
    cout << "KMeans completed." << endl;
    return 0;
}