#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

static unsigned int numLines = 0;

struct point
{
    float x;
    float y;
};
typedef point Point;
struct color
{
    float Red;
    float Green;
    float Blue;
    float Alpha;
};
typedef color Color;

struct rect
{
    Point topLeft;
    Point topRight;
    Point botLeft;
    Point botRight;
    Point center;
    float scale;
    float rotate;
};
typedef rect Rect;

int main(void)
{
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono;      // nanoseconds, system_clock, seconds

    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(700, 700, "SquareJumble", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "Error! glewInit failed\n";

    std::cout << glGetString(GL_VERSION) << std::endl;

    const unsigned int SSIZE(50);

    float R = 0.35f;
    float Rdir = .01f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // Render here
        glClear(GL_COLOR_BUFFER_BIT);
        //float T = .008f;
        // grow and shrink the zone of confusion
        R += Rdir;
        if (R > .45f || R < .05f)
        {
            Rdir = -Rdir;
        }
        float D = 0.03f;
        float fsize = float(SSIZE);
        for (int i = 0; i < SSIZE; i++)
        {
            for (int j = 0; j < SSIZE; j++)
            {
                Color lc = { 1.0f, 1.0f, 1.0f, 1.0f };
                Point center = { float(i) / fsize * 1.6f - .8f, float(j) / fsize * 1.6f - .8f };
                float scale = 1.0f / (fsize);
                center.x = float(i) / fsize * 1.6f - .8f;
                center.y = float(j) / fsize * 1.6f - .8f;
                scale = 1.0f / (fsize);
                float dist = (center.x + 1.0f / fsize) * (center.x + 1.0f / fsize) +
                    (center.y + 1.0f / fsize) * (center.y + 1.0f / fsize);
                float O = ((R - dist) > 0) ? 4.0f * (R - dist) : 0.0f;
                center.x += ((float(rand() % 100) / 100.0f) - 0.5f) * O * D;
                center.y += ((float(rand() % 100) / 100.0f) - 0.5f) * O * D;
                float rot = ((R - dist) > 0) ? 4.0f * (R - dist) : 0.0f;
                float rotate = (float(rand() % 100) / 100.0f - 0.5f) * rot;
                float sinr = sin(rotate + 45.0f / 360.0f * 2.0f * 3.14159265359f);
                float cosr = cos(rotate + 45.0f / 360.0f * 2.0f * 3.14159265359f);
                // draw top of rect
                float x1 = center.x - scale * sinr;
                float y1 = center.y + scale * cosr;
                float x2 = center.x + scale * cosr;
                float y2 = center.y + scale * sinr;
                glBegin(GL_LINES);
                glVertex2f(x1, y1);
                glVertex2f(x2, y2);
                glEnd();
                x1 = center.x + scale * cosr;
                y1 = center.y + scale * sinr;
                x2 = center.x + scale * sinr;
                y2 = center.y - scale * cosr;
                glBegin(GL_LINES);
                glVertex2f(x1, y1);
                glVertex2f(x2, y2);
                glEnd();
                x1 = center.x + scale * sinr;
                y1 = center.y - scale * cosr;
                x2 = center.x - scale * cosr;
                y2 = center.y - scale * sinr;
                glBegin(GL_LINES);
                glVertex2f(x1, y1);
                glVertex2f(x2, y2);
                glEnd();
                x1 = center.x - scale * cosr;
                y1 = center.y - scale * sinr;
                x2 = center.x - scale * sinr;
                y2 = center.y + scale * cosr;
                glBegin(GL_LINES);
                glVertex2f(x1, y1);
                glVertex2f(x2, y2);
                glEnd();
            }
        }
        glfwSwapBuffers(window);
        std::this_thread::sleep_for(100ms);
        //std::cin.get();
        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
