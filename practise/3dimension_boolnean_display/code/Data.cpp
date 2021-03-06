#include"Point.h"
#include"Segment.h"
#include"Planar.h"
#include"Face.h"
#include"Yinset.h"
#include"HassNode.h"
#include"FunctorHead.h"
#include<map>
#include<set>
#include<vector>
#include<stack>
using namespace std;



std::set<int> Data::existpoints;
std::set<int> Data::existsegments;
std::set<int> Data::existplanars;
std::set<int> Data::existfaces;
std::vector<Point> Data::points(1);
std::vector<Segment> Data::segments;
std::vector<Planar> Data::planars;
std::vector<Face> Data::faces;
std::vector<Yinset> Data::yinsets;
std::map<Point, set<int>> Data::pastpoints;
int Data::pointsnum = 1;
int Data::segmentsnum = 0;
int Data::planarsnum = 0;
int Data::facesnum = 0;
int Data::yinsetsnum = 0;
Point Data::farpoint = Point(0, 0, 0, 0);


void Data::load(const Yinset& y){
    vector<int> yfaces = y.getfaces();
    for(auto i = yfaces.begin(); i != yfaces.end(); i++){
        existfaces.insert(*i);
        Face f = faces[*i];
        f.setinYinset(y.getid());
        vector<int> fplanars = f.getplanars();
        for(auto j = fplanars.begin(); j != fplanars.end(); j++){
            existplanars.insert(*j);
            Planar pl = planars[*j];
            pl.setinYinset(y.getid());
            pl.setinFace(f.getid());
            vector<int> plpoints = pl.getpoints(),
                plsegments = pl.getsegments();
            set<int> existseg;
            vector<Point> p(3);
            vector<Segment> seg(3);
            for(int k = 0; k < 3; k++){
                existsegments.insert(plsegments[k]);
                existpoints.insert(plpoints[k]);
                existseg.insert(plsegments[k]);
                p[k] = points[plpoints[k]];
                p[k].setinYinset(y.getid());
                seg[k] = segments[plsegments[k]];
                seg[k].setinYinset(y.getid());
                set<int> inPlanar = seg[k].getinPlanar();
                inPlanar.insert(pl.getid());
                seg[k].setinPlanar(inPlanar);
                if(seg[k][0] == p[k].getid()){
                    set<int> inPlanar01 = seg[k].getinPlanar01();
                    inPlanar01.insert(pl.getid());
                    seg[k].setinPlanar01(inPlanar01);
                }
                else if(seg[k][1] == p[k].getid()){
                    set<int> inPlanar10 = seg[k].getinPlanar10();
                    inPlanar10.insert(pl.getid());
                    seg[k].setinPlanar10(inPlanar10);
                }
                if(p[k][0] > farpoint[0]){
                    farpoint[0] = p[k][0];
                }
                if(p[k][1] > farpoint[1]){
                    farpoint[1] = p[k][1];
                }
                if(p[k][2] > farpoint[2]){
                    farpoint[2] = p[k][2];
                }
            }
            set<int> inSegment0 = p[0].getinSegment(),
                inSegment1 = p[1].getinSegment(),
                inSegment2 = p[2].getinSegment();
            inSegment0.insert(seg[0].getid());
            inSegment0.insert(seg[2].getid());
            inSegment1.insert(seg[1].getid());
            inSegment1.insert(seg[0].getid());
            inSegment2.insert(seg[2].getid());
            inSegment2.insert(seg[1].getid());
            p[0].setinSegment(inSegment0);
            p[1].setinSegment(inSegment1);
            p[2].setinSegment(inSegment2);
            pl.setexistsegments(existseg);
        }
    }
    for(int k = 0; k < 3; k++){
        farpoint[k] = farpoint[k] + 1;
        points[0] = farpoint;
    }
}


