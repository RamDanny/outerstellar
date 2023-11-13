# include <stdio.h>
# include "raylib.h"
# include "rlgl.h"
# include "rlights.h"
# include "scene.h"


int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Outerstellar");
    InitAudioDevice();
    Music music = LoadMusicStream("rsc/ticktock.mp3");
    SetTargetFPS(60);

    // lighting for outro
    ground = LoadModelFromMesh(GenMeshPlane(5000, 5000, 1, 1));
    model = LoadModelFromMesh(GenMeshPlane(10.0f, 10.0f, 3, 3));
    cube = LoadModelFromMesh(GenMeshCube(2.0f, 2.0f, 2.0f));
    shader = LoadShader(TextFormat("rsc/shaders/glsl%i/lighting.vs", GLSL_VERSION), TextFormat("rsc/shaders/glsl%i/lighting.fs", GLSL_VERSION)); // load shader
    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos"); // get shader location
    int ambientLoc = GetShaderLocation(shader, "ambient");
    float shadervals[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
    SetShaderValue(shader, ambientLoc, shadervals, SHADER_UNIFORM_VEC4);
    model.materials[0].shader = shader;
    cube.materials[0].shader = shader;
    headPos = (Vector3){-20, 20, 0};
    static Light light = CreateLight(LIGHT_POINT, (Vector3){0, 0, 0}, (Vector3){headPos.x, headPos.y, headPos.z}, YELLOW, shader);

    // sky bg textures
    sky1 = LoadTexture("rsc/sky.png");
    sky2 = LoadTexture("rsc/sky2.png");
    sky3 = LoadTexture("rsc/sky4.png");

    PlayMusicStream(music);


    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateMusicStream(music);
        float cameraPos[3] = { camera.position.x, camera.position.y, camera.position.z };
        SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
        light.enabled = true;
        UpdateLightValues(shader, light);

        BeginDrawing();

        if (SCENE == 0) {
            ClearBackground(BLACK);
            intro(TIME);
        }
        else if (SCENE == 1) {
            ClearBackground(SKYBLUE);
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
            ClearBackground(SKYBLUE);
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
            ClearBackground(SKYBLUE);
            liftoff2(TIME);
        }
        else if (SCENE == 4) {
            ClearBackground(BLUE);
            liftoff3(TIME);
        }
        else if (SCENE == 5) {
            ClearBackground(DARKBLUE);
            liftoff4(TIME);
        }
        else if (SCENE == 6) {
            ClearBackground(BLACK);
            if (FLAG4 == 0) {
                camera.position = (Vector3){ 0.0f, 45.0f, 45.0f };
                camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
                camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
                camera.fovy = 45.0f;
                camera.projection = CAMERA_PERSPECTIVE;
                headPos = (Vector3){-20, 20, 0};
                FLAG4 = 1;
            }
            drift1(TIME);
        }
        else if(SCENE == 7) {
            ClearBackground(BLACK);
            outro(TIME);
        }
        else if (SCENE == 8) {
            ClearBackground(BLACK);
            if (FLAG5 == 0) {
                camera.position = (Vector3){ 0.0f, 15.0f, 15.0f };
                camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
                camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
                camera.fovy = 45.0f;
                camera.projection = CAMERA_PERSPECTIVE;
                FLAG5 = 1;
            }
            finale(TIME);
        }
        else if (SCENE == 9) {
            ClearBackground(BLACK);
            credits(TIME);
        }
        else if (SCENE == 10) {
            break;
        }

        if (GetFrameTime() > 0) {
            TIME++;
        }

        EndDrawing();
    }
    
    StopMusicStream(music);
    UnloadMusicStream(music);
    CloseAudioDevice();
    UnloadModel(model);
    UnloadModel(cube);
    UnloadShader(shader);
    CloseWindow();        // Close window and OpenGL context
    return 0;
}