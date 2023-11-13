# include <raylib.h>
# include <string.h>
# include <math.h>
# include <stdio.h>
# include "rlgl.h"
# include "rlights.h"
# include "rocket.h"
# define GLSL_VERSION 330


static int TIME = 0; // global time variable
static int SCENE = 0; // global scene counter
static int FLAG1 = 0; // init for countdown scene
static int FLAG2 = 659; // displays countdown
static int FLAG3 = 0; // init for liftoff
static int FLAG4 = 0; // init for outro scene
static int FLAG5 = 0; // init for final shot

// general
static Camera3D camera = { 0 };
static struct rocket rocket;
// outro
static Model ground;
static Model model;
static Model cube;
static Shader shader;
static Light light;
static Vector3 headPos = (Vector3){0, 0, 0};
//sky bg
static Texture2D sky1;
static Texture2D sky2;
static Texture2D sky3;


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
            DrawTriangle3D(p3, p2, p1, fireColor);
        }
    }
    else if (thick == 1) {
        for (int i = 0; i < numTriangles; i++) {
            int randomOffset = GetRandomValue(5, 20);

            Vector3 p1 = {rocketBasePosition.x, rocketBasePosition.y - (i * 0.4f) - (randomOffset * 0.064f), rocketBasePosition.z};
            Vector3 p2 = {rocketBasePosition.x + 1.5f - (randomOffset * 0.025f), rocketBasePosition.y - i * 0.5f, rocketBasePosition.z};
            Vector3 p3 = {rocketBasePosition.x - 1.5f + (randomOffset * 0.025f), rocketBasePosition.y - i * 0.5f, rocketBasePosition.z};
            DrawTriangle3D(p1, p2, p3, fireColor);
            DrawTriangle3D(p3, p2, p1, fireColor);
            p1.x -= 0.8f;
            p2.x -= 0.8f;
            p3.x -= 0.8f;
            DrawTriangle3D(p1, p2, p3, fireColor);
            DrawTriangle3D(p3, p2, p1, fireColor);
            p1.x += 1.6f;
            p2.x += 1.6f;
            p3.x += 1.6f;
            DrawTriangle3D(p1, p2, p3, fireColor);
            DrawTriangle3D(p3, p2, p1, fireColor);
        }
    }
    else if (thick == 2) {
        for (int i = 0; i < numTriangles; i++) {
            int randomOffset = GetRandomValue(5, 20);

            Vector3 p1 = {rocketBasePosition.x - 0.4f, rocketBasePosition.y - (i * 0.4f) - (randomOffset * 0.064f), rocketBasePosition.z};
            Vector3 p2 = {rocketBasePosition.x + 1.1f - (randomOffset * 0.025f), rocketBasePosition.y - i * 0.5f, rocketBasePosition.z};
            Vector3 p3 = {rocketBasePosition.x - 1.9f + (randomOffset * 0.025f), rocketBasePosition.y - i * 0.5f, rocketBasePosition.z};
            DrawTriangle3D(p1, p2, p3, fireColor);
            DrawTriangle3D(p3, p2, p1, fireColor);
            p1 = {rocketBasePosition.x + 0.4f, rocketBasePosition.y - (i * 0.4f) - (randomOffset * 0.064f), rocketBasePosition.z};
            p2 = {rocketBasePosition.x + 1.9f - (randomOffset * 0.025f), rocketBasePosition.y - i * 0.5f, rocketBasePosition.z};
            p3 = {rocketBasePosition.x - 1.1f + (randomOffset * 0.025f), rocketBasePosition.y - i * 0.5f, rocketBasePosition.z};
            DrawTriangle3D(p1, p2, p3, fireColor);
            DrawTriangle3D(p3, p2, p1, fireColor);
        }
    }
}

