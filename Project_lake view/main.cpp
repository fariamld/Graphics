#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265f

void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);

    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * PI * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }

    glEnd();
}

void drawEllipse(float cx, float cy, float rx, float ry, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);

    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * PI * float(i) / float(num_segments);
        float x = rx * cosf(theta);
        float y = ry * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }

    glEnd();
}

void drawTree(float x, float y, float scale) {
    // Tree trunk
    glColor3f(0.025f, 0.025f, 0.02f);

    glBegin(GL_QUADS);
        glVertex2f(x - 7.0f * scale, y);
        glVertex2f(x + 7.0f * scale, y);
        glVertex2f(x + 9.0f * scale, y + 65.0f * scale);
        glVertex2f(x - 9.0f * scale, y + 65.0f * scale);
    glEnd();

    glColor3f(0.015f, 0.025f, 0.015f);

    drawEllipse(x, y + 105.0f * scale, 45.0f * scale, 48.0f * scale, 35);
    drawEllipse(x - 32.0f * scale, y + 92.0f * scale, 32.0f * scale, 34.0f * scale, 35);
    drawEllipse(x + 32.0f * scale, y + 92.0f * scale, 32.0f * scale, 34.0f * scale, 35);
    drawEllipse(x - 18.0f * scale, y + 122.0f * scale, 30.0f * scale, 32.0f * scale, 35);
    drawEllipse(x + 18.0f * scale, y + 122.0f * scale, 30.0f * scale, 32.0f * scale, 35);

    drawEllipse(x, y + 78.0f * scale, 48.0f * scale, 28.0f * scale, 35);
}

void drawBackgroundSky() {
    glBegin(GL_QUADS);
        glColor3f(0.35f, 0.38f, 0.42f);
        glVertex2f(0.0f, 720.0f);
        glVertex2f(1280.0f, 720.0f);

        glColor3f(0.85f, 0.88f, 0.90f);
        glVertex2f(1280.0f, 300.0f);
        glVertex2f(0.0f, 300.0f);
    glEnd();
}

void drawSun() {
    glColor4f(1.0f, 1.0f, 1.0f, 0.15f);
    drawCircle(640.0f, 400.0f, 80.0f, 50);

    glColor4f(1.0f, 1.0f, 1.0f, 0.4f);
    drawCircle(640.0f, 400.0f, 50.0f, 50);

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    drawCircle(640.0f, 400.0f, 25.0f, 50);
}

void drawClouds() {
    glColor3f(0.55,0.58,0.58);

    drawCircle(680.0f, 410.0f, 35.0f, 30);
    drawCircle(610.0f, 420.0f, 45.0f, 30);
    drawCircle(640.0f, 440.0f, 40.0f, 30);
}

void drawRiver() {
    glBegin(GL_QUADS);
        glColor3f(0.7f, 0.75f, 0.75f);
        glVertex2f(0.0f, 300.0f);
        glVertex2f(1280.0f, 300.0f);

        glColor3f(0.3f, 0.3f, 0.3f);
        glVertex2f(1280.0f, 240.0f);
        glVertex2f(0.0f, 240.0f);
    glEnd();
}

void drawWetRoad() {
    glBegin(GL_QUADS);
        glColor3f(0.08f, 0.08f, 0.08f);
        glVertex2f(0.0f, 240.0f);
        glVertex2f(1280.0f, 240.0f);

        glColor3f(0.15f, 0.15f, 0.15f);
        glVertex2f(1280.0f, 0.0f);
        glVertex2f(0.0f, 0.0f);
    glEnd();
}

void drawWetRoadReflection() {
    glBegin(GL_POLYGON);
        glColor4f(1.0f, 1.0f, 0.9f, 0.4f);
        glVertex2f(580.0f, 240.0f);
        glVertex2f(700.0f, 240.0f);

        glColor4f(0.8f, 0.8f, 0.8f, 0.05f);
        glVertex2f(900.0f, 0.0f);
        glVertex2f(380.0f, 0.0f);
    glEnd();
}

