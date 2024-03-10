//include necessary library 
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <math.h>

//global variable
bool isDay = true; //start with dayTime first
bool fullScreenMode = false;

//initialization for first car
float carPosX = -1.3f; // Start from the left side
float carSpeed = 0.001f; // Adjust the speed of the car 

//initialization for second car  
float carPosX2 = 0.75f; // Start from the left side
float carSpeedCar2 = 0.001f; // Adjust the speed of the car

float speedMultiplier = 1.0f; // Speed multiplier , night will be slower default set it to 1 

bool cloudMoving = true; // default cloud is moving 

//Initialize OpenGL Graphics 
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

//use to draw an ellipse 
void midPointEllipse(float xradius, float yradius, float q) 
{
    glBegin(GL_POLYGON);

    for (int i = 0; i < 360; i++)
    {
        //convert degrees into radians
        float degInRad = i * (3.14159 / 180.0) / q;
        glVertex2f(cos(degInRad) * xradius, sin(degInRad) * yradius);
    }
    glEnd();
}

//draw Kl tower
void drawKLTower() { 
    // Base color for the tower's main structure
    glColor3ub(169, 169, 169); // Silver/Gray for the tower
    glBegin(GL_QUADS);
    glVertex2f(-0.75f, -0.59f);
    glVertex2f(-0.5f, -0.59f);
    glVertex2f(-0.51f, -0.4f);
    glVertex2f(-0.74f, -0.4f);

    glVertex2f(-0.72f, 0.3f);
    glVertex2f(-0.52f, 0.3f);
    glVertex2f(-0.52f, 0.4f);
    glVertex2f(-0.72f, 0.4f);

    // Darker shade for contrast and depth
    glColor3ub(105, 105, 105); // DimGray for shadowed parts
    glVertex2f(-0.74f, -0.4f);
    glVertex2f(-0.51f, -0.4f);
    glVertex2f(-0.52f, 0.3f);
    glVertex2f(-0.72f, 0.3f);

    glEnd();

    // Top dome
    glPushMatrix();
    glTranslatef(-0.62, 0.45, 0);
    glScalef(0.08, 0.08, 1);
    midPointEllipse(4, 1, 1); //keep the color as is for the dome
    glPopMatrix();

    // Antenna or spire
    glColor3ub(255, 255, 255); // White for the antenna/spire
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.6f, 0.55f);
    glVertex2f(-0.64f, 0.55f);
    glVertex2f(-0.62f, 0.7f);
    glEnd();

    // Horizontal bands
    glBegin(GL_QUADS);
    glVertex2f(-0.95f, 0.43f);
    glVertex2f(-0.3f, 0.43f);
    glVertex2f(-0.3f, 0.48f);
    glVertex2f(-0.95f, 0.48f);

    // Windows and details with slight color adjustments
    glColor3ub(135, 206, 235); 
    glVertex2f(-0.66f, 0.55f);
    glVertex2f(-0.58f, 0.55f);
    glVertex2f(-0.58f, 0.5f);
    glVertex2f(-0.66f, 0.5f);

    // "lighting effects" 
    glColor3ub(255, 215, 0); 
    glVertex2f(-0.93f, 0.44f);
    glVertex2f(-0.83f, 0.44f);
    glVertex2f(-0.83f, 0.47f);
    glVertex2f(-0.93f, 0.47f);

    glVertex2f(-0.58f, 0.44f);
    glVertex2f(-0.68f, 0.44f);
    glVertex2f(-0.68f, 0.47f);
    glVertex2f(-0.58f, 0.47f);

    glVertex2f(-0.43f, 0.44f);
    glVertex2f(-0.33f, 0.44f);
    glVertex2f(-0.33f, 0.47f);
    glVertex2f(-0.43f, 0.47f);


    glEnd();
}

//draw quad with gradient color 
void drawGradientQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, GLfloat* color1, GLfloat* color2) {
    glBegin(GL_QUADS);
    glColor3fv(color1); // Bottom color
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glColor3fv(color2); // Top color
    glVertex2f(x3, y3);
    glVertex2f(x4, y4);
    glEnd();
}

