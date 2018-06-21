//
// Created by 舒意恒 on 2018/6/21.
//

#include "../lib/DBSCAN.h"

int main() {
    string inFileName;
    string outFileName;
    cout << "Input file name:" << endl;
    cin >> inFileName;
    cout << "Output file name:" << endl;
    cin >> outFileName;
    ifstream ifs(inFileName);
    ofstream ofs(outFileName);
    return 0;
}