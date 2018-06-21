//
// Created by 舒意恒 on 2018/6/13.
//

#ifndef UCI_CPP_MLALGO_UTIL_H

void setFileStream(ifstream ifs, ofstream ofs, string inFileName, string outFileName);

void split(std::string &s, std::string delim, std::vector<std::string> &ret);

vector<Tuple<double>> normaliazation(vector<Tuple<double>> &data);

ifstream openIfs(string &inFileName) {
    ifstream ifs(inFileName);
    ofs.open(outFileName, ofstream::out);
    if (!ifs) {
        cout << "[Error] cannot open the file " << inFileName << " ." << endl;
        return -1;
    }
}

void closeFileStream(ifstream ifs, ofstream ofs) {
    ifs.close();
    ofs.close();
}

// s 被分割字符串
// delimiters 分隔符
// ret 分割后的字符串集合
void split(std::string &s, std::string delim, std::vector<std::string> &ret) {
    size_t last = 0;
    size_t index = s.find_first_of(delim, last);
    while (index != string::npos) {
        ret.push_back(s.substr(last, index - last));
        last = index + 1;
        index = s.find_first_of(delim, last);
    }
    if (index - last > 0) {
        ret.push_back(s.substr(last, index - last));
    }
}

vector<Tuple<double>> normaliazation(vector<Tuple<double>> &data) { // 数据归一化
    assert(data.size() != 0);
    const int dimen = data[0].size(); // 维数
    const int size = data.size();
    vector<Tuple<double>> norm(size, Tuple<double>(dimen));
    Tuple<double> min_bound(dimen);
    Tuple<double> max_bound(dimen);
    for (auto &tuple : data) {
        for (int j = 0; j < dimen; j++) {
            min_bound[j] = min(min_bound[j], tuple[j]);
            max_bound[j] = max(max_bound[j], tuple[j]);
        }
    }
    // 归一化
    for (int i = 0; i < norm.size(); i++) {
        norm[i].type = data[i].type;
        for (int j = 0; j < dimen; j++) {
            norm[i][j] = (data[i][j] - min_bound[j]) / (max_bound[j] - min_bound[j]);
        }
    }
    return norm;
}

#define UCI_CPP_MLALGO_UTIL_H

#endif //UCI_CPP_MLALGO_UTIL_H