//draw KLCC
void drawKLCC() {
    float xOffset = -0.15f; // Shift the towers slightly more to the right
    float scale = 1.5f; // Scale factor for making it bigger

    GLfloat bottomColor[3] = { 0.5f, 0.5f, 0.5f }; // Darker shade for the bottom
    GLfloat topColor[3] = { 0.7f, 0.7f, 0.7f }; // Lighter shade for the top
    GLfloat windowColor[3] = { 0.9f, 0.9f, 0.9f }; // White with slight gray tint for windows

    // Tower 1 - Main structure with gradient
    drawGradientQuad((0.1f + xOffset) * scale, -0.5f * scale, (0.3f + xOffset) * scale, -0.5f * scale, (0.3f + xOffset) * scale, 0.3f * scale, (0.1f + xOffset) * scale, 0.3f * scale, bottomColor, topColor);

    // Tower 2 - Main structure with gradient
    drawGradientQuad((0.4f + xOffset) * scale, -0.5f * scale, (0.6f + xOffset) * scale, -0.5f * scale, (0.6f + xOffset) * scale, 0.3f * scale, (0.4f + xOffset) * scale, 0.3f * scale, bottomColor, topColor);

    // Connecting Skybridge with slighty gradient
    glColor3ub(160, 167, 174); 
    glBegin(GL_QUADS);
    glVertex2f((0.3f + xOffset) * scale, 0.1f * scale);
    glVertex2f((0.4f + xOffset) * scale, 0.1f * scale);
    glVertex2f((0.4f + xOffset) * scale, 0.15f * scale);
    glVertex2f((0.3f + xOffset) * scale, 0.15f * scale);
    glEnd();

    glColor3ub(183, 190, 196); // Same color as the main structure for the tops

    // Tower 1 - Sharp top
    glBegin(GL_TRIANGLES);
    glVertex2f((0.1f + xOffset) * scale, 0.3f * scale); // Base left
    glVertex2f((0.2f + xOffset) * scale, 0.5f * scale); // Top middle peak
    glVertex2f((0.3f + xOffset) * scale, 0.3f * scale); // Base right
    glEnd();

    // Tower 2 - Sharp top
    glBegin(GL_TRIANGLES);
    glVertex2f((0.4f + xOffset) * scale, 0.3f * scale); // Base left
    glVertex2f((0.5f + xOffset) * scale, 0.5f * scale); // Top middle peak
    glVertex2f((0.6f + xOffset) * scale, 0.3f * scale); // Base right
    glEnd();

    // Draw windows for Tower 1
    // Updated Draw windows for Tower 1 with consistent color
    float windowLightness = 0.9f; // Fixed lightness for windows
    for (float y = (-0.45f * scale); y < (0.3f * scale); y += (0.03f * scale + 0.01f * scale)) {
        for (float x = ((0.12f + xOffset) * scale); x < ((0.28f + xOffset) * scale); x += (0.02f * scale + 0.01f * scale)) {
            glColor3f(windowLightness, windowLightness, windowLightness); // Consistent color for all windows
            glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + (0.02f * scale), y);
            glVertex2f(x + (0.02f * scale), y + (0.03f * scale));
            glVertex2f(x, y + (0.03f * scale));
            glEnd();
        }
    }

    // Updated Draw windows for Tower 2 with consistent color
    for (float y = (-0.45f * scale); y < (0.3f * scale); y += (0.03f * scale + 0.01f * scale)) {
        for (float x = ((0.42f + xOffset) * scale); x < ((0.58f + xOffset) * scale); x += (0.02f * scale + 0.01f * scale)) {
            glColor3f(windowLightness, windowLightness, windowLightness); // Consistent color for all windows
            glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + (0.02f * scale), y);
            glVertex2f(x + (0.02f * scale), y + (0.03f * scale));
            glVertex2f(x, y + (0.03f * scale));
            glEnd();
        }
    }
}

//draw grass with road
void road()
{
    //grass 1

    glBegin(GL_QUADS);
    glColor3ub(102, 153, 0);
    glVertex2f(1.0, -0.71);
    glVertex2f(1.0, -0.7);
    glVertex2f(-1.0, -0.7);
    glVertex2f(-1.0, -0.71);
    glEnd();


    //roadside 

    glBegin(GL_QUADS);
    glColor3ub(102, 51, 0);
    glVertex2f(1.0, -0.7195);
    glVertex2f(1.0, -0.71);
    glVertex2f(-1.0, -0.71);
    glVertex2f(-1.0, -0.7195);
    glEnd();

    //road 1
    glBegin(GL_QUADS);
    glColor3ub(115, 115, 115);
    glVertex2f(1.0, -0.8);
    glVertex2f(1.0, -0.7195);
    glVertex2f(-1.0, -0.7195);
    glVertex2f(-1.0, -0.8);
    glEnd();


    glBegin(GL_QUADS);
    glColor3ub(230, 255, 255);
    glVertex2f(1.0, -0.7295);
    glVertex2f(1.0, -0.725);
    glVertex2f(-1.0, -0.725);
    glVertex2f(-1.0, -0.7295);
    glEnd();


    glBegin(GL_QUADS);
    glColor3ub(230, 255, 255);
    glVertex2f(1.0, -0.795);
    glVertex2f(1.0, -0.79);
    glVertex2f(-1.0, -0.79);
    glVertex2f(-1.0, -0.795);
    glEnd();


    glBegin(GL_QUADS);
    glColor3ub(255, 255, 255);
    glVertex2f(-.5, -0.76);
    glVertex2f(-.50, -0.77);
    glVertex2f(-1.0, -0.77);
    glVertex2f(-1.0, -0.76);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(255, 255, 255);
    glVertex2f(.2, -0.76);
    glVertex2f(.20, -0.77);
    glVertex2f(-.30, -0.77);
    glVertex2f(-.30, -0.76);
    glEnd();


    glBegin(GL_QUADS);
    glColor3ub(255, 255, 255);
    glVertex2f(.4, -0.76);
    glVertex2f(.40, -0.77);
    glVertex2f(.90, -0.77);
    glVertex2f(.90, -0.76);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(102, 153, 0);
    glVertex2f(1.0, -0.85);
    glVertex2f(1.0, -0.8);
    glVertex2f(-1.0, -0.8);
    glVertex2f(-1.0, -0.85);
    glEnd();

    //roadside
    glBegin(GL_QUADS);
    glColor3ub(102, 51, 0);
    glVertex2f(1.0, -0.86);
    glVertex2f(1.0, -0.85);
    glVertex2f(-1.0, -0.85);
    glVertex2f(-1.0, -0.86);
    glEnd();

    //road 2

    glBegin(GL_QUADS);
    glColor3ub(115, 115, 115);
    glVertex2f(1.0, -0.86);
    glVertex2f(1.0, -0.97);
    glVertex2f(-1.0, -0.97);
    glVertex2f(-1.0, -0.86);
    glEnd();


    glBegin(GL_QUADS);
    glColor3ub(255, 255, 255);
    glVertex2f(1.0, -0.87);
    glVertex2f(1.0, -0.875);
    glVertex2f(-1.0, -0.875);
    glVertex2f(-1.0, -0.87);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(255, 255, 255);
    glVertex2f(-.5, -0.91);
    glVertex2f(-.50, -0.92);
    glVertex2f(-1.0, -0.92);
    glVertex2f(-1.0, -0.91);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(255, 255, 255);
    glVertex2f(.2, -0.91);
    glVertex2f(.20, -0.92);
    glVertex2f(-.30, -0.92);
    glVertex2f(-.30, -0.91);
    glEnd();


    glBegin(GL_QUADS);
    glColor3ub(255, 255, 255);
    glVertex2f(.4, -0.91);
    glVertex2f(.40, -0.92);
    glVertex2f(.90, -0.92);
    glVertex2f(.90, -0.91);
    glEnd();


    //grass 
    glBegin(GL_QUADS);
    glColor3ub(255, 255, 255);
    glVertex2f(1.0, -0.965);
    glVertex2f(1.0, -0.96);
    glVertex2f(-1.0, -0.96);
    glVertex2f(-1.0, -0.965);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(102, 153, 0);
    glVertex2f(1.0, -0.97);
    glVertex2f(1.0, -1.0);
    glVertex2f(-1.0, -1.0);
    glVertex2f(-1.0, -0.97);
    glEnd();


}

