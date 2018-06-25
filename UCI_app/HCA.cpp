//
// Created by 舒意恒 on 2018/6/25.
//

#include <iostream>
#include <fstream>
#include "../lib/HCA.h"
#include "../lib/Util.h"
#include "../lib/Tuple.h"

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


    return 0;
}