//
// Created by erick on 9/7/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_INPUT_H
#define MORDEROPENGLUDEMYTUTORIAL_INPUT_H

#include <stdlib.h>

class Input {
private:
    double lastX = 0;
    double lastY = 0;
    double XChange = 0;
    double YChange = 0;
    double XWheelChange = 0;
    double YWheelChange = 0;
    bool keys[1024] {false};
    bool invertedX = false;
    bool invertedY = false;
    bool mouseFirstMoved = true;
    bool mouseLastMoved = false;

public:
    double getXChange() {

        return XChange;
    }

    double getYChange() {
        return YChange;
    }

    bool *getKeys() {
        return keys;
    }

    bool isInvertedX() const {
        return invertedX;
    }

    void setInvertedX(bool invertedX) {
        Input::invertedX = invertedX;
    }

    bool isInvertedY() const {
        return invertedY;
    }

    void setInvertedY(bool invertedY) {
        Input::invertedY = invertedY;
    }

    bool isMouseFirstMoved() const {
        return mouseFirstMoved;
    }

    void setMouseFirstMoved(bool mouseFirstMoved) {
        Input::mouseFirstMoved = mouseFirstMoved;
    }

    bool isMouseLastMoved() const {
        return mouseLastMoved;
    }

    void setMouseLastMoved(bool mouseLastMoved) {
        Input::mouseLastMoved = mouseLastMoved;
    }

    double getLastX() const {
        return lastX;
    }

    void setLastX(double lastX) {
        Input::lastX = lastX;
    }

    double getLastY() const {
        return lastY;
    }

    void setLastY(double lastY) {
        Input::lastY = lastY;
    }

    void setXChange(double XChange) {
        Input::XChange = XChange;
    }

    void setYChange(double YChange) {
        Input::YChange = YChange;
    }

    double getXWheelChange() {
        return XWheelChange;
    }

    double getYWheelChange() {
        return YWheelChange;
    }

    void setXWheelChange(double XWheelChange) {
        Input::XWheelChange = XWheelChange;
    }

    void setYWheelChange(double YWheelChange) {
        Input::YWheelChange = YWheelChange;
    }
};


#endif //MORDEROPENGLUDEMYTUTORIAL_INPUT_H