//draw stars at night
void stars() {
    glLoadIdentity(); //Reset the drawing perspective
    glMatrixMode(GL_MODELVIEW);

    //draw blue background
    glColor3ub(38, 77, 115);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 1.0f);
    glEnd();

    //draw star
    glPointSize(2);
    glBegin(GL_POINTS);
    glColor3ub(255, 255, 255);//white

    //start drawing star on different location 
    glVertex2f(-0.0f, 0.79f);
    glVertex2f(-0.0f, 0.9f);
    glVertex2f(-0.07f, 0.9f);
    glVertex2f(-0.07f, 0.7f);
    glVertex2f(-0.03f, 0.75f);
    glVertex2f(-0.03f, 0.85f);
    glVertex2f(-0.03f, 0.95f);
    glVertex2f(-0.13f, 0.79f);
    glVertex2f(-0.13f, 0.9f);
    glVertex2f(-0.23f, 0.75f);
    glVertex2f(-0.23f, 0.85f);
    glVertex2f(-0.33f, 0.65f);
    glVertex2f(-0.33f, 0.785f);
    glVertex2f(-0.33f, 0.958f);
    glVertex2f(-0.43f, 0.55f);
    glVertex2f(-0.43f, 0.75f);
    glVertex2f(-0.43f, 0.89f);
    glVertex2f(-0.55f, 0.47f);
    glVertex2f(-0.55f, 0.67f);
    glVertex2f(-0.55f, 0.87f);
    glVertex2f(-0.5f, 0.42f);
    glVertex2f(-0.58f, 0.45f);
    glVertex2f(-0.58f, 0.65f);
    glVertex2f(-0.58f, 0.95f);
    glVertex2f(-0.49f, 0.51f);
    glVertex2f(-0.63f, 0.525f);
    glVertex2f(-0.63f, 0.725f);
    glVertex2f(-0.63f, 0.925f);
    glVertex2f(-0.73f, 0.425f);
    glVertex2f(-0.73f, 0.525f);
    glVertex2f(-0.73f, 0.725f);
    glVertex2f(-0.83f, 0.35f);
    glVertex2f(-0.83f, 0.46f);
    glVertex2f(-0.83f, 0.56f);
    glVertex2f(-0.83f, 0.76f);
    glVertex2f(-0.83f, 0.96f);
    glVertex2f(-0.93f, 0.485f);
    glVertex2f(-0.93f, 0.585f);
    glVertex2f(-0.93f, 0.785f);
    glVertex2f(-0.98f, 0.885f);
    glVertex2f(-0.98f, 0.285f);
    glVertex2f(0.0f, 0.79f);
    glVertex2f(0.0f, 0.9f);
    glVertex2f(0.07f, 0.9f);
    glVertex2f(0.07f, 0.7f);
    glVertex2f(0.03f, 0.75f);
    glVertex2f(0.03f, 0.85f);
    glVertex2f(0.03f, 0.95f);
    glVertex2f(0.13f, 0.79f);
    glVertex2f(0.13f, 0.9f);
    glVertex2f(0.23f, 0.75f);
    glVertex2f(0.23f, 0.85f);
    glVertex2f(0.33f, 0.65f);
    glVertex2f(0.33f, 0.785f);
    glVertex2f(0.33f, 0.958f);
    glVertex2f(0.43f, 0.55f);
    glVertex2f(0.43f, 0.75f);
    glVertex2f(0.43f, 0.89f);
    glVertex2f(0.55f, 0.47f);
    glVertex2f(0.55f, 0.67f);
    glVertex2f(0.55f, 0.87f);
    glVertex2f(0.5f, 0.42f);
    glVertex2f(0.58f, 0.45f);
    glVertex2f(0.58f, 0.65f);
    glVertex2f(0.58f, 0.95f);
    glVertex2f(0.49f, 0.51f);
    glVertex2f(0.63f, 0.525f);
    glVertex2f(0.63f, 0.725f);
    glVertex2f(0.63f, 0.925f);
    glVertex2f(0.73f, 0.425f);
    glVertex2f(0.73f, 0.525f);
    glVertex2f(0.73f, 0.725f);
    glVertex2f(0.83f, 0.35f);
    glVertex2f(0.83f, 0.46f);
    glVertex2f(0.83f, 0.56f);
    glVertex2f(0.83f, 0.76f);
    glVertex2f(0.83f, 0.96f);
    glVertex2f(0.93f, 0.485f);
    glVertex2f(0.93f, 0.585f);
    glVertex2f(0.93f, 0.785f);
    glVertex2f(0.98f, 0.885f);
    glVertex2f(0.98f, 0.285f);

    glEnd();
}

