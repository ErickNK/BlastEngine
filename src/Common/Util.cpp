/*
 * Copyright (C) 2014 Benny Bobaganoosh
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>
#include "GLFW/glfw3.h"
#include "Util.h"

void Util::Sleep(unsigned int seconds)
{
    sleep(seconds);
}

std::vector<std::string> Util::Split(const std::string& s, char delim)
{
    std::vector<std::string> elems;

    const char* cstr = s.c_str();
    auto strLength = (unsigned int)s.length();
    unsigned int start = 0;
    unsigned int end = 0;

    while(end <= strLength)
    {
        while(end <= strLength)
        {
            if(cstr[end] == delim)
                break;
            end++;
        }

        elems.push_back(s.substr(start, end - start));
        start = end + 1;
        end = start;
    }

    return elems;
}

float Util::barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos) {
    float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
    float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
    float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
    float l3 = 1.0f - l1 - l2;
    return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

int Util::getDirFiles (std::string dir, std::vector<std::string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        std::cout << "Error(" << errno << ") opening " << dir << std::endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(std::string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

glm::mat4 Util::fromAssimp(aiMatrix4x4 m)
{
    glm::mat4 matrix;

    matrix[0][0] = m.a1;
    matrix[0][1] = m.a2;
    matrix[0][2] = m.a3;
    matrix[0][3] = m.a4;

    matrix[1][0] = m.b1;
    matrix[1][1] = m.b2;
    matrix[1][2] = m.b3;
    matrix[1][3] = m.b4;

    matrix[2][0] = m.c1;
    matrix[2][1] = m.c2;
    matrix[2][2] = m.c3;
    matrix[2][3] = m.c4;

    matrix[3][0] = m.d1;
    matrix[3][1] = m.d2;
    matrix[3][2] = m.d3;
    matrix[3][3] = m.d4;

    return matrix;
}