void drawBridge() {
    glColor3f(0.1f, 0.1f, 0.1f);

    glBegin(GL_POLYGON);
        glVertex2f(0.0f, 450.0f);
        glVertex2f(600.0f, 320.0f);
        glVertex2f(600.0f, 290.0f);
        glVertex2f(0.0f, 380.0f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(100.0f, 400.0f);
        glVertex2f(130.0f, 400.0f);
        glVertex2f(130.0f, 260.0f);
        glVertex2f(100.0f, 260.0f);

        glVertex2f(350.0f, 345.0f);
        glVertex2f(380.0f, 345.0f);
        glVertex2f(380.0f, 250.0f);
        glVertex2f(350.0f, 250.0f);
    glEnd();
}

void drawTreesAndShoreline() {
    glColor3f(0.04f, 0.05f, 0.04f);

    glBegin(GL_QUADS);
        glVertex2f(0.0f, 255.0f);
        glVertex2f(1280.0f, 255.0f);
        glVertex2f(1280.0f, 235.0f);
        glVertex2f(0.0f, 235.0f);
    glEnd();

    // Trees from the left side
    drawTree(45.0f, 235.0f, 0.45f);
    drawTree(135.0f, 235.0f, 0.55f);
    drawTree(245.0f, 235.0f, 0.50f);
    drawTree(370.0f, 235.0f, 0.62f);
    drawTree(500.0f, 235.0f, 0.50f);


    // Trees continue again on the right side
    drawTree(835.0f, 235.0f, 0.55f);
    drawTree(930.0f, 235.0f, 0.65f);
    drawTree(1035.0f, 235.0f, 0.75f);
    drawTree(1150.0f, 235.0f, 0.85f);
    drawTree(1255.0f, 235.0f, 0.65f);
}

void drawOverheadWires() {
    glColor4f(0.1f, 0.1f, 0.1f, 0.8f);
    glLineWidth(1.5f);

    glBegin(GL_LINES);
        glVertex2f(0.0f, 420.0f);
        glVertex2f(1280.0f, 400.0f);

        glVertex2f(0.0f, 400.0f);
        glVertex2f(1280.0f, 420.0f);
    glEnd();
}

void drawStreetLights() {
    glColor3f(0.1f, 0.1f, 0.1f);
    glLineWidth(4.0f);

    glBegin(GL_LINES);
        glVertex2f(150.0f, 240.0f);
        glVertex2f(195.0f, 470.0f);

        // Left lamp head
        glVertex2f(195.0f, 470.0f);
        glVertex2f(155.0f, 495.0f);

        // Right streetlight
        glVertex2f(1180.0f, 240.0f);
        glVertex2f(1130.0f, 460.0f);

        // Right lamp head
        glVertex2f(1130.0f, 460.0f);
        glVertex2f(1170.0f, 480.0f);
    glEnd();
}



void drawCar(float x, float y, float scale) {
    // Car shadow/reflection on wet road
    glColor4f(0.02f, 0.02f, 0.02f, 0.45f);
    glBegin(GL_POLYGON);
        glVertex2f(x - 80.0f * scale, y - 12.0f * scale);
        glVertex2f(x + 95.0f * scale, y - 12.0f * scale);
        glVertex2f(x + 120.0f * scale, y - 35.0f * scale);
        glVertex2f(x - 105.0f * scale, y - 35.0f * scale);
    glEnd();

    glColor3f(0.75f, 0.05f, 0.03f);
    glBegin(GL_POLYGON);
        glVertex2f(x - 90.0f * scale, y);
        glVertex2f(x + 90.0f * scale, y);
        glVertex2f(x + 110.0f * scale, y + 35.0f * scale);
        glVertex2f(x + 70.0f * scale, y + 50.0f * scale);
        glVertex2f(x - 65.0f * scale, y + 50.0f * scale);
        glVertex2f(x - 105.0f * scale, y + 32.0f * scale);
    glEnd();

    // Car roof, slightly darker red
    glColor3f(0.55f, 0.02f, 0.02f);
    glBegin(GL_POLYGON);
        glVertex2f(x - 45.0f * scale, y + 50.0f * scale);
        glVertex2f(x + 45.0f * scale, y + 50.0f * scale);
        glVertex2f(x + 25.0f * scale, y + 90.0f * scale);
        glVertex2f(x - 25.0f * scale, y + 90.0f * scale);
    glEnd();

    // Windows, light bluish gray
    glColor3f(0.55f, 0.75f, 0.85f);
    glBegin(GL_QUADS);
        // Left window
        glVertex2f(x - 38.0f * scale, y + 55.0f * scale);
        glVertex2f(x - 5.0f * scale, y + 55.0f * scale);
        glVertex2f(x - 8.0f * scale, y + 82.0f * scale);
        glVertex2f(x - 25.0f * scale, y + 82.0f * scale);

        // Right window
        glVertex2f(x + 5.0f * scale, y + 55.0f * scale);
        glVertex2f(x + 38.0f * scale, y + 55.0f * scale);
        glVertex2f(x + 25.0f * scale, y + 82.0f * scale);
        glVertex2f(x + 8.0f * scale, y + 82.0f * scale);
    glEnd();

    // Small white window divider
    glColor3f(0.9f, 0.9f, 0.9f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(x, y + 55.0f * scale);
        glVertex2f(x, y + 84.0f * scale);
    glEnd();

    // Headlight
    glColor3f(1.0f, 0.95f, 0.45f);
    glBegin(GL_QUADS);
        glVertex2f(x + 88.0f * scale, y + 22.0f * scale);
        glVertex2f(x + 108.0f * scale, y + 25.0f * scale);
        glVertex2f(x + 108.0f * scale, y + 35.0f * scale);
        glVertex2f(x + 88.0f * scale, y + 34.0f * scale);
    glEnd();

    // Tail light
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(x - 105.0f * scale, y + 22.0f * scale);
        glVertex2f(x - 88.0f * scale, y + 22.0f * scale);
        glVertex2f(x - 88.0f * scale, y + 34.0f * scale);
        glVertex2f(x - 105.0f * scale, y + 34.0f * scale);
    glEnd();

    // Wheels
    glColor3f(0.005f, 0.005f, 0.005f);
    drawCircle(x - 55.0f * scale, y, 22.0f * scale, 30);
    drawCircle(x + 55.0f * scale, y, 22.0f * scale, 30);

    // Wheel inner circles
    glColor3f(0.45f, 0.45f, 0.45f);
    drawCircle(x - 55.0f * scale, y, 10.0f * scale, 25);
    drawCircle(x + 55.0f * scale, y, 10.0f * scale, 25);
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    drawBackgroundSky();
    drawSun();
    drawClouds();
    drawRiver();

    // Trees are behind bridge and road
    drawTreesAndShoreline();

    drawWetRoad();
    drawWetRoadReflection();
    drawCar(300.0f, 115.0f, 1.0f);
    drawCar(950.0f, 165.0f, 0.55f);
    drawCar(650.0f, 150.0f, 0.75f);
    drawBridge();

    drawOverheadWires();
    drawStreetLights();

    glutSwapBuffers();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1280.0, 0.0, 720.0);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Atmospheric Bridge Scenery - 1280x720");

    init();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