void Data::clear(){
    farpoint = Point(0, 0, 0, 0);
    for(auto i = existpoints.begin(); i != existpoints.end(); i++){
        points[*i].setinYinset(-2);
        points[*i].setinSegment(set<int>());
    }
    existpoints.clear();
    for(auto i = existsegments.begin(); i != existsegments.end(); i++){
        segments[*i].setinYinset(-2);
        segments[*i].setinPlanar(set<int>());
        segments[*i].setinPlanar01(set<int>());
        segments[*i].setinPlanar10(set<int>());
    }
    existsegments.clear();
    for(auto i = existplanars.begin(); i != existplanars.end(); i++){
        planars[*i].setinYinset(-2);
        planars[*i].setinFace(-2);
        planars[*i].setexistpoints(set<int>());
        planars[*i].setexistsegments(set<int>());
    }
    existplanars.clear();
    for(auto i = existfaces.begin(); i != existfaces.end(); i++){
        faces[*i].setinYinset(-2);
        faces[*i].settype(-2);
    }
    existfaces.clear();
    pastpoints.clear();
}

void Data::structcopy(){
    map<int, int> cypoints;
    map<int, int> cysegments;
    map<int, int> cyplanars;
    map<int, int> cyfaces;
    Point cyfarpoint = farpoint;
    for(auto i = existpoints.begin(); i != existpoints.end(); i++){
        Point p = points[*i];
        Point newp(p[0], p[1], p[2], pointsnum++);
        newp.setinYinset(p.getinYinset());
        cypoints[*i] = newp.getid();
    }
    for(auto i = existsegments.begin(); i != existsegments.end(); i++){
        Segment newseg = segments[*i];
        newseg.setid(segmentsnum++);
        cysegments[*i] = newseg.getid();
    }
    for(auto i = existplanars.begin(); i != existplanars.end(); i++){
        Planar newpl = planars[*i];
        newpl.setid(planarsnum++);
        cyplanars[*i] = newpl.getid();
    }
    for(auto i = existfaces.begin(); i != existfaces.end(); i++){
        Face newf = faces[*i];
        newf.setid(facesnum++);
        cyfaces[*i] = newf.getid();
    }
    /*
    for(auto i = cypoints.begin(); i != cypoints.end(); i++){
        Point newp = points[i->second];
        set<int> inSegment = newp.getinSegment(),
            newinSegment;
        for(auto j = inSegment.begin(); j != inSegment.end(); j++){
            newinSegment.insert(cysegments[*j]);
        }
        newp.setinSegment();
    }
    */
    for(auto i = cysegments.begin(); i != cysegments.end(); i++){
        Segment newseg = segments[i->second];
        newseg.setendpoints(0, cypoints[newseg[0]]);
        newseg.setendpoints(1, cypoints[newseg[1]]);
        set<int> inPlanar = newseg.getinPlanar(), newinPlanar,
            inPlanar10 = newseg.getinPlanar10(), newinPlanar10,
            inPlanar01 = newseg.getinPlanar01(), newinPlanar01;
        for(auto j = inPlanar.begin(); j != inPlanar.end(); j++){
            newinPlanar.insert(cyplanars[*j]);
        }
        for(auto j = inPlanar10.begin(); j != inPlanar10.end(); j++){
            newinPlanar10.insert(cyplanars[*j]);
        }
        for(auto j = inPlanar01.begin(); j != inPlanar01.end(); j++){
            newinPlanar01.insert(cyplanars[*j]);
        }
        newseg.setinPlanar(newinPlanar);
        newseg.setinPlanar01(newinPlanar01);
        newseg.setinPlanar10(newinPlanar10);
    }
    for(auto i = cyplanars.begin(); i != cyplanars.end(); i++){
        Planar newpl = planars[i->second];
        vector<int> points = newpl.getpoints(), newpoints,
            segments = newpl.getsegments(), newsegments;
        set<int> existpoints = newpl.getexistpoints(), newexistpoints,
            existsegments = newpl.getexistsegments(), newexistsegments;
        for(auto j = points.begin(); j != points.end(); j++){
            newpoints.push_back(cypoints[*j]);
        }
        for(auto j = segments.begin(); j != segments.end(); j++){
            newsegments.push_back(cysegments[*j]);
        }
        for(auto j = existpoints.begin(); j != existpoints.end(); j++){
            newexistpoints.insert(cypoints[*j]);
        }
        for(auto j = existsegments.begin(); j != existsegments.end(); j++){
            newexistsegments.insert(cysegments[*j]);
        }
        newpl.setpoints(newpoints);
        newpl.setsegments(newsegments);
        newpl.setexistpoints(newexistpoints);
        newpl.setexistsegments(newexistsegments);
        newpl.setinFace(cyfaces[newpl.getinFace()]);
    }
    for(auto i = cyfaces.begin(); i != cyfaces.end(); i++){
        Face newf = faces[i->second];
        vector<int> planars = newf.getplanars(), newplanars;
        for(auto j = planars.begin(); j != planars.end(); j++){
            newplanars.push_back(cyplanars[*j]);
        }
        newf.setplanars(newplanars);
    }
    clear();
    for(auto i = cypoints.begin(); i != cypoints.end(); i++){
        existpoints.insert(i->second);
    }
    for(auto i = cysegments.begin(); i != cysegments.end(); i++){
        existsegments.insert(i->second);
    }
    for(auto i = cyplanars.begin(); i != cyplanars.end(); i++){
        existplanars.insert(i->second);
    }
    for(auto i = cyfaces.begin(); i != cyfaces.end(); i++){
        existfaces.insert(i->second);
    }
    farpoint = cyfarpoint;
    points[0] = farpoint;
}


