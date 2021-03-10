
#ifndef COLONY_H
#define COLONY_H

#include <vector>

using namespace std;

enum AgentTypes {
    COMMON,
    ELITE
};

typedef struct point {
    double x;
    double y;
    int id;
} Point;

class Agent {
private:
    vector<bool>isPassed;
    int type;
    int vertice;
public:
};

class Colony {
private:
   vector<Point> points;
   int evaporationRate;
   int alpha;
   int beta;


public:

};
#endif //!COLONY_H
