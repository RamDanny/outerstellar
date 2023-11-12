# include <raylib.h>

struct rocket {
    Vector3 body1;
    Vector3 body2;
    Vector3 head;
    Vector3 left1;
    Vector3 left2;
    Vector3 right1;
    Vector3 right2;
    void init();
    void draw(int detach = 0);
    void move(float, int detach = 0);
    void detach1(float);
    void detach2(float);
    void detach3(float);
};