// Draw sphere at 0,0,0 with radius 1.0
void DrawSphereBasic(Color color)
{
    int rings = 16;
    int slices = 16;

    // Make sure there is enough space in the internal render batch
    // buffer to store all required vertex, batch is reseted if required
    rlCheckRenderBatchLimit((rings + 2)*slices*6);

    rlBegin(RL_TRIANGLES);
        rlColor4ub(color.r, color.g, color.b, color.a);

        for (int i = 0; i < (rings + 2); i++)
        {
            for (int j = 0; j < slices; j++)
            {
                rlVertex3f(cosf(DEG2RAD*(270+(180/(rings + 1))*i))*sinf(DEG2RAD*(j*360/slices)),
                           sinf(DEG2RAD*(270+(180/(rings + 1))*i)),
                           cosf(DEG2RAD*(270+(180/(rings + 1))*i))*cosf(DEG2RAD*(j*360/slices)));
                rlVertex3f(cosf(DEG2RAD*(270+(180/(rings + 1))*(i+1)))*sinf(DEG2RAD*((j+1)*360/slices)),
                           sinf(DEG2RAD*(270+(180/(rings + 1))*(i+1))),
                           cosf(DEG2RAD*(270+(180/(rings + 1))*(i+1)))*cosf(DEG2RAD*((j+1)*360/slices)));
                rlVertex3f(cosf(DEG2RAD*(270+(180/(rings + 1))*(i+1)))*sinf(DEG2RAD*(j*360/slices)),
                           sinf(DEG2RAD*(270+(180/(rings + 1))*(i+1))),
                           cosf(DEG2RAD*(270+(180/(rings + 1))*(i+1)))*cosf(DEG2RAD*(j*360/slices)));

                rlVertex3f(cosf(DEG2RAD*(270+(180/(rings + 1))*i))*sinf(DEG2RAD*(j*360/slices)),
                           sinf(DEG2RAD*(270+(180/(rings + 1))*i)),
                           cosf(DEG2RAD*(270+(180/(rings + 1))*i))*cosf(DEG2RAD*(j*360/slices)));
                rlVertex3f(cosf(DEG2RAD*(270+(180/(rings + 1))*(i)))*sinf(DEG2RAD*((j+1)*360/slices)),
                           sinf(DEG2RAD*(270+(180/(rings + 1))*(i))),
                           cosf(DEG2RAD*(270+(180/(rings + 1))*(i)))*cosf(DEG2RAD*((j+1)*360/slices)));
                rlVertex3f(cosf(DEG2RAD*(270+(180/(rings + 1))*(i+1)))*sinf(DEG2RAD*((j+1)*360/slices)),
                           sinf(DEG2RAD*(270+(180/(rings + 1))*(i+1))),
                           cosf(DEG2RAD*(270+(180/(rings + 1))*(i+1)))*cosf(DEG2RAD*((j+1)*360/slices)));
            }
        }
    rlEnd();
}

void drawSphere(Vector3 position, float radius, Color color) {
    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
    rlScalef(radius, radius, radius);
    DrawSphereBasic(color);
    rlPopMatrix();
}

// Intro text
void intro(int time) {
    char msg[] = "\"IT'S NOT POSSIBLE....\"\n\"NO IT'S NECESSARY....\"\nAs the dying earth's last hope, the\n Jeevanyaan spacecraft prepares to launch.......";
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
    DrawModel(ground, (Vector3){0, -1, 0}, 1.0, GREEN);
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
        //DrawGrid(1000, 5.0f);
        DrawModel(ground, (Vector3){0, 0, 0}, 1.0, GREEN);
        EndMode3D();
        /* char msg[] = "00000000";
        sprintf(msg, "%08d", (int)(round(rocket.head.y)));
        DrawText(msg, 50, 50, 15, BLACK); */
    }
    else {
        SCENE++;
        TIME = -1;
    }
}

