#include <utility>

//
// Created by erick on 9/19/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_ANIMATION_H
#define MORDEROPENGLUDEMYTUTORIAL_ANIMATION_H

#include <vector>
#include "KeyFrame.h"

/**
 *
 * * Represents an animation that can applied to an {@link AnimatedModel} . It
 * contains the length of the animation in seconds, and a list of
 * {@link KeyFrame}s.
 *
 * @author Karl
 *
 *
 */
class Animation {
public:
    Animation():length(0){};
    /**
     *
     * @param lengthInSeconds
     *            - the total length of the animation in seconds.
     * @param frames
     *            - all the keyframes for the animation, ordered by time of
     *            appearance in the animation.
     */
    Animation(float lengthInSeconds, std::vector<KeyFrame> frames):
    length(lengthInSeconds),
    keyFrames(std::move(frames)){}

    const float getLength() const {
        return length;
    }

    const std::vector<KeyFrame> &getKeyFrames() const {
        return keyFrames;
    }

private:
    float length; //in seconds
    std::vector<KeyFrame> keyFrames;

};

#endif //MORDEROPENGLUDEMYTUTORIAL_ANIMATION_H
