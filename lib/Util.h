//
// Created by 舒意恒 on 2018/6/13.
//

#ifndef UCI_CPP_MLALGO_UTIL_H

// str 被分割字符串
// delimiters 分隔符
// elems 分割后的字符串集合
vector <string> &split(const string &str, const string &delimiters, vector <string> &elems, bool skip_empty = true) {
    string::size_type pos, prev = 0;
    while ((pos = str.find_first_of(delimiters, prev)) != string::npos) {
        if (pos > prev) {
            if (skip_empty && 1 == pos - prev) break;
            elems.emplace_back(str, prev, pos - prev);
        }
        prev = pos + 1;
    }
    if (prev < str.size()) elems.emplace_back(str, prev, str.size() - prev);
    return elems;
}

#define UCI_CPP_MLALGO_UTIL_H

#endif //UCI_CPP_MLALGO_UTIL_H