//draw clouds at dayTime
void clouds(float x, float y) {
    // Declare local variables to control cloud movement
    static float cloudScale = 1.0f; // Initial scale of the cloud
    static bool increaseScale = true; // Flag to determine whether to increase or decrease the scale
    float scaleChangeRate = 0.00005f; // Rate at which the scale changes
    float cloudSpeedX = 0.001f; // Speed of movement in the x direction
    float cloudSpeedY = 0.0f; // Speed of movement in the y direction

    // update cloud position and scale
    if (cloudMoving) {
        // Update cloud position based on speed
        x += cloudSpeedX; // Move the cloud horizontally
        y += cloudSpeedY; // Move the cloud vertically

        // Increase or decrease cloud scale
        if (increaseScale) {
            cloudScale += scaleChangeRate; // Adjust scale increase rate 
            if (cloudScale >= 1.1f) { // Maximum scale reached, start decreasing
                increaseScale = false;
            }
        }
        else {
            cloudScale -= scaleChangeRate; // Adjust scale decrease rate
            if (cloudScale <= 0.9f) { // Minimum scale reached, start increasing
                increaseScale = true;
            }
        }
    }

    // Draw the cloud using ellipses or circles
    glColor3f(1.0f, 1.0f, 1.0f); // Set color to white

    // Draw first circle
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(cloudScale, cloudScale, 1.0f); // Scale the cloud
    glutSolidSphere(0.1, 50, 50);
    glPopMatrix();

    // Draw second circle
    glPushMatrix();
    glTranslatef(x + 0.1f, y, 0.0f);
    glScalef(cloudScale, cloudScale, 1.0f); // Scale the cloud
    glutSolidSphere(0.1, 50, 50);
    glPopMatrix();

    // Draw third circle
    glPushMatrix();
    glTranslatef(x + 0.05f, y + 0.05f, 0.0f);
    glScalef(cloudScale, cloudScale, 1.0f); // Scale the cloud
    glutSolidSphere(0.1, 50, 50);
    glPopMatrix();
}

//draw sun / moon at night 
void drawSunMoon() {
    int numSegments = 100;
    GLfloat radius = 0.1f; // Sun radius
    GLfloat cx = 0.9f; // Sun X position, top right corner
    GLfloat cy = 0.9f; // Sun Y position, top right corner

    // Start drawing the sun with an improved gradient
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy); // Center of circle
    glColor3f(1.0, 0.85, 0.0); // Solid yellow for the center

    for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
        GLfloat angle = 2.0f * 3.1415926f * float(i) / float(numSegments); // 360 degrees in radians

        // Calculate gradient
        GLfloat fraction = float(i) / float(numSegments);
        GLfloat red = 1.0; // Keep red constant to ensure the color stays within the yellow-orange-red spectrum
        GLfloat green = 0.85 * (1 - fraction); // Decrease green to transition from yellow to orange/red
        GLfloat blue = 0.0; // Keep blue at 0

        glColor3f(red, green, blue); 

        GLfloat x = radius * cosf(angle);
        GLfloat y = radius * sinf(angle);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();


    // Check if it's nighttime
    if (!isDay) {
        // Draw the moon covering the sun
        glColor3ub(38, 77, 115); // Dark blue color
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx + 0.1f, cy); // Center of circle, shifted to the right
        for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
            GLfloat angle = 2.5f * 3.1415926f * float(i) / float(numSegments); // 360 degrees in radians
            GLfloat x = radius * cosf(angle) * 0.5f; // Make the moon smaller than the sun
            GLfloat y = radius * sinf(angle);
            glVertex2f(x + cx +0.05f , y + cy); // Shifted to the right
        }
        glEnd();
    }
}

