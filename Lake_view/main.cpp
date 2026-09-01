#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265f

// ============================================================
// ANIMATION VARIABLES
// ============================================================

float carX1 = -220.0f;
float carX2 = 500.0f;
float carX3 = 1050.0f;

float carSpeed1 = 2.2f;
float carSpeed2 = 1.5f;
float carSpeed3 = 2.8f;

float waterMove = 0.0f;

// Cloud animation values.
float cloudMove = 0.0f;
float cloudSpeed = 0.6f;

// Cars moving on the bridge.
float bridgeCarX1 = 80.0f;
float bridgeCarX2 = 300.0f;
float bridgeCarX3 = 520.0f;

float bridgeCarSpeed1 = 1.0f;
float bridgeCarSpeed2 = 1.3f;
float bridgeCarSpeed3 = 1.6f;


// ============================================================
// BASIC SHAPES
// ============================================================

void drawCircle(float cx, float cy, float r, int segments)
{
    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(cx, cy);

    for (int i = 0; i <= segments; i++)
    {
        float theta = 2.0f * PI * i / segments;

        float x = r * cosf(theta);
        float y = r * sinf(theta);

        glVertex2f(cx + x, cy + y);
    }

    glEnd();
}


void drawEllipse(float cx, float cy,
                 float rx, float ry,
                 int segments)
{
    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(cx, cy);

    for (int i = 0; i <= segments; i++)
    {
        float theta = 2.0f * PI * i / segments;

        float x = rx * cosf(theta);
        float y = ry * sinf(theta);

        glVertex2f(cx + x, cy + y);
    }

    glEnd();
}


// ============================================================
// SKY
// ============================================================

void drawBackgroundSky()
{
    glBegin(GL_QUADS);

    // Top: friend-style daytime sky
    glColor3f(0.53f, 0.81f, 0.98f);

    glVertex2f(0.0f, 720.0f);
    glVertex2f(1280.0f, 720.0f);

    // Bottom: same clear blue palette
    glColor3f(0.53f, 0.81f, 0.98f);

    glVertex2f(1280.0f, 250.0f);
    glVertex2f(0.0f, 250.0f);

    glEnd();
}


// ============================================================
// DAYTIME SUN
// ============================================================

void drawSun()
{
    // Warm yellow daytime glow
    glColor4f(1.0f, 0.90f, 0.20f, 0.10f);
    drawCircle(640.0f, 550.0f, 100.0f, 60);

    glColor4f(1.0f, 0.92f, 0.25f, 0.18f);
    drawCircle(640.0f, 550.0f, 75.0f, 60);

    glColor3f(1.0f, 0.75f, 0.05f);
    drawCircle(640.0f, 550.0f, 50.0f, 60);
}


// ============================================================
// CLOUDS
// ============================================================

void drawCloud(float x, float y, float scale)
{
    glColor4f(1.0f, 1.0f, 1.0f, 0.90f);

    drawEllipse(x, y, 55.0f * scale,
                25.0f * scale, 40);

    drawCircle(x - 35.0f * scale,
               y + 8.0f * scale,
               28.0f * scale, 40);

    drawCircle(x,
               y + 18.0f * scale,
               35.0f * scale, 40);

    drawCircle(x + 35.0f * scale,
               y + 5.0f * scale,
               27.0f * scale, 40);
}


void drawClouds()
{
    // Move every cloud to the right and wrap it around the screen.
    float x1 = fmod(630.0f + cloudMove, 1450.0f) - 150.0f;
    float x2 = fmod(300.0f + cloudMove, 1450.0f) - 150.0f;
    float x3 = fmod(1000.0f + cloudMove, 1450.0f) - 150.0f;
    float x4 = fmod(1150.0f + cloudMove, 1450.0f) - 150.0f;

    drawCloud(x1, 430.0f, 1.0f);
    drawCloud(x2, 555.0f, 0.75f);
    drawCloud(x3, 560.0f, 0.85f);
    drawCloud(x4, 470.0f, 0.60f);
}


// ============================================================
// TREE
// ============================================================

