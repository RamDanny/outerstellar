# include <raylib.h>
# include <rlgl.h>
# include "rocket.h"

void rocket::init() {
    body1 = (Vector3) { 0.0f, 4.0f, 0.0f };
    body2 = (Vector3) { 0.0f, 14.0f, 0.0f };
    head = (Vector3) { 0.0f, 21.0f, 0.0f };
    left1 = (Vector3) { -2.5f, 4.0f, 0.0f };
    left2 = (Vector3) { -2.5f, 12.0f, 0.0f };
    right1 = (Vector3) { 2.5f, 4.0f, 0.0f };
    right2 = (Vector3) { 2.5f, 12.0f, 0.0f };
}

void rocket::draw(int detach) {
    if (detach == 0) {
        DrawCube(body1, 3.0f, 8.0f, 3.0f, GRAY);
        DrawCubeWires(body1, 3.0f, 8.0f, 3.0f, DARKGRAY);
        DrawCube(body2, 3.0f, 12.0f, 3.0f, GRAY);
        DrawCubeWires(body2, 3.0f, 12.0f, 3.0f, DARKGRAY);
        DrawCube(head, 2.0f, 2.0f, 2.0f, DARKGRAY);
        DrawCubeWires(head, 2.0f, 2.0f, 2.0f, WHITE);
        DrawCube(left1, 2.0f, 8.0f, 2.0f, GRAY);
        DrawCubeWires(left1, 2.0f, 8.0f, 2.0f, DARKGRAY);
        DrawCube(left2, 2.0f, 8.0f, 2.0f, GRAY);
        DrawCubeWires(left2, 2.0f, 8.0f, 2.0f, DARKGRAY);
        DrawCube(right1, 2.0f, 8.0f, 2.0f, GRAY);
        DrawCubeWires(right1, 2.0f, 8.0f, 2.0f, DARKGRAY);
        DrawCube(right2, 2.0f, 8.0f, 2.0f, GRAY);
        DrawCubeWires(right2, 2.0f, 8.0f, 2.0f, DARKGRAY);
    }
    else if (detach == 1) {
        DrawCube(body1, 3.0f, 8.0f, 3.0f, GRAY);
        DrawCubeWires(body1, 3.0f, 8.0f, 3.0f, DARKGRAY);
        DrawCube(body2, 3.0f, 12.0f, 3.0f, GRAY);
        DrawCubeWires(body2, 3.0f, 12.0f, 3.0f, DARKGRAY);
        DrawCube(head, 2.0f, 2.0f, 2.0f, DARKGRAY);
        DrawCubeWires(head, 2.0f, 2.0f, 2.0f, WHITE);
        DrawCube(left2, 2.0f, 8.0f, 2.0f, GRAY);
        DrawCubeWires(left2, 2.0f, 8.0f, 2.0f, DARKGRAY);
        DrawCube(right2, 2.0f, 8.0f, 2.0f, GRAY);
        DrawCubeWires(right2, 2.0f, 8.0f, 2.0f, DARKGRAY);
    }
    else if (detach == 2) {
        DrawCube(body2, 3.0f, 12.0f, 3.0f, GRAY);
        DrawCubeWires(body2, 3.0f, 12.0f, 3.0f, DARKGRAY);
        DrawCube(head, 2.0f, 2.0f, 2.0f, DARKGRAY);
        DrawCubeWires(head, 2.0f, 2.0f, 2.0f, WHITE);
        DrawCube(left2, 2.0f, 8.0f, 2.0f, GRAY);
        DrawCubeWires(left2, 2.0f, 8.0f, 2.0f, DARKGRAY);
        DrawCube(right2, 2.0f, 8.0f, 2.0f, GRAY);
        DrawCubeWires(right2, 2.0f, 8.0f, 2.0f, DARKGRAY);
    }
    else if (detach == 3) {
        DrawCube(head, 2.0f, 2.0f, 2.0f, DARKGRAY);
        DrawCubeWires(head, 2.0f, 2.0f, 2.0f, WHITE);
    }
}

void rocket::move(float spd, int detach) {
    if (detach == 0) {
        body1.y += spd;
        body2.y += spd;
        head.y += spd;
        left1.y += spd;
        left2.y += spd;
        right1.y += spd;
        right2.y += spd;
    }
    else if (detach == 1) {
        body1.y += spd;
        body2.y += spd;
        head.y += spd;
        left1.y += spd * 0.75;
        left2.y += spd;
        right1.y += spd * 0.75;
        right2.y += spd;
    }
    else if (detach == 2) {
        body1.y += spd * 0.6;
        body2.y += spd;
        head.y += spd;
        left2.y += spd;
        right2.y += spd;
    }
    else if (detach == 3) {
        head.y += spd;
        body2.y += spd * 0.6;
        left2.y += spd * 0.8;
        right2.y += spd * 0.8;
    }
}

void rocket::detach1(float spd) {
    rlPushMatrix();
    rlRotatef(spd, 1, 0, 1);
    DrawCube(left1, 2.0f, 8.0f, 2.0f, GRAY);
    DrawCubeWires(left1, 2.0f, 8.0f, 2.0f, DARKGRAY);
    rlPopMatrix();

    rlPushMatrix();
    rlRotatef(-spd, 0, 0, 1);
    DrawCube(right1, 2.0f, 8.0f, 2.0f, GRAY);
    DrawCubeWires(right1, 2.0f, 8.0f, 2.0f, DARKGRAY);
    rlPopMatrix();
}

void rocket::detach2(float spd) {
    rlPushMatrix();
    rlRotatef(spd, 0, 1, 0);
    DrawCube(body1, 3.0f, 8.0f, 3.0f, GRAY);
    DrawCubeWires(body1, 3.0f, 8.0f, 3.0f, DARKGRAY);
    rlPopMatrix();
}

void rocket::detach3(float spd) {
    rlPushMatrix();
    rlRotatef(spd, 0, 0, 1);
    DrawCube(left2, 2.0f, 8.0f, 2.0f, GRAY);
    DrawCubeWires(left2, 2.0f, 8.0f, 2.0f, DARKGRAY);
    rlPopMatrix();

    rlPushMatrix();
    rlRotatef(spd, 0, 1, 0);
    DrawCube(body2, 3.0f, 12.0f, 3.0f, GRAY);
    DrawCubeWires(body2, 3.0f, 12.0f, 3.0f, DARKGRAY);
    rlPopMatrix();

    rlPushMatrix();
    rlRotatef(-spd, 1, 0, 1);
    DrawCube(right2, 2.0f, 8.0f, 2.0f, GRAY);
    DrawCubeWires(right2, 2.0f, 8.0f, 2.0f, DARKGRAY);
    rlPopMatrix();
}
