# include <raylib.h>
# include "pc.h"

void pc::initPC() {
    body = (Vector3) { 0.0f, 2.0f, 0.0f };
    head = (Vector3) { 0.0f, 3.5f, 0.0f };
    legl = (Vector3) { -0.5f, 0.5f, 0.0f };
    legr = (Vector3) { 0.5f, 0.5f, 0.0f };
    arml = (Vector3) { -1.0f, 2.0f, 0.0f };
    armr = (Vector3) { 1.0f, 2.0f, 0.0f };
}

void pc::draw() {
    DrawCube(body, 1.5f, 2.0f, 2.0f, RED);
    DrawCubeWires(body, 1.5f, 2.0f, 2.0f, MAROON);
    DrawCube(head, 1.0f, 1.0f, 1.0f, BLUE);
    DrawCubeWires(head, 1.0f, 1.0f, 1.0f, VIOLET);
    DrawCube(legl, 0.5f, 1.0f, 0.5f, GREEN);
    DrawCubeWires(legl, 0.5f, 1.0f, 0.5f, DARKGREEN);
    DrawCube(legr, 0.5f, 1.0f, 0.5f, GREEN);
    DrawCubeWires(legr, 0.5f, 1.0f, 0.5f, DARKGREEN);
    DrawCube(arml, 0.5f, 2.0f, 0.5f, GREEN);
    DrawCubeWires(arml, 0.5f, 2.0f, 0.5f, DARKGREEN);
    DrawCube(armr, 0.5f, 2.0f, 0.5f, GREEN);
    DrawCubeWires(armr, 0.5f, 2.0f, 0.5f, DARKGREEN);
}

void pc::move() {
    body.z -= 0.05f;
    head.z -= 0.05f;
    legl.z -= 0.05f;
    legr.z -= 0.05f;
    arml.z -= 0.05f;
    armr.z -= 0.05f;
}
