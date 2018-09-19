#include <utility>

//
// Created by erick on 9/16/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_LINE_H
#define MORDEROPENGLUDEMYTUTORIAL_LINE_H


#include "Point.h"

class Line : Collider{

    Line(): Collider(TYPE_LINE){
        start = Point();
        end = Point();
    };
    Line(const Line &line): Collider(TYPE_LINE){
        start = line.start;
        end = line.end;
        this->m_parent = line.m_parent;
    }
    Line(Point p1,Point p2): Collider(TYPE_LINE){
        start = std::move(p1);
        end = std::move(p2);
    }
    Line(glm::vec3 p1,glm::vec3 p2): Collider(TYPE_LINE){
        start = Point(p1);
        end = Point(p2);
    }

    IntersectData IntersectPoint(Point& point) const;

    IntersectData Intersect(const Collider& other) const override;

    glm::vec3 ToVector() {
        return (end.m_point - start.m_point);
    }

    float getLength(){
        glm::length(end.m_point - start.m_point);
    }

    float getLengthSquared(){
        glm::length2(end.m_point - start.m_point);
    }

private:
    Point start;
    Point end;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_LINE_H
