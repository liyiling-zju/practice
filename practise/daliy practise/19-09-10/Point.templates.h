#include "Point11.h"
using namespace std;

template <int DIM>
ostream &operator<<(ostream& os, const Point<DIM>& _pnt)
{
    for (int i = 0; i < DIM; i++)
        os << _pnt.coordinate[i] << "\t";
    return os;
};

template <int DIM>
Point<DIM>::Point(double x, double y)
{
    if (DIM != 2)
    {
        cerr << "Dimension error!" << "\n";
        exit(-1);
    }
    coordinate[0] = x;
    coordinate[1] = y;
};

template <int DIM>
Point<DIM>::Point(double x, double y, double z)
{
    if(DIM != 3)
    {
        cerr << "Dimension error!" << "\n";
        exit(-1);
    }
    coordinate[0] = x;
    coordinate[1] = y;
    coordinate[2] = z;
};

template <int DIM>
Point<DIM>::Point(const Point<DIM> &_pnt)
{
    for (int i = 0; i < DIM; i++)
        coordinate[i] = _pnt.coordinate[i];
};

template <int DIM>
const double *Point<DIM>::read() const
{
    return coordinate;
};

template <int DIM>
double &Point<DIM>::operator[](int i)
{
    if(i > DIM - 1)
    {
        cerr << "Dimension out of range!" << "\n";
        exit(-1);
    }
    return coordinate[i];
};

template <int DIM>
const double &Point<DIM>::operator[](int i) const
{
    if (i > DIM - 1)
    {
        cerr << "Demension out range!" << "\n";
        exit(-1);
    }
    return coordinate[i];
}

template <int DIM>
Point<DIM> operator+(const Point<DIM> &_p1, const Point<DIM> &_p2)
{
    // Here we want a default constructor.
    Point<DIM> result;
    for (int i = 0; i < DIM; i++)
        result.coordinate[i] = _p1[i] + _p2[i];
    return result;
};

template <int DIM>
Point<DIM> &Point<DIM>::operator=(const Point<DIM> &_pnt)
{
    for (int i = 0; i < DIM; i++)
        coordinate[i] = _pnt.coordinate[i];
    return *this;
};

template <int DIM>
Point<DIM> &Point<DIM>::operator+=(const Point<DIM> &_pnt)
{
    for (int i = 0; i < DIM; i++)
        coordinate[i] += _pnt.coordinate[i];
    return *this;
};