void Data::intersection(){
    TriangleIntersection functor;
    for(auto i = existplanars.begin(); i != prev(existplanars.end(), 1); i++){
        for(auto j = next(i); j != existplanars.end(); j++){
            Planar pli = planars[*i],
                plj = planars[*j];
            functor(pli, plj);
        }
    }
    SegmentIntersection functor1;
    for(auto i = existplanars.begin(); i != existplanars.end(); i++){
        functor1(planars[*i]);
    }
    for(auto i = existplanars.begin(); i != existplanars.end(); i++){
        Data::planars[*i].remove_not_pastpoints();
    }
}

void Data::triangulation(){
    vector<vector<Planar>> triangles;
    for(auto i = existplanars.begin(); i != existplanars.end(); i++){
        Triangulation functor;
        Planar pl = Data::planars[*i];
        vector<Planar> parttriangles = functor(pl);
        // copy(parttriangles.begin(), parttriangles.end(), triangles.end());
        triangles.push_back(parttriangles);
    }
    existplanars.clear();
    for(auto i = triangles.begin(); i != triangles.end(); i++){
        vector<Planar> vpl = *i;
        for(auto j = vpl.begin(); j != vpl.end(); j++){
            existplanars.insert((*j).getid());
        }
    }
}

void Data::selecttriangles(const Yinset& y1, const Yinset& y2){
    vector<int> delpl;
    for(auto i = existplanars.begin(); i != existplanars.end(); i++){
        Planar pl = Data::planars[*i];
        YinsetContainTriangle functor;
        if(pl.getinYinset() == y1.getid()){
            if(functor(y2, pl, 0) == false){
                delpl.push_back(pl.getid());
            }
        }
        else{
            if(functor(y1, pl, 1) == false){
                delpl.push_back(pl.getid());
            }
        }
    }
    for(auto i = delpl.begin(); i != delpl.end(); i++){
        Planar pl = planars[*i];
        vector<int> plsegments = pl.getsegments();
        assert(segments.size() == 3 && "selecttriangles assert");
        for(auto j = plsegments.begin(); j != plsegments.end(); j++){
            Segment plseg = segments[*j];
            set<int> inplanar = plseg.getinPlanar(),
                inplanar01 = plseg.getinPlanar01(),
                inplanar10 = plseg.getinPlanar10();
            inplanar.erase(pl.getid());
            inplanar01.erase(pl.getid());
            inplanar10.erase(pl.getid());
            plseg.setinPlanar(inplanar);
            plseg.setinPlanar01(inplanar01);
            plseg.setinPlanar10(inplanar10);
            plseg.setinYinset(-2);
            Point p0 = points[plseg[0]],
                p1 = points[plseg[1]];
            set<int> inSegment0 = p0.getinSegment(),
                inSegment1 = p1.getinSegment();
            inSegment0.erase(plseg.getid());
            inSegment1.erase(plseg.getid());
            p0.setinSegment(inSegment0);
            p1.setinSegment(inSegment1);
            if(inSegment0.empty()){
                p0.setinYinset(-2);
                existpoints.erase(p0.getid());
            }
            if(inSegment1.empty()){
                p1.setinYinset(-2);
                existpoints.erase(p1.getid());
            }
            if(inplanar.empty()){
                plseg.setinYinset(-2);
                plseg.setinPlanar01(set<int>());
                plseg.setinPlanar10(set<int>());
                plseg.setinPlanar(set<int>());
                existsegments.erase(plseg.getid());
            }
        }
        planars[*i].setinYinset(-2);
        planars[*i].setinFace(-2);
        planars[*i].setexistpoints(set<int>());
        planars[*i].setexistsegments(set<int>());
        existplanars.erase(*i);
    }
}

