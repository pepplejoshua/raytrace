#pragma once

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3 {
public:
    double e[3];

    vec3() : e{ 0, 0, 0 } {}
    vec3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }

    vec3& operator+=(const vec3& v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3& operator*=(double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3& operator/=(double t) {
        return *this *= 1 / t;
    }

    double length() const {
        return sqrt(length_squared());
    }

    double length_squared() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }
};

// point3 is an alias for vec3 used for geometry
using point3 = vec3;

// utility functions
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& l, const vec3& r) {
    return vec3(l.e[0] + r.e[0], l.e[1] + r.e[1], l.e[2] + r.e[2]);
}

inline vec3 operator-(const vec3& l, const vec3& r) {
    return vec3(l.e[0] - r.e[0], l.e[1] - r.e[1], l.e[2] - r.e[2]);
}

inline vec3 operator*(const vec3& l, const vec3& r) {
    return vec3(l.e[0] * r.e[0], l.e[1] * r.e[1], l.e[2] * r.e[2]);
}

inline vec3 operator*(double l, const vec3& r) {
    return vec3(l * r.e[0], l * r.e[1], l * r.e[2]);
}

inline vec3 operator*(const vec3& l, double r) {
    return r * l;
}

inline vec3 operator/(vec3 l, double r) {
    return (1 / r) * l;
}

inline double dot(const vec3& l, const vec3& r) {
    return l.e[0] * r.e[0] + l.e[1] * r.e[1] + l.e[2] * r.e[2];
}


/*
    i - 0 1 2
    1 - A B C
    2 - D E F
    cross =
    [
        (BF) - (CE),
        (CD) - (AF),
        (AE) - (BD)
    ]
*/
inline vec3 cross(const vec3& l, const vec3& r) {
    return vec3(
        l.e[1] * r.e[2] - l.e[2] * r.e[1],
        l.e[2] * r.e[0] - l.e[0] * r.e[2],
        l.e[0] * r.e[1] - l.e[1] * r.e[0]
    );
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}