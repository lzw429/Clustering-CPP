#include <iostream>
#include <fstream>
#include <string>
#include "../lib/clustering.h"
#include "../lib/Util.h"

using namespace std;

int main() {
    string inFileName;
    string outFileName;
    cout << "Input file name:" << endl;
    cin >> inFileName;
    cout << "Output file name:" << endl;
    cin >> outFileName;
    ifstream ifs(inFileName);
    ofstream ofs(outFileName);
    if (!ifs) {
        cout << "[Error] cannot open the file " << inFileName << " ." << endl;
        return 0;
    }

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
        split(line, ",", nums, true);
        line.clear();
        Tuple<double> tuple(nums.size() - 1);
        cnt++;
        if (cnt <= 59) {
            tuple.type = 1;
        } else if (cnt <= 130) {
            tuple.type = 2;
        } else {
            tuple.type = 3;
        }
        for (unsigned int i = 0; i < nums.size() - 1; i++)
            tuple[i] = stof(nums[i]);
        tuples.push_back(tuple);
    }
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
    ifs.close();
    ofs.close();
    return 0;
}