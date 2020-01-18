#include"YinsetContainTriangle.h"
#include"Data.h"
#include"Tol.h"
#include<vector>
#include<set>
#include<map>
#include<math.h>
#include<utility>
#include<iostream>
#include<algorithm>

using namespace std;



bool YinsetContainTriangle::operator()(const Yinset& yinset, const Planar& triangle, int overlaptriangle = AddOverlap){
    Point p0 = Data::points[triangle.getpoints().[0]],
        p1 = Data::points[triangle.getpoints().[1]],
        p2 = Data::points[triangle.getpoints().[2]];
    Point p((p0[0] + p1[0] + p2[0]) / 3,
            (p0[1] + p1[1] + p2[1]) / 3,
            (p0[2] + p1[2] + p2[2]) / 3,
            Data::pointsnum);
    Data::points[Data::pointsnum] = p;
    Data::pointsnum++;
    Point farpoint = Data::farpoint;
    Segment striaghtLine(p.getid(), fatpoint.getid(), Data::segmentsnum);
    Data::segments[Data::segmentsnum] = striaghtLine;
    Data::segmentsnum++;
    Point intersectPoint;
    vector<Planar> intersectPlanar;
    for(auto i = yinset.getfaces.begin(); i != yinset.getfaces().end(); i++){
        for(auto j = Data::faces[*i].getplanars().begin();
            j != Data::faces[*i].getplanars().end(); j++){
            Planar pl = Data::planars[*j];
            if(pl.ifcontainPlanar(triangle)){
                if(overlaptriangle == AddOverlap){
                    if(triangle.getnormaldirect().dot(pl.getnormaldirect()) < -Tol::t)
                        return true;
                    else if(triangle.getnormaldirect().dot(pl.getnormaldirect()) > Tol::t)
                        return false;
                    else {
                        cout << "YinsetContainTriangle wrong in overlaptriangle == AddOverlap : "
                             << triangle.getid() << " : " << pl.getid();
                        int i;
                        cin >> i;
                    }
                }
                else if(overlaptriangle == notAddOverlap){
                    return false;
                }
                else {
                    cout << "YinsetContainTriangle wrong in overlaptriangle : "
                         << triangle.getid() << " : " << pl.getid();
                    int i;
                    cin >> i;
                }
            }
            Segment seg0 = Data::segments[pl.getsegments().[0]],
                seg1 = Data::segments[pl.getsegments().[1]],
                seg2 = Data::segments[pl.getsegments().[2]];
            Point p0 = Data::points[pl.getpoints().[0]],
                p1 = Data::points[pl.getpoints().[1]],
                p2 = Data::points[pl.getpoints().[2]];
            // int t = 0;
            bool ifcloser = false;
            bool ifequal = false;
            bool ifintersectEdge = false;
            Point interP;
            if(striaghtLine.ifcontainPoint(p0)){
                ifintersectEdge = true;
                interP = p0;
                if(interP == intersectPoint){
                    ifequal = true;
                }
                if((interP - p).norm() < (intersectPoint - p).norm() - Tol::t){
                    ifcloser = true;
                    intersectPoint = interP;
                }
            }
            if(striaghtLine.ifcontainPoint(p1)){
                ifintersectEdge = true;
                interP = p1;
                if(interP == intersectPoint){
                    ifequal = true;
                }
                if((interP - p).norm() < (intersectPoint - p).norm() - Tol::t){
                    ifcloser = true;
                    intersectPoint = interP;
                }
            }
            if(striaghtLine.ifcontainPoint(p2)){
                ifintersectEdge = true;
                interP = p2;
                if(interP == intersectPoint){
                    ifequal = true;
                }
                if((interP - p).norm() < (intersectPoint - p).norm() - Tol::t){
                    ifcloser = true;
                    intersectPoint = interP;
                }
            }
            if(ifintersectEdge == false){
                if(striaghtLine.ifintersectionSegment(seg0)){
                    ifintersectEdge = true;
                    // t++;
                    interP = striaghtLine.intersectionSegment(seg0);
                    if(interP == intersectPoint){
                        ifequal = true;
                    }
                    if((interP - p).norm() < (intersectPoint - p).norm() - Tol::t){
                        ifcloser = true;
                        intersectPoint = interP;
                    }
                }
                if(striaghtLine.ifintersectionSegment(seg1)){
                    ifintersectEdge = true;
                    // t++;
                    interP = striaghtLine.intersectionSegment(seg1);
                    if(interP == intersectPoint){
                        ifequal = true;
                    }
                    if((interP - p).norm() < (intersectPoint - p).norm() - Tol::t){
                        ifcloser = true;
                        intersectPoint = interP;
                    }
                }
                if(striaghtLine.ifintersectionSegment(seg2)){
                    ifintersectEdge = true;
                    // t++;
                    interP = striaghtLine.intersectionSegment(seg1);
                    if(interP == intersectPoint){
                        ifequal = true;
                    }
                    if((interP - p).norm() < (intersectPoint - p).norm() - Tol::t){
                        ifcloser = true;
                        intersectPoint = interP;
                    }
                }
            }
            if(ifintersectEdge){
                if(ifcloser){
                    intersectPlanar.clear();
                    intersectPlanar.push_back(pl);
                }
                else if(ifequal) {
                    intersectPlanar.push_back(pl);
                }
            }
            else {
                if(pl.ifintersectionLine(striaghtLine)){
                    interP = pl.intersectionSegment(striaghtLine);
                    if((interP - p).norm() < (intersectPoint - p).norm() - Tol::t){
                        intersectPoint = interP;
                        intersectPlanar.clear();
                        intersectPlanar.push_back(pl);
                    }
                }
            }
        }
    }
    if(intersectPlanar.empty()){
        return yinset.gettype();
    }
    else if(intersecPlanar.size() == 1){
        Planar interpl = intersectPlanar[0];
        Direction d = intersectPoint - p;
        double dou = d.dot(interpl.getnormaldirect());
        if(dou > 0){
            return 1;
        }
        else if(dou < 0){
            return 0;
        }
        else {
            cout << "YinsetContainTriangle:: intersectPlanar.size() == 1 wrong :"
                 << interpl.getid() <<" : ";
            int i;
            cin >> i;
        }
    }
    else {
        Direction d = intersectPoint - p;
        double angle = M_PI;
        Planar closePl;
        for(auto i = intersectPlanar.begin(); i != intersectPlanar.end(); i++){
            Planar Pl = *i;
            Segment seg,
                seg0 = Data::segments[Pl.getsegments[0]],
                seg1 = Data::segments[Pl.getsegments[1]],
                seg2 = Data::segments[Pl.getsegments[2]];
            if(seg0.ifcontainPoint(intersectPoint)){
                seg = seg0;
            }
            if(seg1.ifcontainPoint(intersectPoint)){
                seg = seg1;
            }
            if(seg2.ifcontainPoint(intersectPoint)){
                seg = seg2;
            }
            Direction d1;
            if(find(seg.getinPlanar01().begin(), seg.getinPlanar01().end(), Pl.getid())){
                d1 = Data::points[seg[0]] - Data::points[seg[1]];
            }
            else if(find(seg.getinPlanar10().begin(), seg.getinPlanar10().end(), Pl.getid())){
                d1 = Data::points[seg[1]] - Data::points[seg[0]];
            }
            Direction normal = d.cross(d1);
            Flat flat(intersectPoint, normal);
            double a = flat.angleBetweenFlats(Pl, d1);
            if(a >= M_PI)
                a = 2 * M_PI - a;
            if(a < angle){
                angle = a;
                closePl = Pl;
            }
        }
        if(d.dot(closePl.getnormaldirect()) > 0) {
            return 1;
        }
        else {
            return 0;
        }
    }
}
