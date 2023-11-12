# include <raylib.h>
# include <string.h>
# include <math.h>
# include <stdio.h>
# include "rlgl.h"
# include "rlights.h"
# include "rocket.h"
# define GLSL_VERSION 330


static int TIME = 0; // global time variable
static int SCENE = 7; // global scene counter
static int FLAG1 = 0; // init for countdown scene
static int FLAG2 = 659; // displays countdown
static int FLAG3 = 0; // init for liftoff
static int FLAG4 = 0; // init for outro scene

static Camera3D camera = { 0 };
static struct rocket rocket;
static Model model;
static Model cube;
static Shader shader;
static Light light;


//// Scene helpers

// Rendering tail fire
void drawFire(Vector3 rocketBasePosition, int thick = 0) {
    int numTriangles = 20;
    Color fireColor = ORANGE;

    if (thick == 0) {
        for (int i = 0; i < numTriangles; i++) {
            int randomOffset = GetRandomValue(5, 20);

            Vector3 p1 = {rocketBasePosition.x, rocketBasePosition.y - (i * 0.4f) - (randomOffset * 0.062f), rocketBasePosition.z};
            Vector3 p2 = {rocketBasePosition.x + 1.5f - (randomOffset * 0.025f), rocketBasePosition.y - i * 0.5f, rocketBasePosition.z};
            Vector3 p3 = {rocketBasePosition.x - 1.5f + (randomOffset * 0.025f), rocketBasePosition.y - i * 0.5f, rocketBasePosition.z};
            DrawTriangle3D(p1, p2, p3, fireColor);
        }
    }
    else if (thick == 1) {
        for (int i = 0; i < numTriangles; i++) {
            int randomOffset = GetRandomValue(5, 20);

            Vector3 p1 = {rocketBasePosition.x, rocketBasePosition.y - (i * 0.4f) - (randomOffset * 0.064f), rocketBasePosition.z};
            Vector3 p2 = {rocketBasePosition.x + 1.5f - (randomOffset * 0.025f), rocketBasePosition.y - i * 0.5f, rocketBasePosition.z};
            Vector3 p3 = {rocketBasePosition.x - 1.5f + (randomOffset * 0.025f), rocketBasePosition.y - i * 0.5f, rocketBasePosition.z};
            DrawTriangle3D(p1, p2, p3, fireColor);
            p1.x -= 0.8f;
            p2.x -= 0.8f;
            p3.x -= 0.8f;
            DrawTriangle3D(p1, p2, p3, fireColor);
            p1.x += 1.6f;
            p2.x += 1.6f;
            p3.x += 1.6f;
            DrawTriangle3D(p1, p2, p3, fireColor);
        }
    }
    else if (thick == 2) {
        for (int i = 0; i < numTriangles; i++) {
            int randomOffset = GetRandomValue(5, 20);

            Vector3 p1 = {rocketBasePosition.x - 0.4f, rocketBasePosition.y - (i * 0.4f) - (randomOffset * 0.064f), rocketBasePosition.z};
            Vector3 p2 = {rocketBasePosition.x + 1.1f - (randomOffset * 0.025f), rocketBasePosition.y - i * 0.5f, rocketBasePosition.z};
            Vector3 p3 = {rocketBasePosition.x - 1.9f + (randomOffset * 0.025f), rocketBasePosition.y - i * 0.5f, rocketBasePosition.z};
            DrawTriangle3D(p1, p2, p3, fireColor);
            p1 = {rocketBasePosition.x + 0.4f, rocketBasePosition.y - (i * 0.4f) - (randomOffset * 0.064f), rocketBasePosition.z};
            p2 = {rocketBasePosition.x + 1.9f - (randomOffset * 0.025f), rocketBasePosition.y - i * 0.5f, rocketBasePosition.z};
            p3 = {rocketBasePosition.x - 1.1f + (randomOffset * 0.025f), rocketBasePosition.y - i * 0.5f, rocketBasePosition.z};
            DrawTriangle3D(p1, p2, p3, fireColor);
        }
    }
}

// Intro text
void intro(int time) {
    char msg[] = "\"IT'S NOT POSSIBLE....\"\n\"NO IT'S NECESSARY....\"\nAs the earth's last hope, the Endurance\nprepares to launch.......";
    if (time/6 > (int)strlen(msg)) {
        DrawText(msg, 100, 100, 25, WHITE);
        SCENE++;
    }
    else DrawText(TextSubtext(msg, 0, time/5), 100, 100, 25, WHITE);
}

// Countdown sequence
void intro2(int time) {
    BeginMode3D(camera);
    rocket.draw();
    DrawGrid(1000, 5.0f);
    EndMode3D();
    char countdown[] = "00";
    if (FLAG2/60 > 0) {
        sprintf(countdown, "%d", FLAG2/60);
        DrawText(countdown, 375, 275, 100, BLACK);
        FLAG2--;
    }
    else {
        SCENE++;
        TIME = -1;
    }
}