void drawTree(float x, float y, float scale)
{
    // ---------------- TRUNK ----------------

    glColor3f(0.20f, 0.12f, 0.05f);

    glBegin(GL_QUADS);

    glVertex2f(x - 7.0f * scale, y);
    glVertex2f(x + 7.0f * scale, y);

    glVertex2f(x + 10.0f * scale,
               y + 70.0f * scale);

    glVertex2f(x - 10.0f * scale,
               y + 70.0f * scale);

    glEnd();


    // ---------------- BRANCHES ----------------

    glLineWidth(5.0f);

    glBegin(GL_LINES);

    glVertex2f(x, y + 50.0f * scale);
    glVertex2f(x - 30.0f * scale,
               y + 90.0f * scale);

    glVertex2f(x, y + 55.0f * scale);
    glVertex2f(x + 30.0f * scale,
               y + 95.0f * scale);

    glEnd();


    // ---------------- LEAVES ----------------

    glColor3f(0.12f, 0.34f, 0.12f);

    drawEllipse(x,
                y + 105.0f * scale,
                48.0f * scale,
                48.0f * scale,
                40);

    drawEllipse(x - 32.0f * scale,
                y + 95.0f * scale,
                34.0f * scale,
                35.0f * scale,
                40);

    drawEllipse(x + 32.0f * scale,
                y + 95.0f * scale,
                34.0f * scale,
                35.0f * scale,
                40);

    drawEllipse(x - 18.0f * scale,
                y + 125.0f * scale,
                32.0f * scale,
                34.0f * scale,
                40);

    drawEllipse(x + 18.0f * scale,
                y + 125.0f * scale,
                32.0f * scale,
                34.0f * scale,
                40);

    drawEllipse(x,
                y + 80.0f * scale,
                52.0f * scale,
                30.0f * scale,
                40);
}


// ============================================================
// DISTANT TREES
// ============================================================

void drawBackgroundTrees()
{
    // Far dark tree line

    glColor3f(0.16f, 0.39f, 0.16f);

    for (int x = 0; x <= 1280; x += 45)
    {
        float height = 30.0f + (x % 70);

        drawEllipse((float)x,
                    250.0f + height * 0.5f,
                    40.0f,
                    height,
                    25);
    }
}


// ============================================================
// RIVER
// ============================================================

void drawRiver()
{
    glBegin(GL_QUADS);

    glColor3f(0.25f, 0.65f, 0.85f);

    glVertex2f(0.0f, 300.0f);
    glVertex2f(1280.0f, 300.0f);

    glColor3f(0.18f, 0.50f, 0.72f);

    glVertex2f(1280.0f, 235.0f);
    glVertex2f(0.0f, 235.0f);

    glEnd();


    // Full-width animated water-flow lines.
    glColor4f(0.85f, 0.95f, 1.0f, 0.55f);
    glLineWidth(2.0f);

    glBegin(GL_LINES);

    // Several rows make the whole river look active.
    for (int row = 0; row < 12; row++)
    {
        float y = 262.0f + row * 3.0f;
        float offset = fmod(waterMove + row * 40.0f, 180.0f);

        // Repeat short lines from the left edge to the right edge.
        for (float x = offset - 180.0f; x < 1280.0f; x += 180.0f)
        {
            glVertex2f(x, y);
            glVertex2f(x + 90.0f, y);
        }
    }

    glEnd();
}


// ============================================================
// SHORELINE
// ============================================================

void drawShoreline()
{
    glColor3f(0.32f, 0.65f, 0.25f);

    glBegin(GL_QUADS);

    glVertex2f(0.0f, 260.0f);
    glVertex2f(1280.0f, 260.0f);

    glVertex2f(1280.0f, 235.0f);
    glVertex2f(0.0f, 235.0f);

    glEnd();
}


// ============================================================
// TREES
// ============================================================

void drawTreesAndShoreline()
{
    drawShoreline();

    drawTree(35.0f, 235.0f, 0.42f);
    drawTree(115.0f, 235.0f, 0.52f);
    drawTree(210.0f, 235.0f, 0.45f);
    drawTree(310.0f, 235.0f, 0.60f);
    drawTree(420.0f, 235.0f, 0.52f);
    drawTree(510.0f, 235.0f, 0.60f);

    // Open middle

    drawTree(820.0f, 235.0f, 0.50f);
    drawTree(910.0f, 235.0f, 0.65f);
    drawTree(1010.0f, 235.0f, 0.72f);
    drawTree(1120.0f, 235.0f, 0.82f);
    drawTree(1230.0f, 235.0f, 0.60f);
}


