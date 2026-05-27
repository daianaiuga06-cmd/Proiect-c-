#pragma once
#include <vector>

using namespace std;
//functiile template
//sunt puse separat ca sa fie mai usor de hestionat si gasit
template <typename T, typename Predicate>
vector<T> filtreaza(const vector<T>& v, Predicate p) {
    vector<T> rezultat;

    for (auto &x : v)
        if (p(x))
            rezultat.push_back(x);

    return rezultat;
}

template <typename T, typename Func>
double acumuleaza(const vector<T>& v, Func f) {
    double suma = 0;

    for (auto &x : v)
        suma += f(x);

    return suma;
}