// Liftoff
void liftoff1(int time) {
    if (rocket.head.y < 700) {
        BeginMode3D(camera);
        UpdateCameraPro(&camera, (Vector3){0.0f, 0.0f, time * 0.001f}, (Vector3){0.0f, 0.0f, 0.0f}, 0.0f);
        rocket.move(time * 0.001f);
        rocket.draw();
        drawFire((Vector3){rocket.body1.x, rocket.body1.y - 4.0f, rocket.body1.z}, 1);
        drawFire((Vector3){rocket.left1.x, rocket.left1.y - 4.0f, rocket.left1.z});
        drawFire((Vector3){rocket.right1.x, rocket.right1.y - 4.0f, rocket.right1.z});
        DrawGrid(1000, 5.0f);
        EndMode3D();
        char msg[] = "00000000";
        sprintf(msg, "%08d", (int)(round(rocket.head.y)));
        DrawText(msg, 50, 50, 15, BLACK);
    }
    else {
        SCENE++;
        TIME = -1;
    }
}

// First detach
void liftoff2(int time) {
    if (rocket.head.y < 1200) {
        BeginMode3D(camera);
        UpdateCameraPro(&camera, (Vector3){0.0f, 0.0f, time * 0.001f}, (Vector3){0.0f, 0.0f, 0.0f}, 0.0f);
        rocket.move(time * 0.001f, 1);
        rocket.draw(1);
        rocket.detach1(time * 0.006f);
        drawFire((Vector3){rocket.body1.x, rocket.body1.y - 4.0f, rocket.body1.z}, 1);
        drawFire((Vector3){rocket.left2.x, rocket.left2.y - 4.0f, rocket.left2.z});
        drawFire((Vector3){rocket.right2.x, rocket.right2.y - 4.0f, rocket.right2.z});
        DrawGrid(1000, 5.0f);
        EndMode3D();
        char msg[] = "00000000";
        sprintf(msg, "%08d", (int)(round(rocket.head.y)));
        DrawText(msg, 50, 50, 15, BLACK);
    }
    else {
        SCENE++;
        TIME = -1;
    }
}

// Second detach
void liftoff3(int time) {
    if (rocket.head.y < 1700) {
        BeginMode3D(camera);
        UpdateCameraPro(&camera, (Vector3){0.0f, 0.0f, time * 0.001f}, (Vector3){0.0f, 0.0f, 0.0f}, 0.0f);
        rocket.move(time * 0.001f, 2);
        rocket.draw(2);
        rocket.detach2(time * 0.006f);
        drawFire((Vector3){rocket.body2.x, rocket.body2.y - 4.0f, rocket.body2.z}, 1);
        drawFire((Vector3){rocket.left2.x, rocket.left2.y - 4.0f, rocket.left2.z});
        drawFire((Vector3){rocket.right2.x, rocket.right2.y - 4.0f, rocket.right2.z});
        DrawGrid(1000, 5.0f);
        EndMode3D();
        char msg[] = "00000000";
        sprintf(msg, "%08d", (int)(round(rocket.head.y)));
        DrawText(msg, 50, 50, 15, BLACK);
    }
    else {
        SCENE++;
        TIME = -1;
    }
}

// Third detach
void liftoff4(int time) {
    if (rocket.head.y < 2000) {
        BeginMode3D(camera);
        UpdateCameraPro(&camera, (Vector3){0.0f, 0.0f, time * 0.001f}, (Vector3){0.0f, 0.0f, 0.0f}, 0.0f);
        rocket.move(time * 0.001f, 3);
        rocket.draw(3);
        rocket.detach3(time * 0.006f);
        drawFire((Vector3){rocket.head.x, rocket.head.y - 1.0f, rocket.head.z}, 2);
        DrawGrid(1000, 5.0f);
        EndMode3D();
        char msg[] = "00000000";
        sprintf(msg, "%08d", (int)(round(rocket.head.y)));
        DrawText(msg, 50, 50, 15, BLACK);
    }
    else {
        SCENE++;
        TIME = -1;
    }
}

// Outro scene
void drift1(int TIME) {    
    BeginMode3D(camera);
    DrawModel(model, (Vector3){0, -2, 0}, 1.0f, WHITE);
    DrawModel(cube, (Vector3){-2.5f, 0, 0}, 1.0f, WHITE);
    if (light.enabled) {
        DrawSphereEx(light.position, 0.2f, 8, 8, light.color);
        DrawSphereWires(light.position, 0.2f, 8, 8, ColorAlpha(light.color, 0.5f));
    }
    /* else {
        DrawSphereEx(light.position, 0.2f, 8, 8, light.color);
        DrawSphereWires(light.position, 0.2f, 8, 8, ColorAlpha(light.color, 0.3f));
    } */
    DrawGrid(10, 1.0f);
    EndMode3D();
}
