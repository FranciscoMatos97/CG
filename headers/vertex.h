#include <vector>
#include "Point.h"

using namespace std;

vector<Point*> makePlane(float size);
vector<Point*> makeBox(float x, float y, float z, int divisions);
vector<Point*> makeCone(float radius, float height, int slices, int stacks);
//vector<Point*> makeSphere(float radius, int slices, int stacks);
