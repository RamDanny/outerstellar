# include <stdio.h>
# include "raylib.h"
# include "rlgl.h"
# include "scene.h"


int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Outerstellar");

    SetTargetFPS(60);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();

        if (SCENE == 0) {
            ClearBackground(BLACK);
            intro(TIME);
        }
        else if (SCENE == 1) {
            ClearBackground(RAYWHITE);
            if (FLAG1 == 0) {
                camera.position = (Vector3){ 0.0f, 30.0f, 30.0f };  // Camera position
                camera.target = (Vector3){ 0.0f, 15.0f, 0.0f };      // Camera looking at point
                camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
                camera.fovy = 45.0f;                                // Camera field-of-view Y
                camera.projection = CAMERA_PERSPECTIVE;  
                rocket.init();
                FLAG1 = 1;
            }
            intro2(TIME);
        }
        else if (SCENE == 2) {
            ClearBackground(RAYWHITE);
            if (FLAG3 == 0) {
                camera.position = (Vector3){ 0.0f, 30.0f, 45.0f };  // Camera position
                camera.target = (Vector3){ 0.0f, 15.0f, 0.0f };      // Camera looking at point
                camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
                camera.fovy = 45.0f;                                // Camera field-of-view Y
                camera.projection = CAMERA_PERSPECTIVE;  
                rocket.init();
                FLAG3 = 1;
            }
            liftoff1(TIME);
        }
        else if (SCENE == 3) {
            ClearBackground(RAYWHITE);
            liftoff2(TIME);
        }
        else if (SCENE == 4) {
            ClearBackground(RAYWHITE);
            liftoff3(TIME);
        }
        else if (SCENE == 5) {
            ClearBackground(RAYWHITE);
            liftoff3(TIME);
        }
        else if (SCENE == 6) {
            ClearBackground(RAYWHITE);
            /* if (FLAG4 == 0) {
                camera.position = (Vector3){ 0.0f, 30.0f, 45.0f };  // Camera position
                camera.target = (Vector3){ 0.0f, 15.0f, 0.0f };      // Camera looking at point
                camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
                camera.fovy = 45.0f;                                // Camera field-of-view Y
                camera.projection = CAMERA_PERSPECTIVE;  
                rocket.init();
                FLAG4 = 1;
            } */
            liftoff4(TIME);
        }

        if (GetFrameTime() > 0) {
            TIME++;
        }

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context
    return 0;
}