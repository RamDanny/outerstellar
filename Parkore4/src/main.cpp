#include "raylib.h"
# include "pc.h"


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Parkore");

    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };  // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type
    struct pc p1;
    p1.initPC();


    SetTargetFPS(60);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // TODO: Update your variables here
        UpdateCameraPro(&camera, (Vector3){0.05f, 0.0f, 0.0f}, (Vector3){0.0f, 0.0f, 0.0f}, 0.0f);
        p1.move();

        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                p1.draw();

                DrawGrid(1000, 1.0f);

            EndMode3D();

        EndDrawing();
    }
    CloseWindow();        // Close window and OpenGL context
    return 0;
}