//draw several buildings in front of KLCC and Kl Tower 
void buildings() {
    //Building 1 (from left) //************************

    glBegin(GL_QUADS);
    glColor3ub(204, 51, 0);
    glVertex2f(-0.95, -0.7);
    glVertex2f(-0.95, -0.2);
    glVertex2f(-1.0, -0.2);  
    glVertex2f(-1.0, -0.7);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(230, 57, 0);
    glVertex2f(-0.8, -0.7);
    glVertex2f(-0.8, -0.2); 
    glVertex2f(-0.950, -0.2); 
    glVertex2f(-0.950, -0.7);
    glEnd();

    //glass on building 1
    glBegin(GL_QUADS);
    glColor3ub(255, 128, 0);
    glVertex2f(-0.81, -0.7);
    glVertex2f(-0.81, -0.2); 
    glVertex2f(-0.945, -0.2); 
    glVertex2f(-0.945, -0.7);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(230, 115, 0);
    glVertex2f(-0.96, -0.7);
    glVertex2f(-0.96, -0.2); 
    glVertex2f(-0.995, -0.2); 
    glVertex2f(-0.995, -0.7);
    glEnd();

    // Building 2
    glBegin(GL_QUADS);
    glColor3ub(102, 153, 153);
    glVertex2f(-0.75, -0.7);
    glVertex2f(-0.75, -0.43);
    glVertex2f(-0.8, -0.43);
    glVertex2f(-0.8, -0.7);
    glEnd();

    // Black border for Building 2 (top, left, right)
    glLineWidth(2.0); // Set line width
    glBegin(GL_LINES);
    glColor3ub(0.9, 0.9, 0.9); // Black color
    // Top side
    glVertex2f(-0.75, -0.43);
    glVertex2f(-0.8, -0.43);
    // Left side
    glVertex2f(-0.75, -0.7);
    glVertex2f(-0.75, -0.43);
    // Right side
    glVertex2f(-0.8, -0.7);
    glVertex2f(-0.8, -0.43);
    glEnd();

    // Building 3
    glBegin(GL_QUADS);
    glColor3ub(117, 163, 163);
    glVertex2f(-0.65, -0.7);
    glVertex2f(-0.65, -0.38);
    glVertex2f(-0.75, -0.38);
    glVertex2f(-0.75, -0.7);
    glEnd();

    // Black border for Building 3 (top, left, right)
    glBegin(GL_LINES);
    glColor3ub(0.9, 0.9, 0.9); // Black color
    // Top side
    glVertex2f(-0.65, -0.38);
    glVertex2f(-0.75, -0.38);
    // Left side
    glVertex2f(-0.65, -0.7);
    glVertex2f(-0.65, -0.38);
    // Right side
    glVertex2f(-0.75, -0.7);
    glVertex2f(-0.75, -0.38);
    glEnd();



    //Building 4

    glBegin(GL_QUADS);
    glColor3ub(191, 191, 191);
    glVertex2f(-.6, -0.7);
    glVertex2f(-.6, 0.01); 
    glVertex2f(-0.65, 0.01); 
    glVertex2f(-.65, -0.7);
    glEnd();

    //glass of building


    glBegin(GL_QUADS);
    glColor3ub(153, 153, 255);
    glVertex2f(-.59, -0.7);
    glVertex2f(-.59, -0.01); 
    glVertex2f(-0.64, -0.01);
    glVertex2f(-.64, -0.7);
    glEnd();


    //building

    glBegin(GL_QUADS);
    glColor3ub(204, 204, 204);
    glVertex2f(-.5, -0.7);
    glVertex2f(-.5, 0.01);
    glVertex2f(-0.6, 0.01); 
    glVertex2f(-.6, -0.7);
    glEnd();


    //miror 2
    glBegin(GL_QUADS);
    glColor3ub(153, 153, 255);
    glVertex2f(-.51, -0.7);
    glVertex2f(-.51, -0.01); 
    glVertex2f(-0.59, -0.01); 
    glVertex2f(-.59, -0.7);
    glEnd();


    //Building 5

    glBegin(GL_QUADS);
    glColor3ub(198, 140, 83);
    glVertex2f(-.45, -0.7);
    glVertex2f(-.45, -0.21); 
    glVertex2f(-0.5, -0.21); 
    glVertex2f(-0.5, -0.7);
    glEnd();


    glBegin(GL_QUADS);
    glColor3ub(204, 153, 102);
    glVertex2f(-.4, -0.7);
    glVertex2f(-.4, -0.21); 
    glVertex2f(-0.45, -0.21); 
    glVertex2f(-0.45, -0.7);
    glEnd();

    //Glass
    glBegin(GL_QUADS);
    glColor3ub(224, 224, 209);
    glVertex2f(-.405, -0.7);
    glVertex2f(-.405, -0.22); 
    glVertex2f(-0.447, -0.22); 
    glVertex2f(-0.447, -0.7);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(224, 224, 209);
    glVertex2f(-.457, -0.7);
    glVertex2f(-.457, -0.22);
    glVertex2f(-0.495, -0.22); 
    glVertex2f(-0.495, -0.4);
    glEnd();



    // Building 6
    glBegin(GL_QUADS);
    glColor3ub(90, 90, 90); 
    glVertex2f(-0.05, -0.7);
    glVertex2f(-0.05, -0.4); 
    glVertex2f(-0.48, -0.4); 
    glVertex2f(-0.48, -0.7); 
    glEnd();

    // Glass
    glBegin(GL_QUADS);
    glColor3ub(180, 180, 180); 
    glVertex2f(-0.26, -0.7); 
    glVertex2f(-0.26, -0.4); 
    glVertex2f(-0.47, -0.4); 
    glVertex2f(-0.47, -0.7);
    glEnd();

    //Building 7
    glBegin(GL_QUADS);
    glColor3ub(100, 100, 200); //blue
    glVertex2f(-0.15, -0.7); // Right side of previous building
    glVertex2f(-0.15, -0.3);
    glVertex2f(-0.25, -0.3);
    glVertex2f(-0.25, -0.7);
    glEnd();

    //Building 8
    glBegin(GL_QUADS);
    glColor3ub(180, 100, 50); 
    glVertex2f(0.0, -0.7);
    glVertex2f(0.0, -0.2); 
    glVertex2f(-0.2, -0.2);
    glVertex2f(-0.2, -0.7); 
    glEnd();

    //Building 9
    glPushMatrix();
    glTranslatef(0.2, -0.7, 0); 
    glBegin(GL_POLYGON);
    glColor3ub(100, 100, 150); 

    int numSegments = 100; // Number of segments to approximate a circle
    float radius = 0.25; // Radius of the semi-circle
    for (int i = 0; i <= numSegments / 2; i++) { // Only loop through half of the segments for semi-circle
        float theta = 3.1415926f * float(i) / float(numSegments / 2); // Angle for each segment
        float x = radius * cosf(theta); // x-coordinate
        float y = radius * sinf(theta); // y-coordinate
        glVertex2f(x, y); // Vertex for the semi-circle
    }

    glEnd();

    // Draw Windows
    glColor3ub(150, 150, 150); // Window color (e.g., light gray)
    float windowSize = 0.05; // Size of the windows
    float windowGap = 0.03; // Gap between windows
    int numWindows = 5; // Number of windows
    for (int i = 0; i < numWindows; i++) {
        float windowX = -radius + (2 * radius - windowSize * numWindows - windowGap * (numWindows - 1)) / 2 + i * (windowSize + windowGap);
        float windowY = -windowSize / 2 + 0.05; 
        glBegin(GL_QUADS);
        glVertex2f(windowX, windowY);
        glVertex2f(windowX + windowSize, windowY);
        glVertex2f(windowX + windowSize, windowY + windowSize);
        glVertex2f(windowX, windowY + windowSize);
        glEnd();
    }

    glPopMatrix();


    // Building 10
    glBegin(GL_QUADS);
    glColor3ub(102, 153, 153);
    glVertex2f(0.5, -0.70); 
    glVertex2f(0.5, -0.41); 
    glVertex2f(0.3, -0.41); 
    glVertex2f(0.3, -0.70); 
    glEnd();

    // Second base of the building 
    glBegin(GL_QUADS);
    glColor3ub(117, 163, 163);
    glVertex2f(0.75, -0.70);
    glVertex2f(0.75, -0.41); 
    glVertex2f(0.5, -0.41);
    glVertex2f(0.5, -0.70); 
    glEnd();

    // Additional elements on the building
    glColor3ub(255, 255, 255); 
    glLineWidth(3.0); 
    glBegin(GL_LINES);
    glVertex2f(0.3, -0.55); 
    glVertex2f(0.5, -0.55); 
    glEnd();

    // Draw vertical lines on the first base
    glBegin(GL_LINES);
    glVertex2f(0.4, -0.70); 
    glVertex2f(0.4, -0.41); 
    glEnd();

    // Draw horizontal lines on the second base 
    glBegin(GL_LINES);
    glVertex2f(0.5, -0.55); 
    glVertex2f(0.75, -0.55); 
    glEnd();

    // Draw vertical lines on the second base 
    glBegin(GL_LINES);
    glVertex2f(0.6, -0.70); 
    glVertex2f(0.6, -0.41); 
    glEnd();

    glPushMatrix();


    // Building 11
    glBegin(GL_QUADS);
    glColor3ub(200, 100, 150);
    glVertex2f(0.75, -0.70); 
    glVertex2f(0.75, -0.2);  
    glVertex2f(1.0, -0.2);
    glVertex2f(1.0, -0.70);
    glEnd();

    // Additional elements on Building 11
    glColor3ub(255, 255, 255);
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glVertex2f(0.75, -0.55); 
    glVertex2f(1.0, -0.55);
    glEnd();

    // Draw vertical lines on Building 11
    glBegin(GL_LINES);
    glVertex2f(0.8, -0.70);
    glVertex2f(0.8, -0.2); 
    glEnd();

    // Draw horizontal lines on Building 11
    glBegin(GL_LINES);
    glVertex2f(0.75, -0.45);
    glVertex2f(1.0, -0.45);
    glEnd();

    // Draw vertical lines on the first base of Building 11
    glBegin(GL_LINES);
    glVertex2f(0.9, -0.70);
    glVertex2f(0.9, -0.2);
    glEnd();

    // Draw horizontal lines on the second base of Building 11
    glBegin(GL_LINES);
    glVertex2f(0.75, -0.35);
    glVertex2f(1.0, -0.35);
    glEnd();

}