// First detach
void liftoff2(int time) {
    DrawTexturePro(sky1, (Rectangle){0, 0, sky1.width, sky1.height}, (Rectangle){0, -500+(time*0.5f), GetScreenWidth(), GetScreenHeight()}, (Vector2){0, 0}, 0, WHITE);
    DrawTexturePro(sky1, (Rectangle){0, 0, sky1.width, sky1.height}, (Rectangle){0, (time*0.5f), GetScreenWidth(), GetScreenHeight()}, (Vector2){0, 0}, 0, WHITE);
    if (rocket.head.y < 1200) {
        BeginMode3D(camera);
        camera.position.x = rocket.head.x + sinf(GetTime()*0.5) * 60;
        camera.position.z = rocket.head.z + cosf(GetTime()*0.5) * 60;
        UpdateCameraPro(&camera, (Vector3){0.0f, 0.0f, time * 0.001f}, (Vector3){0.0f, 0.0f, 0.0f}, 0.0f);
        rocket.move(time * 0.001f, 1);
        rocket.draw(1);
        rocket.detach1(time * 0.006f);
        drawFire((Vector3){rocket.body1.x, rocket.body1.y - 4.0f, rocket.body1.z}, 1);
        drawFire((Vector3){rocket.left2.x, rocket.left2.y - 4.0f, rocket.left2.z});
        drawFire((Vector3){rocket.right2.x, rocket.right2.y - 4.0f, rocket.right2.z});
        //DrawGrid(1000, 5.0f);
        DrawModel(ground, (Vector3){0, 0, 0}, 1.0, GREEN);
        EndMode3D();
        /* char msg[] = "00000000";
        sprintf(msg, "%08d", (int)(round(rocket.head.y)));
        DrawText(msg, 50, 50, 15, BLACK); */
    }
    else {
        SCENE++;
        TIME = -1;
    }
}

// Second detach
void liftoff3(int time) {
    DrawTexturePro(sky2, (Rectangle){0, 0, sky2.width, sky2.height}, (Rectangle){0, -1200+(time*0.5f), GetScreenWidth(), GetScreenHeight()}, (Vector2){0, 0}, 0, WHITE);
    DrawTexturePro(sky2, (Rectangle){0, 0, sky2.width, sky2.height}, (Rectangle){0, -600+(time*0.5f), GetScreenWidth(), GetScreenHeight()}, (Vector2){0, 0}, 0, WHITE);
    DrawTexturePro(sky2, (Rectangle){0, 0, sky2.width, sky2.height}, (Rectangle){0, (time*0.5f), GetScreenWidth(), GetScreenHeight()}, (Vector2){0, 0}, 0, WHITE);
    if (rocket.head.y < 1700) {
        BeginMode3D(camera);
        camera.position.x = rocket.head.x + sinf(GetTime()*0.5) * 60;
        camera.position.z = rocket.head.z + cosf(GetTime()*0.5) * 60;
        UpdateCameraPro(&camera, (Vector3){0.0f, 0.0f, time * 0.001f}, (Vector3){0.0f, 0.0f, 0.0f}, 0.0f);
        rocket.move(time * 0.001f, 2);
        rocket.draw(2);
        rocket.detach2(time * 0.006f);
        drawFire((Vector3){rocket.body2.x, rocket.body2.y - 4.0f, rocket.body2.z}, 1);
        drawFire((Vector3){rocket.left2.x, rocket.left2.y - 4.0f, rocket.left2.z});
        drawFire((Vector3){rocket.right2.x, rocket.right2.y - 4.0f, rocket.right2.z});
        EndMode3D();
        /* char msg[] = "00000000";
        sprintf(msg, "%08d", (int)(round(rocket.head.y)));
        DrawText(msg, 50, 50, 15, BLACK); */
    }
    else {
        SCENE++;
        TIME = -1;
    }
}

