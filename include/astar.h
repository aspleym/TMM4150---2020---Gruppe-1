#define X_MAX 300
#define Y_MAX 200

#define ROBOT_XSIZE 20
#define ROBOT_YSIZE 20

struct Node
{
    int x;
    int y;
    int parentX;
    int parentY;
    float gCost;
    float hCost;
    float fCost;
};

void setupNetwork();
void changeNode(int xpos, int ypos);
Node getPath();