#ifndef YINSET_BOOLEAN
#define YINSET_BOOLEAN

#include"Data.h"
#include"HassNode.h"
#include<vector>
#include<utility>
#include<map>
#include"STLHead.h"

class HassNode;
class Point;

class Yinset{
    std::vector<int> faces;
    std::vector<HassNode> hassmap;
    int id;
    int type;
    std::map<Point, std::set<int>> pastpoints;
public:
    explicit Yinset(std::vector<int> vf = std::vector<int>(), int identity = -1, int t = -1) : faces(vf), id(identity), type(t) {
        if(identity != -1){
            if(id >= Data::yinsets.size())
                Data::yinsets.resize(1 + id);
            Data::yinsets[identity] = *this;
        }
    }
    Yinset(const Yinset& y) //: faces(y.faces), hassmap(y.hassmap),
    // id(y.id), type(y.type), pastpoints(y.pastpoints)
        {
            *this = y;
        }
    Yinset& operator=(const Yinset& y){
        faces = y.faces;
        hassmap = y.hassmap;
        id = y.id;
        type = y.type;
        pastpoints = y.pastpoints;
        return *this;
/*
        Yinset temp(y);
        std::swap(*this, temp);
        return *this;
        */
    }
    std::vector<int> getfaces() const {
        return faces;
    }
    void setfaces(const std::vector<int>& vf){
        faces = vf;
        if(id != -1){
            if(id >= Data::yinsets.size())
                Data::yinsets.resize(1 + id);
            Data::yinsets[id] = *this;
        }
    }
    std::vector<HassNode> gethassmap() const {
        return hassmap;
    }
    void sethassmap(const std::vector<HassNode>& vh){
        hassmap = vh;
        if(id != -1){
            if(id >= Data::yinsets.size())
                Data::yinsets.resize(1 + id);
            Data::yinsets[id] = *this;
        }
    }
    int getid() const {
        return id;
    }
    void setid(const int i){
        id = i;
        if(id != -1){
            if(id >= Data::yinsets.size())
                Data::yinsets.resize(1 + id);
            Data::yinsets[id] = *this;
        }
    }
    int gettype() const {
        return type;
    }
    void settype(const int i){
        type = i;
        if(id != -1){
            if(id >= Data::yinsets.size())
                Data::yinsets.resize(1 + id);
            Data::yinsets[id] = *this;
        }
    }
    std::map<Point, std::set<int>> getpastpoints() const {
        return pastpoints;
    }
    void setpastpoints(){
        pastpoints = Data::pastpoints;
    }
    void generatorhassmap();
    Yinset meet(const Yinset&) const;
    Yinset complement() const;
    Yinset join(const Yinset&) const;
    friend std::ostream& operator<<(std::ostream& os, const Yinset& y){
        Data::print(os, y);
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Yinset& y){
        int i = Data::import(is);
        y = Data::yinsets[i];
        return is;
    }
};

#endif