// Third detach
void liftoff4(int time) {
    DrawTexturePro(sky3, (Rectangle){0, 0, sky3.width, sky3.height}, (Rectangle){0, -1000+(time*0.5f), GetScreenWidth(), GetScreenHeight()}, (Vector2){0, 0}, 0, WHITE);
    DrawTexturePro(sky3, (Rectangle){0, 0, sky3.width, sky3.height}, (Rectangle){0, -500+(time*0.5f), GetScreenWidth(), GetScreenHeight()}, (Vector2){0, 0}, 0, WHITE);
    DrawTexturePro(sky3, (Rectangle){0, 0, sky3.width, sky3.height}, (Rectangle){0, time*0.5f, GetScreenWidth(), GetScreenHeight()}, (Vector2){0, 0}, 0, WHITE);
    if (rocket.head.y < 2000) {
        BeginMode3D(camera);
        camera.position.x = rocket.head.x + sinf(GetTime()*0.5) * 60;
        camera.position.z = rocket.head.z + cosf(GetTime()*0.5) * 60;
        UpdateCameraPro(&camera, (Vector3){0.0f, 0.0f, time * 0.001f}, (Vector3){0.0f, 0.0f, 0.0f}, 0.0f);
        rocket.move(time * 0.001f, 3);
        rocket.draw(3);
        rocket.detach3(time * 0.006f);
        drawFire((Vector3){rocket.head.x, rocket.head.y - 1.0f, rocket.head.z}, 2);
        EndMode3D();
        /* char msg[] = "00000000";
        sprintf(msg, "%08d", (int)(round(rocket.head.y)));
        DrawText(msg, 50, 50, 15, BLACK); */
    }
    else {
        SCENE++;
        TIME = -1;
    }
}

// Outro scene
void drift1(int time) {
    if (headPos.x < 30) {
        BeginMode3D(camera);
        rlPushMatrix();
        rlTranslatef(headPos.x, headPos.y, headPos.z);
        rlRotatef(time*2, 1, 1, 1);
        rlTranslatef(-headPos.x, -headPos.y, -headPos.z);
        DrawModel(cube, headPos, 1.0f, WHITE);
        rlPopMatrix();
        headPos.x += time * 0.001f;
        headPos.y -= time * 0.0001f;
        headPos.z += time * 0.001f;
        drawSphere((Vector3){-28, 24, -5}, 5.5 - (TIME * 0.01f), BLUE);
        EndMode3D();
    }
    else {
        SCENE++;
        TIME = -1;
    }
}

// Outro text
void outro(int time) {
    char msg[] = "Jeevanyaan bids farewell to the pale blue dot\ncalled home, speeding towards\nthe space that lies beyond....\nBut is it ready for what's next????";
    if (time/6 > (int)strlen(msg)) {
        DrawText(msg, 100, 100, 25, WHITE);
        SCENE++;
        TIME = -1;
    }
    else DrawText(TextSubtext(msg, 0, time/5), 100, 100, 25, WHITE);
}

// Final shot
void finale(int time) {
    if (time < 660) {
        BeginMode3D(camera);
        for (int i = 0; i < 360; i += 45) {
            DrawCircle3D((Vector3){ 0, 0, 0 }, 1.0f + (i * 0.001f), (Vector3){0, 1, 1}, i*time*0.02f, Color{ 255, 165, 0, 255 });
            if (i % 10 == 0) {
                for (float r = 4.0f; r < 5.0f; r+=0.01f) {
                    DrawCircle3D((Vector3){ 0, 0, 0 }, r + (i * 0.01f), (Vector3){1, 0, 1}, i*time*0.002f, Color{ 255, 165, 0, 255 });
                }
            }
        }
        DrawSphereBasic((Color){255, 200, 200, 1});
        EndMode3D();
    }
    else {
        SCENE++;
        TIME = -1;
    }
}

// credits
void credits(int time) {
    char msg1[] = "OUTERSTELLAR";
    char msg2[] = "by\n\t\t\tRamdhanush.V\n\t\t\tRoshan.S";
    if (time/6 < (int)strlen(msg1)) {
        DrawText(TextSubtext(msg1, 0, time/5), 200, 200, 50, WHITE);
    }
    else if (time/6 < (int)strlen(msg2)) {
        DrawText(msg1, 200, 200, 50, WHITE);
        DrawText(TextSubtext(msg2, 0, time/5), 250, 250, 25, WHITE);
    }
    else {
        DrawText(msg1, 200, 200, 50, WHITE);
        DrawText(msg2, 250, 250, 25, WHITE);
    }
    if (time/20 > (int)strlen(msg2)) {
        SCENE++;
    }
}
