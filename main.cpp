#include <iostream>
#include <random>

#include "Colony.h"


static const std::string test_path = "/home/toliman/Projects/Algorithms-AntColony/test_cases/";

void test001() {

    int vertexCount = 12;
    random_device gen;
    Colony c(vertexCount, CSV, .7, .7, 0.95, 1, test_path + "test001");
    for (int i = 0; i < 1e7; ++i) {
        c.iteration(gen() % vertexCount, i);
    }

//    Colony::printm(c.getMatrix(), c.getSize());
    Colony::printm(c.getPheramonesMatrix(), c.getSize());
//    std::cout<<c.exportFinalResult();
//    Colony::makeVideo();
    c.makeFrame(0);
    c.drawGraph();
}

void test002() {
    int vertexCount = 50;
    random_device gen;
    Colony c(vertexCount, CSV, .5, .5, 1, 1, test_path + "test002");
    for (int i = 0; i < 1000; ++i) {
        c.iteration(gen() % vertexCount, i);
    }
    c.makeFrame(0);
    c.drawGraph();
}

void test003() {
    int vertexCount = 100;
    random_device gen;
    Colony c(vertexCount, CSV, 90, 90, 0.9, 10, test_path + "test003");
    for (int i = 0; i < 10000000; ++i) {
        c.iteration(gen() % vertexCount, i);
    }
//    Colony::printm(c.getPheramonesMatrix(), c.getSize());

    c.makeFrame(0);
    c.drawGraph();
}

signed main() {
    cout.precision(4);


    test003();


    return 0;
}