// ============================================================
// BRIDGE
// ============================================================

void drawBridge()
{
    // Full-width bridge deck.
    glColor3f(0.45f, 0.45f, 0.48f);

    glBegin(GL_QUADS);
    glVertex2f(0.0f, 420.0f);
    glVertex2f(1280.0f, 420.0f);
    glVertex2f(1280.0f, 390.0f);
    glVertex2f(0.0f, 390.0f);
    glEnd();

    // Light-colored upper edge.
    glColor3f(0.65f, 0.65f, 0.68f);
    glLineWidth(7.0f);

    glBegin(GL_LINES);
    glVertex2f(0.0f, 420.0f);
    glVertex2f(1280.0f, 420.0f);
    glEnd();

    // Supports placed regularly under the complete bridge.
    glColor3f(0.60f, 0.60f, 0.63f);
    glBegin(GL_QUADS);

    glVertex2f(100.0f, 390.0f);
    glVertex2f(130.0f, 390.0f);
    glVertex2f(130.0f, 260.0f);
    glVertex2f(100.0f, 260.0f);

    glVertex2f(350.0f, 390.0f);
    glVertex2f(380.0f, 390.0f);
    glVertex2f(380.0f, 250.0f);
    glVertex2f(350.0f, 250.0f);

    glVertex2f(600.0f, 390.0f);
    glVertex2f(630.0f, 390.0f);
    glVertex2f(630.0f, 245.0f);
    glVertex2f(600.0f, 245.0f);

    glVertex2f(850.0f, 390.0f);
    glVertex2f(880.0f, 390.0f);
    glVertex2f(880.0f, 250.0f);
    glVertex2f(850.0f, 250.0f);

    glVertex2f(1100.0f, 390.0f);
    glVertex2f(1130.0f, 390.0f);
    glVertex2f(1130.0f, 260.0f);
    glVertex2f(1100.0f, 260.0f);

    glEnd();
}


// ============================================================
// WET ROAD
// ============================================================

void drawWetRoad()
{
    glBegin(GL_QUADS);

    glColor3f(0.045f, 0.05f, 0.055f);

    glVertex2f(0.0f, 240.0f);
    glVertex2f(1280.0f, 240.0f);

    glColor3f(0.12f, 0.13f, 0.14f);

    glVertex2f(1280.0f, 0.0f);
    glVertex2f(0.0f, 0.0f);

    glEnd();


    // Road lane markings

    glColor4f(1.0f, 0.9f, 0.6f, 0.75f);

    glLineWidth(3.0f);

    glBegin(GL_LINES);

    for (int x = 0; x < 1280; x += 160)
    {
        glVertex2f(x, 125.0f);
        glVertex2f(x + 80.0f, 125.0f);
    }

    glEnd();
}


// ============================================================
// ROAD REFLECTION
// ============================================================

void drawWetRoadReflection()
{
    // Main reflection

    glBegin(GL_POLYGON);

    glColor4f(1.0f, 1.0f, 0.92f, 0.16f);

    glVertex2f(570.0f, 240.0f);
    glVertex2f(710.0f, 240.0f);

    glColor4f(0.7f, 0.75f, 0.78f, 0.01f);

    glVertex2f(880.0f, 0.0f);
    glVertex2f(390.0f, 0.0f);

    glEnd();


    // Small wet streaks

    glColor4f(0.7f, 0.75f, 0.78f, 0.18f);

    glLineWidth(2.0f);

    glBegin(GL_LINES);

    glVertex2f(250.0f, 70.0f);
    glVertex2f(430.0f, 70.0f);

    glVertex2f(800.0f, 50.0f);
    glVertex2f(1050.0f, 50.0f);

    glVertex2f(100.0f, 180.0f);
    glVertex2f(300.0f, 180.0f);

    glVertex2f(900.0f, 170.0f);
    glVertex2f(1200.0f, 170.0f);

    glEnd();
}


