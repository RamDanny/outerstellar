/*# include "raylib.h"
# include "rlgl.h"
# include "pc.h"


int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Parkore");

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };  // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type
    struct pc p1;
    p1.initPC();
    
    Vector3 box = {-5.0f, -1.0f, 0.0f};
    float rotleg = 0.0f;
    int delta = 5;

    SetTargetFPS(60);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // TODO: Update your variables here
        UpdateCameraPro(&camera, (Vector3){0.15f, 0.0f, 0.0f}, (Vector3){0.0f, 0.0f, 0.0f}, 0.0f);
        //p1.move();

        box.z -= 0.15f;
        if (rotleg > 45 || rotleg < -45) delta = -delta;
        rotleg += delta;

        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                rlPushMatrix(); // rotation only applies until rlPopMatrix below
                rlTranslatef(box.x, 0, box.z);
                rlRotatef(rotleg, 1, 0, 0); // rotate 45 degrees along <1,0,0> x-axis
                rlTranslatef(-box.x, 0, -box.z);
                DrawCube(box, 1.0f, 2.0f, 1.0f, RED);
                DrawCubeWires(box, 1.0f, 2.0f, 1.0f, MAROON);
                rlPopMatrix();

                //p1.draw();

                DrawGrid(1000, 1.0f);

            EndMode3D();

        EndDrawing();
    }
    CloseWindow();        // Close window and OpenGL context
    return 0;
}*/