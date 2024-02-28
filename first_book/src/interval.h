//
// Created by rrr on 2/26/24.
//

#ifndef RAY_TRACING_INTERVAL_H
#define RAY_TRACING_INTERVAL_H

class interval{
public:
    double min, max;

    interval(): min(+infinity), max(-infinity) {}

    interval(double mmin, double mmax): min(mmin), max(mmax) {}

    bool contains(double x) const{
        return min <= x && x<=max;
    }

    bool surrounds(double x) const{
        return min<x && x<max;
    }

    double clamp(double x) const{
        if(x < min) return min;
        if(x > max) return max;
        return x;
    }

    static const interval empty, universe;
};

const static interval empty (+infinity, -infinity);
const static interval universe (-infinity, +infinity);
#endif //RAY_TRACING_INTERVAL_H