// ============================================================
// STREET LIGHTS
// ============================================================

void drawStreetLights()
{
    glColor3f(0.06f, 0.065f, 0.07f);

    glLineWidth(5.0f);

    glBegin(GL_LINES);

    // Left pole
    glVertex2f(150.0f, 240.0f);
    glVertex2f(195.0f, 470.0f);

    // Left arm
    glVertex2f(195.0f, 470.0f);
    glVertex2f(155.0f, 495.0f);

    // Right pole
    glVertex2f(1180.0f, 240.0f);
    glVertex2f(1130.0f, 460.0f);

    // Right arm
    glVertex2f(1130.0f, 460.0f);
    glVertex2f(1170.0f, 480.0f);

    glEnd();


    // Lamps

    glColor4f(1.0f, 0.85f, 0.45f, 0.25f);

    drawCircle(155.0f, 495.0f, 25.0f, 30);
    drawCircle(1170.0f, 480.0f, 25.0f, 30);

    glColor3f(1.0f, 0.85f, 0.45f);

    drawCircle(155.0f, 495.0f, 6.0f, 20);
    drawCircle(1170.0f, 480.0f, 6.0f, 20);
}


// ============================================================
// OVERHEAD WIRES
// ============================================================

void drawOverheadWires()
{
    glColor4f(0.04f, 0.04f, 0.045f, 0.75f);

    glLineWidth(1.5f);

    glBegin(GL_LINES);

    glVertex2f(0.0f, 420.0f);
    glVertex2f(1280.0f, 400.0f);

    glVertex2f(0.0f, 400.0f);
    glVertex2f(1280.0f, 420.0f);

    glEnd();
}


// ============================================================
// CAR
// ============================================================

void drawCar(float x, float y, float scale,
             float red, float green, float blue)
{
    // ---------------- SHADOW ----------------

    glColor4f(0.0f, 0.0f, 0.0f, 0.45f);

    glBegin(GL_POLYGON);

    glVertex2f(x - 100.0f * scale,
               y - 10.0f * scale);

    glVertex2f(x + 100.0f * scale,
               y - 10.0f * scale);

    glVertex2f(x + 120.0f * scale,
               y - 28.0f * scale);

    glVertex2f(x - 120.0f * scale,
               y - 28.0f * scale);

    glEnd();


    // ---------------- MAIN BODY ----------------

    glColor3f(red, green, blue);

    glBegin(GL_POLYGON);

    glVertex2f(x - 95.0f * scale, y);

    glVertex2f(x + 95.0f * scale, y);

    glVertex2f(x + 110.0f * scale,
               y + 32.0f * scale);

    glVertex2f(x + 70.0f * scale,
               y + 52.0f * scale);

    glVertex2f(x - 65.0f * scale,
               y + 52.0f * scale);

    glVertex2f(x - 108.0f * scale,
               y + 30.0f * scale);

    glEnd();


    // ---------------- ROOF ----------------

    glColor3f(red * 0.70f, green * 0.70f, blue * 0.70f);

    glBegin(GL_POLYGON);

    glVertex2f(x - 48.0f * scale,
               y + 52.0f * scale);

    glVertex2f(x + 48.0f * scale,
               y + 52.0f * scale);

    glVertex2f(x + 27.0f * scale,
               y + 90.0f * scale);

    glVertex2f(x - 27.0f * scale,
               y + 90.0f * scale);

    glEnd();


    // ---------------- WINDOWS ----------------

    glColor3f(0.25f, 0.40f, 0.47f);

    glBegin(GL_QUADS);

    // Left window
    glVertex2f(x - 40.0f * scale,
               y + 56.0f * scale);

    glVertex2f(x - 5.0f * scale,
               y + 56.0f * scale);

    glVertex2f(x - 8.0f * scale,
               y + 82.0f * scale);

    glVertex2f(x - 26.0f * scale,
               y + 82.0f * scale);


    // Right window
    glVertex2f(x + 5.0f * scale,
               y + 56.0f * scale);

    glVertex2f(x + 40.0f * scale,
               y + 56.0f * scale);

    glVertex2f(x + 26.0f * scale,
               y + 82.0f * scale);

    glVertex2f(x + 8.0f * scale,
               y + 82.0f * scale);

    glEnd();


    // ---------------- WINDOW DIVIDER ----------------

    glColor3f(0.85f, 0.85f, 0.82f);

    glLineWidth(2.0f);

    glBegin(GL_LINES);

    glVertex2f(x, y + 56.0f * scale);
    glVertex2f(x, y + 84.0f * scale);

    glEnd();


    // ---------------- HEADLIGHT GLOW ----------------

    glColor4f(1.0f, 0.85f, 0.35f, 0.10f);

    drawCircle(x + 105.0f * scale,
               y + 28.0f * scale,
               18.0f * scale,
               25);


    // ---------------- HEADLIGHT ----------------

    glColor3f(1.0f, 0.92f, 0.45f);

    glBegin(GL_QUADS);

    glVertex2f(x + 88.0f * scale,
               y + 21.0f * scale);

    glVertex2f(x + 108.0f * scale,
               y + 24.0f * scale);

    glVertex2f(x + 108.0f * scale,
               y + 34.0f * scale);

    glVertex2f(x + 88.0f * scale,
               y + 33.0f * scale);

    glEnd();


    // ---------------- TAIL LIGHT ----------------

    glColor3f(0.9f, 0.02f, 0.02f);

    glBegin(GL_QUADS);

    glVertex2f(x - 108.0f * scale,
               y + 21.0f * scale);

    glVertex2f(x - 88.0f * scale,
               y + 21.0f * scale);

    glVertex2f(x - 88.0f * scale,
               y + 34.0f * scale);

    glVertex2f(x - 108.0f * scale,
               y + 34.0f * scale);

    glEnd();


    // ---------------- WHEELS ----------------

    glColor3f(0.005f, 0.005f, 0.005f);

    drawCircle(x - 55.0f * scale,
               y,
               22.0f * scale,
               30);

    drawCircle(x + 55.0f * scale,
               y,
               22.0f * scale,
               30);


    // Wheel hubs

    glColor3f(0.35f, 0.35f, 0.37f);

    drawCircle(x - 55.0f * scale,
               y,
               9.0f * scale,
               25);

    drawCircle(x + 55.0f * scale,
               y,
               9.0f * scale,
               25);
}





