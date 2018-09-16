#include <utility>

//
// Created by erick on 9/16/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_LINE_H
#define MORDEROPENGLUDEMYTUTORIAL_LINE_H


#include "Point.h"

class Line : Collider<std::pair<Point,Point>>{

    Line(): Collider(TYPE_LINE){
        this->m_parent.first.SetParent(Vector3f());
        this->m_parent.second.SetParent(Vector3f());
    };
    Line(const Line &line): Collider(TYPE_LINE){
        this->m_parent = line.m_parent;
    }
    Line(Point p1,Point p2): Collider(TYPE_LINE){
        this->m_parent.first = std::move(p1);
        this->m_parent.second = std::move(p2);
    }
    Line(Vector3f p1,Vector3f p2): Collider(TYPE_LINE){
        this->m_parent.first.SetParent(std::move(p1));
        this->m_parent.second.SetParent(std::move(p2));
    }

    IntersectData IntersectPoint(Point& point) const;

    template <class OtherParent>
    IntersectData Intersect(const Collider<OtherParent>& other) const;

    Vector3f ToVector() {
        return (m_parent.second.GetParent() - m_parent.first.GetParent());
    }

    float getLength(){
        (m_parent.second.GetParent() - m_parent.first.GetParent()).Length();
    }

    float getLengthSquared(){
        (m_parent.second.GetParent() - m_parent.first.GetParent()).LengthSq();
    }
};


#endif //MORDEROPENGLUDEMYTUTORIAL_LINE_H
