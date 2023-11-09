# include <raylib.h>

struct pc {
    Vector3 body;
    Vector3 head;
    Vector3 legl;
    Vector3 legr;
    Vector3 arml;
    Vector3 armr;
    void initPC();
    void draw();
    void move();
};