//draw first car 
void movingCar(float x, float y) {
    // Draw the body of the car
    glPushMatrix();
    glTranslatef(x, y, 0.0f); // Translate according to the position
    glBegin(GL_QUADS);
    glColor3ub(255, 0, 0);
    glVertex2f(0.23, -0.58);
    glVertex2f(0.23, -0.55);
    glVertex2f(0.32, -0.55);
    glVertex2f(0.32, -0.58);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(230, 255, 255);
    glVertex2f(0.26, -0.55);
    glVertex2f(0.26, -0.51);
    glVertex2f(0.313, -0.51);
    glVertex2f(0.313, -0.55);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(0, 0, 0);
    glVertex2f(0.265, -0.55);
    glVertex2f(0.265, -0.515);
    glVertex2f(0.309, -0.515);
    glVertex2f(0.309, -0.55);
    glEnd();
    glPopMatrix();

    // Draw the tires
    float tireRadius = 0.015f; // Adjust the tire size
    // Left tire
    glPushMatrix();
    glTranslatef(x + 0.245f, y - 0.58f, 0.0f); // Translate according to the position
    glColor3ub(0, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    for (int i = 0; i <= 360; i++) {
        float angle = 2.0f * 3.1415926f * float(i) / float(360);
        float tireX = tireRadius * cosf(angle);
        float tireY = tireRadius * sinf(angle);
        glVertex2f(tireX, tireY);
    }
    glEnd();
    glPopMatrix();

    // Right tire
    glPushMatrix();
    glTranslatef(x + 0.305f, y - 0.58f, 0.0f); // Translate according to the position
    glColor3ub(0, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    for (int i = 0; i <= 360; i++) {
        float angle = 2.0f * 3.1415926f * float(i) / float(360);
        float tireX = tireRadius * cosf(angle);
        float tireY = tireRadius * sinf(angle);
        glVertex2f(tireX, tireY);
    }
    glEnd();
    glPopMatrix();
}

//draw second car
void movingCar2(float x, float y) {
    // Draw the body of the car
    glPushMatrix();
    glTranslatef(x, y, 0.0f); // Translate according to the position
    glBegin(GL_QUADS);
    glColor3ub(255, 51, 51); // Red color for the body
    glVertex2f(0.23, -0.58);
    glVertex2f(0.23, -0.55);
    glVertex2f(0.32, -0.55);
    glVertex2f(0.32, -0.58);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(0, 102, 204); // Blue color for the windows
    glVertex2f(0.26, -0.55);
    glVertex2f(0.26, -0.51);
    glVertex2f(0.313, -0.51);
    glVertex2f(0.313, -0.55);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(0, 0, 0); // Black color for the details
    glVertex2f(0.265, -0.55);
    glVertex2f(0.265, -0.515);
    glVertex2f(0.309, -0.515);
    glVertex2f(0.309, -0.55);
    glEnd();
    glPopMatrix();

    // Draw the tires
    float tireRadius = 0.015f; // Adjust the tire size 
    // Left tire
    glPushMatrix();
    glTranslatef(x + 0.245f, y - 0.58f, 0.0f); // Translate according to the position
    glColor3ub(0, 0, 0); // Black color for the tire
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    for (int i = 0; i <= 360; i++) {
        float angle = 2.0f * 3.1415926f * float(i) / float(360);
        float tireX = tireRadius * cosf(angle);
        float tireY = tireRadius * sinf(angle);
        glVertex2f(tireX, tireY);
    }
    glEnd();
    // Add rim
    glColor3ub(255, 255, 255); // White color for the rim
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= 360; i += 10) {
        float angle = 2.0f * 3.1415926f * float(i) / float(360);
        float innerRadius = tireRadius - 0.002f; // Adjust the inner radius of the rim
        float outerRadius = tireRadius + 0.002f; // Adjust the outer radius of the rim
        float innerX = innerRadius * cosf(angle);
        float innerY = innerRadius * sinf(angle);
        float outerX = outerRadius * cosf(angle);
        float outerY = outerRadius * sinf(angle);
        glVertex2f(innerX, innerY);
        glVertex2f(outerX, outerY);
    }
    glEnd();
    glPopMatrix();

    // Right tire
    glPushMatrix();
    glTranslatef(x + 0.305f, y - 0.58f, 0.0f); // Translate according to the position
    glColor3ub(0, 0, 0); // Black color for the tire
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    for (int i = 0; i <= 360; i++) {
        float angle = 2.0f * 3.1415926f * float(i) / float(360);
        float tireX = tireRadius * cosf(angle);
        float tireY = tireRadius * sinf(angle);
        glVertex2f(tireX, tireY);
    }
    glEnd();
    // Add rim
    glColor3ub(255, 255, 255); // White color for the rim
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= 360; i += 10) {
        float angle = 2.0f * 3.1415926f * float(i) / float(360);
        float innerRadius = tireRadius - 0.002f; // Adjust the inner radius of the rim
        float outerRadius = tireRadius + 0.002f; // Adjust the outer radius of the rim
        float innerX = innerRadius * cosf(angle);
        float innerY = innerRadius * sinf(angle);
        float outerX = outerRadius * cosf(angle);
        float outerY = outerRadius * sinf(angle);
        glVertex2f(innerX, innerY);
        glVertex2f(outerX, outerY);
    }
    glEnd();
    glPopMatrix();
}

