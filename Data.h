#pragma once
#include <iostream>
using namespace std;

class Data {
private:
    int zi, luna, an;

public:
    Data();//constructor implicit
    Data(int, int, int);

    int getZi() const;
    int getLuna() const;
    int getAn() const;

    bool esteValida() const;

    friend ostream& operator<<(ostream&, const Data&);
};