#include <iostream>
#include <cmath>
#include <random>
#include <fstream>
#include <algorithm>

#include "Colony.h"

#define int int64_t

double dist(Point first, Point second) {
    return sqrt(pow(first.x - second.x, 2) + pow(first.y - second.y, 2));
}

Colony::Colony(int64_t size1, int64_t initType, string fileName) {
    this->size = size1;
    this->points.resize(size1);
    this->answer.resize(size1);
    int id1, x1, y1;
    if (initType == STDIN) {
        this->readStdin();
    } else if (initType == CSV) {
        this->readCsv(fileName);
    }
}

void Colony::readCsv(string fileName) {
    ifstream input(fileName);
    string line;
    input >> line;
    int id1;
    double x1;
    double y1;
    for (int i = 0; i < size; ++i) {
        input >> line;
        auto lineContent = Colony::split(line, ',');
        id1 = atol(lineContent[0].c_str());
        x1 = atof(lineContent[1].c_str());
        y1 = atof(lineContent[2].c_str());
        points[i] = new Point(x1, y1, id1);
    }
}

vector<string> Colony::split(string buffer, char separator) {
    vector<string> result;
    string buf;
    for (auto &x : buffer + separator) {
        if (x == separator) {
            if (!buf.empty()) {
                result.push_back(buf);
                buf = "";
            } else {
                buf += x;
            }
        }
    }
    return result;
}

void Colony::readStdin() {
    int id1;
    double x1;
    double y1;
    for (int i = 0; i < size; ++i) {
        cin >> id1 >> x1 >> y1;
        points[i] = new Point(x1, y1, id1);
    }
}

void Colony::setAlpha(double value) {
    this->alpha = value;
}

void Colony::setBeta(double value) {
    this->beta = value;
}

void Colony::setOptimalCost(int64_t value) {
    this->optimalCost = value;
}

double Colony::getCost() {
    double result = 0;
    for (int i = 0; i < size; ++i) {
        result += dist(*points[i], *points[(i + 1) % size]);
    }
    return result;
}

bool Colony::isCorrectAns() {
    bool *cor = new bool[size];
    for (int i = 0; i < size; ++i) {
        if (cor[answer[i]]) return false;
        cor[answer[i]] = true;
    }
    return true;
}