//moving function for first car
void idle() {
    carSpeed = 0.001f * speedMultiplier;
    carPosX += carSpeed; // Move the car right
    if (carPosX > 0.72f) { // Reset the car's position if it goes off-screen
        carPosX = -1.3f;
    }
    glutPostRedisplay(); // Request a redraw
}

//moving function for second car
void idleCar2() {
    carSpeedCar2 = 0.0005f * speedMultiplier;
    carPosX2 -= carSpeedCar2; // Move the car left
    if (carPosX2 < -1.3f) { // Reset the car's position if it goes off-screen
        carPosX2 = 0.75f;
    }
    glutPostRedisplay(); // Request a redraw
}

//display function 
void display() {
    // Clear the color buffer with the appropriate background color
    if (isDay) {
        glClearColor(0.7f, 0.9f, 1.0f, 1.0f); // Day color
    }
    else {
        glClearColor(38 / 255.0, 77 / 255.0, 115 / 255.0, 1.0); // Night color
       
    }
    glClear(GL_COLOR_BUFFER_BIT);

    // Redraw the entire window to cover the sides with the background color
    glColor3f(0.7f, 0.9f, 1.0f); // Use the same background color as for clearing
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();

    //if daytime draw moving clouds , if night draw starts
    if (isDay) {
        clouds(-0.8, 0.8);
        clouds(-0.3, 0.65);
        clouds(0.2, 0.8);
        clouds(0.6, 0.75);
    }
    else {
        stars();
    }

    //call draw function to draw them
    drawKLTower();
    drawKLCC();
    road();
    buildings();
    drawSunMoon();
  
    //draw moving cars 
    movingCar(carPosX, -0.17f);
    movingCar2(carPosX2, -0.3f);


    // Swap the front and back buffers to display the rendered image
    glutSwapBuffers();
}

