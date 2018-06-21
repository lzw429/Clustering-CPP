//
// Created by 舒意恒 on 2018/6/21.
//

#ifndef UCI_CPP_MLALGO_DBSCAN_H
#define UCI_CPP_MLALGO_DBSCAN_H

#include "clustering.h"

class Point : public Tuple {
public:
    int pts; // points in MinPts
    bool visited;

    Point(vector<double> v, int type) {
        this->v = v;
        this->type = type;
    }
};

#endif //UCI_CPP_MLALGO_DBSCAN_H
