//
// Created by 舒意恒 on 2018/6/21.
//
#ifndef UCI_CPP_MLALGO_DBSCAN_H
#define UCI_CPP_MLALGO_DBSCAN_H

#include <stack>
#include <queue>
#include "Tuple.h"
#include "Clustering.h"

using namespace std;

template<class T>
class Point : public Tuple<T> {
public:
    // type 的值
    static const int NOISE = 1;
    static const int BORDER = 2;
    static const int CORE = 3;

    int pts; // the number of points in the Epsilon range
    bool visited;
    vector<int> corepts;
    int cluster;

    Point(int size) {
        this->v.resize(size);
    }

    Point(vector<double> v, int cluster) {
        this->v = v;
        this->cluster = cluster;
    }

    bool operator<(const Point &p) const {
        if (this->cluster < p.cluster)
            return true;
        return false;
    }
};

struct smallTopHeap {
    bool operator()(const Point<double> &a, const Point<double> &b) const {
        return !(a < b); // 小顶堆
    }
};

// 函数声明
void DBSCAN(vector<Point<double>> &data, ofstream &ofs, double Epsilon, int minPts, string &dist_type);

void print(vector<Point<double>> &, vector<Point<double>> &, ofstream &);

// 函数实现
inline void DBSCAN(vector<Point<double>> &data, ofstream &ofs, double Epsilon, int minPts, string &dist_type) {
    const int size = data.size();
    vector<Point<double>> corePoint;

    for (auto i = 0; i < size; i++) {
        for (auto j = i + 1; j < size; j++) {
            if (getDist(data[i], data[j], dist_type) < Epsilon) {
                data[i].pts++;
                data[j].pts++;
            }
        }
    }
    for (int i = 0; i < size; i++) {
        if (data[i].pts >= minPts) {
            data[i].type = Point<double>::CORE;
            corePoint.push_back(data[i]);
        }
    }
    for (int i = 0; i < corePoint.size(); i++) {
        for (int j = i + 1; j < corePoint.size(); j++) {
            if (getDist(corePoint[i], corePoint[j], dist_type) < Epsilon) {
                corePoint[i].corepts.push_back(j);
                corePoint[j].corepts.push_back(i);
            }
        }
    }
    for (int i = 0; i < corePoint.size(); i++) {
        stack<Point<double>> stack;
        if (corePoint[i].visited)
            continue;
        stack.push(corePoint[i]);
        while (!stack.empty()) {
            Point<double> cur = stack.top();
            stack.pop();
            cur.visited = true;
            for (int j = 0; j < cur.corepts.size(); j++) {
                if (corePoint[cur.corepts[j]].visited = true)
                    continue;
                corePoint[cur.corepts[j]].cluster = corePoint[i].cluster;
                stack.push(corePoint[cur.corepts[j]]);
            }
        }
    }
    for (int i = 0; i < size; i++) {
        if (data[i].type == Point<double>::CORE)
            continue;
        for (int j = 0; j < corePoint.size(); j++) {
            if (getDist(data[i], corePoint[j], dist_type) < Epsilon) {
                data[i].type = Point<double>::BORDER;
                data[i].cluster = corePoint[j].cluster;
                break;
            }
        }
    }
    print(data, corePoint, ofs);
}

inline void print(vector<Point<double>> &data, vector<Point<double>> &corePoint, ofstream &ofs) {
    const int size = data.size();
    priority_queue<Point<double>, vector<Point<double>>, smallTopHeap> priorityQueue;
    for (int i = 0; i < size; i++) {
        if (data[i].type == Point<double>::BORDER) {
            priorityQueue.push(data[i]);
        }
    }
    for (int i = 0; i < corePoint.size(); i++)
        priorityQueue.push(corePoint[i]);
    while (!priorityQueue.empty()) {
        Point<double> cur = priorityQueue.top();
        priorityQueue.pop();
        ofs << "[" << cur.cluster << "] (";
        for (int i = 0; i < cur.size(); i++)
            ofs << cur[i] << ((i != cur.size() - 1) ? ", " : "");
        ofs << ")" << endl;
    }
}

#endif //UCI_CPP_MLALGO_DBSCAN_H
