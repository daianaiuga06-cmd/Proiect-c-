#pragma once
#include <iostream>

using namespace std;

class Data {// Clasa pentru gestionarea unei date calendaristice
private:
    int zi, luna, an;

public:
    Data();//constructor implicit
    Data(int, int, int);

    int getZi() const;
    int getLuna() const;
    int getAn() const;

    friend ostream& operator<<(ostream&, const Data&);
};