#include <iostream>
#include <cmath>
#include <random>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <thread>

#include "Colony.h"

static const std::string path = "/home/toliman/Projects/Algorithms-AntColony/";


#define int int64_t
#define rep(x) for (int i = 0; i < (x); ++i)


template<class T>
void print(T t) {
    std::cout << t << std::endl;
}

template<class T>
void print(T array, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << ' ';
    }
    std::cout << std::endl;
}

double dist(Point first, Point second) {
    return sqrt(pow(first.x - second.x, 2) + pow(first.y - second.y, 2));
}

Colony::Colony(int64_t size1, int64_t initType, double alpha1, double beta1, double evRate1, double optCost1,
               const string &fileName) {
    this->size = size1;
    this->evaporationRate = evRate1;
    this->optimalCostParam = optCost1;

    this->points.resize(size1);
    this->answer.resize(size1);

    this->answerCost = 1e9;

    this->setAlpha(alpha1);
    this->setBeta(beta1);

    for (int i = 0; i < size1; ++i) {
        for (int j = i + i; j < size1; ++j) {
        }
    }

    this->matrix = new double *[size1];
    this->pheramones = new double *[size1];
    for (int i = 0; i < size1; ++i) {
        matrix[i] = new double[size1];
        pheramones[i] = new double[size1];
    }
    rep(size1) {
        matrix[i][i] = 0;
        pheramones[i][i] = 0;
    }

    if (initType == STDIN) {
        this->readStdin();
    } else if (initType == CSV) {
        this->readCsv(fileName);
    }

    for (int i = 0; i < size1; ++i) {
        for (int j = i + 1; j < size1; ++j) {
            double dist = this->points[i]->dist(*this->points[j]);
            matrix[i][j] = dist;
            matrix[j][i] = dist;
        }
    }

    for (int i = 0; i < size1; ++i) {
        for (int j = i + 1; j < size1; ++j) {
            pheramones[i][j] = .5;
            pheramones[j][i] = .5;
        }
    }
}

void Colony::readCsv(const string &fileName) {
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

vector<string> Colony::split(const string &buffer, char separator) {
    vector<string> result;
    string buf;
    for (auto x : buffer + separator) {
        if (x == separator) {
            if (!buf.empty()) {
                result.push_back(buf);
                buf = "";
            }
        } else {
            buf += x;
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
    this->optimalCostParam = value;
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

double Colony::getNewPheramonLevel(double currentCost) const {
    return this->optimalCostParam / max(1., currentCost);
}

double Colony::getProbability2(int64_t from, int64_t to) {
    return 0;
}

double getRandomDoubleFrom0To1() {
    random_device gen;
    return static_cast<double>(gen() % 65536) / 65536.;
}

double getRandomDouble(double lower, double upper) {
    double result = getRandomDoubleFrom0To1();
    result *= upper - lower;
    result += lower;
    return result;
}

int Colony::nextVertice(int64_t current, Agent *agent) {
    vector<double> probabilities(size);

    for (int i = 0; i < size; ++i) {
        probabilities[i] = getProbabilitySum(current, i, agent);
    }

    double s = sum(probabilities);

    double pointer = getRandomDouble(0, s);

    for (int i = 0; i < size; ++i) {
        if (pointer < probabilities[i]) {
            return i;
        }
        pointer -= probabilities[i];
    }

    return 0;
}

double Colony::getProbabilitySum(int64_t from, int64_t to, Agent *agent) {
    double result = 0.;

    if (from != to && !(agent->isPassed[to]))
        result += pow(pheramones[from][to], alpha) + pow(1. / matrix[from][to], beta);

    return result;
}

double **Colony::getMatrix() {
    return this->matrix;
}

int64_t Colony::getSize() const {
    return this->size;
}

double **Colony::getPheramonesMatrix() {
    return this->pheramones;
}

void Colony::iteration(int startVertex, int iter) {
    auto agent = new Agent(this->size, COMMON);
    this->agents.push_back(agent);

    agent->setPassed(startVertex);
    agent->addVertexToAnswer(startVertex);

    for (int i = 0; i < size - 1; ++i) {
        int curVertex = agent->getLastVertex();
        int vertexTo = this->nextVertice(curVertex, agent);
        agent->addCost(matrix[curVertex][vertexTo]);
        agent->setPassed(vertexTo);
        agent->addVertexToAnswer(vertexTo);
        this->pheramones[curVertex][vertexTo] += getNewPheramonLevel(agent->getCurCost());
    }
    agent->addCost(matrix[agent->getLastVertex()][startVertex]);
    dryPheramone();

//    if (iter % 10 == 0)
//        makeFrame(iter);

//    if (iter % 1000 == 0) {
//        cout << agent->getCurCost() << endl;
//    }


    if (agent->getCurCost() < answerCost) {
//        if (agent->getCurCost() < 35.5) {
//            for (int i = 0; i < size; ++i) {
//                matrix[agent->answer[i]][agent->answer[(i + 1) % size]] += getNewPheramonLevel(agent->getCurCost());
//            }
//        }
        answerCost = agent->getCurCost();
        copy(agent->answer.begin(), agent->answer.end(), answer.begin());
        cout << "New ans is : " << answerCost << endl;
        print(answer, size);
    }
}

void Colony::dryPheramone() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            this->pheramones[i][j] *= this->evaporationRate;
        }
    }
}

string Colony::exportFinalResult() {
    string s;
    s += to_string(size) + '\n';
    for (int i = 0; i < size; ++i) {
        s += to_string(points[i]->id) + ' ' + to_string(points[i]->x) + ' ' + to_string(points[i]->y) + '\n';
    }
    for (int i = 0; i < size; ++i) {
        s += to_string(answer[i]) + ' ';
    }
    s += '\n';
    return s;
}

void Colony::drawGraph() {
    ofstream output(path + "tmp/graph");
    output << exportFinalResult();
    output.close();
    string command = "python3.8 ";
    command += path + "scripts/painter.py < ";
    command += path + "tmp/graph";
    system(command.c_str());
}

string Colony::exportFrame(int iteration) {
    string s;
    s += to_string(iteration) + " " + to_string(size) + '\n';
    for (int i = 0; i < size; ++i) {
        s += to_string(points[i]->id) + ' ' + to_string(points[i]->x) + ' ' + to_string(points[i]->y) + '\n';
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            s += to_string(pheramones[i][j]) + ' ';
        }
        s += '\n';
    }
    for (int i = 0; i < size; ++i) {
        s += to_string(answer[i]) + ' ';
    }
    s += '\n';
    return s;
}

void Colony::makeFrame(int iteration) {
    ofstream output(path + "tmp/frame");
    output << exportFrame(iteration);
    output.close();
    string command = "python3.8 ";
    command += path + "scripts/frame_painter.py < ";
    command += path + "tmp/frame";
    system(command.c_str());
}

void Colony::makeVideo() {
    string command = "python3.8 ";
    command += path + "scripts/movie_maker.py";
    system(command.c_str());
}

Agent::Agent(int64_t graphSize, int64_t type1) {
    this->currentCost = 0;
    this->type = type1;
    this->isPassed = new bool[graphSize];
}

void Agent::setPassed(int64_t vertex) const {
    this->isPassed[vertex] = true;
}

void Agent::addVertexToAnswer(int64_t vertex) {
    this->answer.push_back(vertex);
}

int Agent::getLastVertex() {
    return this->answer.back();
}

void Agent::addCost(double cost) {
    this->currentCost += cost;
}

double Agent::getCurCost() {
    return this->currentCost;
}
