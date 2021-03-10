#ifndef COLONY_H
#define COLONY_H

#include <vector>
#include <map>
#include <string>
#include <cmath>

#include "primes.h"

using namespace std;

#define int int64_t

static bool isPrime(int x) {
    auto position = lower_bound(primes, primes + PRIMES_COUNT, x);
    if (*position == x) return true;
    return false;
}

enum AgentTypes {
    COMMON,
    ELITE
};

enum DataInitType {
    STDIN,
    CSV,
};

typedef struct Point {
public:
    explicit Point(double x1, double y1, int id1) {
        x = x1;
        y = y1;
        id = id1;
    }

    [[nodiscard]] double dist(struct Point other) const {
        return sqrt(pow(x - other.x, 2.) + pow(y - other.y, 2));
    }

    double x;
    double y;
    int id;
} Point;

class Agent {
private:
    [[maybe_unused]] vector<bool> isPassed;
    [[maybe_unused]] int type;
    [[maybe_unused]] int vertice;
    int currentCost;
public:
};

class Colony {
private:
    int size;
    map<pair<int, int>, double> pheramones;  // первый элемент - пара id, второй - величина ферамона на ребре
    vector<Point *> points;
    int evaporationRate;  // Скорость высыхания ферамона
    double alpha;  // Первый подбираемый параметр
    double beta;  // Второй подбираемый параметр
    int optimalCost;  // параметр, имеющий величину порядка оптимального решения
    vector<int> answer;  // текущий оптимальный ответ

public:
    static vector<string> split(string buffer, char separator);

    explicit Colony(int size1, int initType, string fileName = "input.csv");

    void readCsv(string fileName);

    void readStdin();

    void setAlpha(double value);

    void setBeta(double value);

    void setOptimalCost(int value);

    double getCost();

    bool isCorrectAns();
};

#endif  // COLONY_H