void Data::past(){
    existfaces.clear();
    FindNearTriangle functor;
    vector<int> face;
    set<int> remain = existplanars;
    stack<int> s;
    while(!remain.empty()){
        if(s.empty()){
            if(face.size() != 0){
                Face f(face, facesnum++);
                existfaces.insert(f.getid());
                face.clear();
            }
            s.push(*remain.begin());
            remain.erase(remain.begin());
        }
        int k = s.top();
        s.pop();
        face.push_back(k);
        Planar pl = planars[k];
        vector<int> neartriangle = functor(pl);
        if(remain.find(neartriangle[0]) != remain.end()){
            remain.erase(neartriangle[0]);
            s.push(neartriangle[0]);
        }
        if(remain.find(neartriangle[1]) != remain.end()){
            remain.erase(neartriangle[1]);
            s.push(neartriangle[1]);
        }
        if(remain.find(neartriangle[2]) != remain.end()){
            remain.erase(neartriangle[2]);
            s.push(neartriangle[2]);
        }
        if(remain.empty()){
            while(!s.empty()){
                int temp = s.top();
                s.pop();
                face.push_back(temp);
            }
            if(face.size() != 0){
                Face f(face, facesnum++);
                existfaces.insert(f.getid());
                face.clear();
            }
        }
    }
}


void Data::print(ostream& os, const Yinset& y){
    clear();
    load(y);
    map<int, int> printv;
    map<int, int> printvn;
    int kv = 1;
    for(auto i = existpoints.begin(); i != existpoints.end(); i++){
        os << "v " << points[*i] << endl;
        printv.insert(make_pair(*i, kv++));
    }
    //os << endl;
    int kvn = 1;
    for(auto i = existplanars.begin(); i != existplanars.end(); i++){
        Planar pl = planars[*i];
        os << "vn " << pl.getnormaldirect() << endl;
        printvn.insert(make_pair(*i, kvn++));
    }
    //os << endl;
    for(auto i = existplanars.begin(); i != existplanars.end(); i++){
        Planar pl = planars[*i];
        vector<int> vp = pl.getpoints();
        os << "f "
           << printv[vp[0]] << "/" << 1 << "/" << printvn[*i] << " "
           << printv[vp[1]] << "/" << 1 << "/" << printvn[*i] << " "
           << printv[vp[2]] << "/" << 1 << "/" << printvn[*i] << endl;
    }
    clear();
}