// ============================================================
// RAIN / ATMOSPHERIC LINES
// ============================================================

void drawRain()
{
    glColor4f(0.75f, 0.80f, 0.82f, 0.10f);

    glLineWidth(1.0f);

    glBegin(GL_LINES);

    for (int i = 0; i < 120; i++)
    {
        float x = (i * 113) % 1280;
        float y = (i * 67) % 720;

        glVertex2f(x, y);
        glVertex2f(x - 5.0f, y - 18.0f);
    }

    glEnd();
}


// ============================================================
// BRIDGE CARS
// ============================================================

float bridgeRoadY(float x)
{
    // The extended bridge is horizontal at y = 420.
    return 420.0f;
}

void drawOneBridgeCar(float x, float scale,
                      float red, float green, float blue)
{
    // Draw only while the car is on the bridge.
    if (x >= -120.0f && x <= 1400.0f)
    {
        glPushMatrix();
        glTranslatef(x, bridgeRoadY(x) - 18.0f, 0.0f);
        glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
        drawCar(0.0f, 0.0f, scale, red, green, blue);
        glPopMatrix();
    }
}

void drawBridgeCars()
{
    drawOneBridgeCar(bridgeCarX1, 0.34f, 0.10f, 0.35f, 0.95f); // Blue
    drawOneBridgeCar(bridgeCarX2, 0.28f, 0.15f, 0.75f, 0.20f); // Green
    drawOneBridgeCar(bridgeCarX3, 0.24f, 1.00f, 0.80f, 0.05f); // Yellow
}