/* Handler for window re-size event. Called back when the window first appears and whenever the window is re-sized with its new width and height */
void reshape(int width, int height) {
    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the projection matrix to reflect the aspect ratio of the window
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width <= height) {
        glOrtho(-1.0, 1.0, -1.0 * height / width, 1.0 * height / width, -1.0, 1.0);
    }
    else {
        glOrtho(-1.0 * width / height, 1.0 * width / height, -1.0, 1.0, -1.0, 1.0);
    }

    // Switch back to the modelview matrix for further rendering
    glMatrixMode(GL_MODELVIEW);
}

//keyboard function for interaction 
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'c':
        isDay = !isDay; // Toggle day/night mode
        if (!isDay) {
            speedMultiplier = 0.2f; // Adjust speed for night mode , slower
        }
        else {
            cloudMoving = true;
            speedMultiplier = 1.0f; // Reset speed multiplier to normal for day mode
        }
        break;
    case 27:     // ESC key to exit program 
        exit(0);
        break;
    
   
    }
    glutPostRedisplay();
}

//combined function for both moving cars 
void combinedIdle() {
    idle();
    idleCar2();
}

//callback event for mouseclick
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Call the 's' event logic
        if (speedMultiplier == 0.0f) {
            if (!isDay) {
                speedMultiplier = 0.1f; // Adjust speed for night mode , slower
            }
            else {
                speedMultiplier = 1.0f; // Reset speed multiplier to normal for day mode
            }
        }
        else {
            speedMultiplier = 0.0f; // Stop all movement
        }
        cloudMoving = !cloudMoving; // Toggle cloud movement
        glutPostRedisplay();
    }
}

/* Callback handler for special-key event */
void specialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_F5:    // F5: Toggle between full-screen and windowed mode
        fullScreenMode = !fullScreenMode;         // Toggle state
        if (fullScreenMode) {                     // Full-screen mode
            glutFullScreen();                      // Switch into full screen
        }
        else {                                     // Windowed mode
            glutReshapeWindow(800, 480);          // Change window size
            glutPositionWindow(50, 50);           // Set window position
        }
        break;
    }
    glutPostRedisplay(); // Request a redraw of the window contents
}

//  Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);          // Initialize GLUT
    glutInitWindowSize(800, 480);   // Set the window's initial width & height - non-square
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutCreateWindow("Individual Assignment - Kuala Lumpur !!!");  // Create window with the given title
    glutDisplayFunc(display);       // Register callback handler for window re-paint event
    glutIdleFunc(combinedIdle);
    glutSpecialFunc(specialKeys); // Register callback handler for special-key event
    glutReshapeFunc(reshape);       // Register callback handler for window re-size event
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);   // Register callback handler for mouse event
    glutFullScreen();
    initGL();                       // Our own OpenGL initialization
    glutMainLoop();                 // Enter the infinite event-processing loop
    return 0;
}