int Data::import(istream& is){
    clear();
    int yinsetid = yinsetsnum++;
    int startpointsid = Data::pointsnum;
    map<int, int> printv;
    map<int, Direction> printvn;
    map<pair<int, int>, int> printseg;
    int kv = 1;
    int kvn = 1;
    string ism,
        sv("v"),
        svn("vn"),
        sf("f"),
        sm("#");
    int s;
    while(is >> ism){
        if(ism == sm){
            is.ignore(256, '\n');
        }
        if(ism == sv){
            Point p;
            is >> p;
            p.setid(pointsnum++);
            existpoints.insert(p.getid());
            if(p > farpoint){
                farpoint[0] = p[0];
                farpoint[1] = p[1];
                farpoint[2] = p[2];
            }
            printv[kv++] = p.getid();
            existpoints.insert(p.getid());
        }
        else if(ism == svn){
            Direction d;
            is >> d;
            printvn.insert(make_pair(kvn++, d));
        }
        else if(ism == sf){
            int id = planarsnum++;
            vector<int> vp;
            vp.resize(3);
            //int i;
            Direction normal;
            for(int j = 0; j < 3; j++){
                is >> s;
                //vp[j] = printv[s[0] - static_cast<int>('0')];
                vp[j] = s + startpointsid - 1;
                char x;
                is >> x;
                is >> s;
                is >> x;
                is >> s;
                normal = normal + //printvn[s[4] -  static_cast<int>('0')];
                    printvn[s];
            }
            Direction d1 = points[vp[1]] - points[vp[0]],
                d2 = points[vp[2]] - points[vp[1]];
            if(d1.cross(d2).dot(normal) < 0){
                int temp = vp[0];
                vp[0] = vp[1];
                vp[1] = temp;
            }
            Segment seg0(vp[0], vp[1]),
                seg1(vp[1], vp[2]),
                seg2(vp[2], vp[0]);
            //set<int> s;
            auto it = printseg.find(make_pair(seg0[0], seg0[1]));
            if(it != printseg.end()){
                int id = it->second;
                seg0 = segments[id];
            }
            else{
                seg0.setid(segmentsnum++);
                printseg[make_pair(seg0[0], seg0[1])] = seg0.getid();
                //existsegments.insert(seg0.getid());
            }
            it = printseg.find(make_pair(seg1[0], seg1[1]));
            if(it != printseg.end()){
                int id = it->second;
                seg1 = segments[id];
            }
            else{
                seg1.setid(segmentsnum++);
                printseg[make_pair(seg1[0], seg1[1])] = seg1.getid();
                //existsegments.insert(seg1.getid());
            }
            it = printseg.find(make_pair(seg2[0], seg2[1]));
            if(it != printseg.end()){
                int id = it->second;
                seg2 = segments[id];
            }
            else{
                seg2.setid(segmentsnum++);
                printseg[make_pair(seg2[0], seg2[1])] = seg2.getid();
                //existsegments.insert(seg2.getid());
            }
            if(seg0[0] == vp[0]){
                set<int> inPlanar = seg0.getinPlanar(),
                    inPlanar01 = seg0.getinPlanar01();
                inPlanar.insert(id);
                inPlanar01.insert(id);
                seg0.setinPlanar(inPlanar);
                seg0.setinPlanar01(inPlanar01);
            }
            else{
                set<int> inPlanar = seg0.getinPlanar(),
                    inPlanar10 = seg0.getinPlanar10();
                inPlanar.insert(id);
                inPlanar10.insert(id);
                seg0.setinPlanar(inPlanar);
                seg0.setinPlanar10(inPlanar10);
            }
            if(seg1[0] == vp[1]){
                set<int> inPlanar = seg1.getinPlanar(),
                    inPlanar01 = seg1.getinPlanar01();
                inPlanar.insert(id);
                inPlanar01.insert(id);
                seg1.setinPlanar(inPlanar);
                seg1.setinPlanar01(inPlanar01);
            }
            else{
                set<int> inPlanar = seg1.getinPlanar(),
                    inPlanar10 = seg1.getinPlanar10();
                inPlanar.insert(id);
                inPlanar10.insert(id);
                seg1.setinPlanar(inPlanar);
                seg1.setinPlanar10(inPlanar10);
            }
            if(seg2[0] == vp[2]){
                set<int> inPlanar = seg2.getinPlanar(),
                    inPlanar01 = seg2.getinPlanar01();
                inPlanar.insert(id);
                inPlanar01.insert(id);
                seg2.setinPlanar(inPlanar);
                seg2.setinPlanar01(inPlanar01);
            }
            else{
                set<int> inPlanar = seg2.getinPlanar(),
                    inPlanar10 = seg2.getinPlanar10();
                inPlanar.insert(id);
                inPlanar10.insert(id);
                seg2.setinPlanar(inPlanar);
                seg2.setinPlanar10(inPlanar10);
            }
            vector<int> vseg;
            vseg.push_back(seg0.getid());
            vseg.push_back(seg1.getid());
            vseg.push_back(seg2.getid());
            existsegments.insert(seg0.getid());
            existsegments.insert(seg1.getid());
            existsegments.insert(seg2.getid());
            Planar pl(vp, vseg, id, -1, yinsetsnum);
            existplanars.insert(pl.getid());
        }
    }
    farpoint += Direction(1, 1, 1);
    past();
    vector<int> faces(existfaces.size());
    copy(Data::existfaces.begin(), Data::existfaces.end(), faces.begin());
    Yinset anwser(faces, yinsetid);
    anwser.generatorhassmap();
    clear();
    return anwser.getid();
}