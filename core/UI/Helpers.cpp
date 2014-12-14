#include "Helpers.h"
#include <GL/gl.h>
#include <cmath>

namespace core {

    void drawCircle(float cx, float cy,float cz, float r, int num_segments) {
        glBegin(GL_LINE_LOOP);
        for (int ii = 0; ii < num_segments; ii++) {
            float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments); //get the current angle
            float x = r * cosf(theta); //calculate the x component
            float y = r * sinf(theta); //calculate the y component
            glVertex3f(x + cx, y + cy,cz); //output vertex
        }
        glEnd();
    }

    void drawQUAD(const int x, const int y,const int z, const int width, const int height) {
        glBegin(GL_QUADS);
        glVertex3d(x, y, z);
        glVertex3d(x + width, y, z);

        glVertex3d(x + width, y + height, z);
        glVertex3d(x, y + height, z);

        glVertex3d(x, y + height, z);
        glVertex3d(x, y, z);

        glVertex3d(x + width, y, z);
        glVertex3d(x + width, y + height, z);
        glEnd();
    }
}