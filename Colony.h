#ifndef COLONY_H
#define COLONY_H

#include <vector>
#include <iostream>
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
    [[maybe_unused]] int type;
    [[maybe_unused]] int startVertice;
    double currentCost;

public:
    vector<int> answer;

    [[maybe_unused]] bool *isPassed;

    explicit Agent(int graphSize, int type);

    void setPassed(int vertex) const;

    void addVertexToAnswer(int vertex);

    int getLastVertex();

    void addCost(double cost);

    double getCurCost();
};

class Colony {
private:
    int size;
    // map<pair<int, int>, double> pheramones;  // первый элемент - пара id, второй - величина ферамона на ребре
    double **matrix;
    double **pheramones;
    vector<Point *> points;
    vector<Agent *> agents;
    double evaporationRate;  // Скорость высыхания ферамона
    double alpha;  // Первый подбираемый параметр
    double beta;  // Второй подбираемый параметр
    int optimalCostParam;  // параметр, имеющий величину порядка оптимального решения
    vector<int64_t> answer;  // текущий оптимальный ответ
    double answerCost;
    double denominatorSum;  // Знаменатель в формуле рассчета вероятности
    double denominatorMul;

public:
    static vector<string> split(const string &buffer, char separator);

    explicit Colony(int size1, int initType, double alpha, double beta, double evaporationRate, double optCostParam,
                    const string &fileName);

    void readCsv(const string &fileName);

    void readStdin();

    double **getMatrix();

    void setAlpha(double value);

    void setBeta(double value);

    void setOptimalCost(int value);

    int nextVertice(int current, Agent *agent);

    double getCost();

    double getProbabilitySum(int from, int to, Agent *agent);

    [[nodiscard]] double getNewPheramonLevel(double currentCost) const;

    double getProbability2(int from, int to);

    bool isCorrectAns();

    template<class T>
    static void printm(T **matrix, int64_t size) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cout << matrix[i][j] << "  ";
            }
            cout << '\n';
        }
    }

    template<class T>
    T sum(vector<T> v) {
        T sum = 0;
        for (auto &x : v)
            sum += x;
        return sum;
    }

    [[nodiscard]] int64_t getSize() const;

    double **getPheramonesMatrix();

    void iteration(int startVertex, int iter);

    void dryPheramone();

    string exportFinalResult();

    void drawGraph();

    string exportFrame(int it);

    void makeFrame(int it);

    static void makeVideo();
};

#endif  // COLONY_H