// ============================================================
// DISPLAY
// ============================================================

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();


    // --------------------------------------------------------
    // BACKGROUND
    // --------------------------------------------------------

    drawBackgroundSky();

    drawSun();

    drawClouds();

    drawBackgroundTrees();


    // --------------------------------------------------------
    // BRIDGE + WATER
    // --------------------------------------------------------

    drawRiver();

    drawBridge();
    drawBridgeCars();


    // --------------------------------------------------------
    // SHORE + TREES
    // --------------------------------------------------------

    drawTreesAndShoreline();


    // --------------------------------------------------------
    // ROAD
    // --------------------------------------------------------

    drawWetRoad();

    drawWetRoadReflection();


    // --------------------------------------------------------
    // CAR REFLECTIONS
    // --------------------------------------------------------




    // --------------------------------------------------------
    // CARS
    // --------------------------------------------------------

    drawCar(carX1, 115.0f, 1.0f, 0.72f, 0.025f, 0.025f);

    drawCar(carX2, 135.0f, 0.70f, 0.72f, 0.025f, 0.025f);

    drawCar(carX3, 155.0f, 0.55f, 0.72f, 0.025f, 0.025f);


    // --------------------------------------------------------
    // STREET LIGHTS
    // --------------------------------------------------------

    drawStreetLights();


    // --------------------------------------------------------
    // WIRES
    // --------------------------------------------------------

    drawOverheadWires();


    // --------------------------------------------------------
    // The scene is daytime, so rain is not drawn.


    glutSwapBuffers();
}


// ============================================================
// UPDATE / ANIMATION
// ============================================================

void update(int value)
{
    // --------------------------------------------------------
    // CAR 1
    // --------------------------------------------------------

    carX1 += carSpeed1;

    if (carX1 > 1450.0f)
    {
        carX1 = -250.0f;
    }


    // --------------------------------------------------------
    // CAR 2
    // --------------------------------------------------------

    carX2 += carSpeed2;

    if (carX2 > 1450.0f)
    {
        carX2 = -250.0f;
    }


    // --------------------------------------------------------
    // CAR 3
    // --------------------------------------------------------

    carX3 += carSpeed3;

    if (carX3 > 1450.0f)
    {
        carX3 = -250.0f;
    }


    // --------------------------------------------------------
    // BRIDGE CAR ANIMATION
    bridgeCarX1 += bridgeCarSpeed1;
    bridgeCarX2 += bridgeCarSpeed2;
    bridgeCarX3 += bridgeCarSpeed3;

    if (bridgeCarX1 > 1400.0f) bridgeCarX1 = -120.0f;
    if (bridgeCarX2 > 1400.0f) bridgeCarX2 = -120.0f;
    if (bridgeCarX3 > 1400.0f) bridgeCarX3 = -120.0f;


    // WATER ANIMATION
    // --------------------------------------------------------

    waterMove += 1.0f;

    // CLOUD ANIMATION
    cloudMove += cloudSpeed;

    if (cloudMove >= 1450.0f)
    {
        cloudMove = 0.0f;
    }

    if (waterMove > 120.0f)
    {
        waterMove = 0.0f;
    }


    glutPostRedisplay();

    glutTimerFunc(16, update, 0);
}


// ============================================================
// INITIALIZATION
// ============================================================

void init()
{
    glClearColor(0.53f, 0.81f, 0.98f, 1.0f);


    // Transparency

    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA,
                GL_ONE_MINUS_SRC_ALPHA);


    // Smooth lines

    glEnable(GL_LINE_SMOOTH);

    glHint(GL_LINE_SMOOTH_HINT,
           GL_NICEST);


    // Smooth polygons

    glEnable(GL_POINT_SMOOTH);


    // Projection

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(0.0f,
               1280.0f,
               0.0f,
               720.0f);


    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
}


// ============================================================
// MAIN
// ============================================================

int main(int argc, char** argv)
{
    glutInit(&argc, argv);


    // Double buffering + RGBA

    glutInitDisplayMode(GLUT_DOUBLE |
                        GLUT_RGBA);


    // Window

    glutInitWindowSize(1280, 720);

    glutInitWindowPosition(100, 100);


    glutCreateWindow(
        "Daylight Bridge - Friend Color Style"
    );


    // Initialize

    init();


    // Display callback

    glutDisplayFunc(display);


    // Animation timer

    glutTimerFunc(16, update, 0);


    // Start

    glutMainLoop();


    return 0;
}
