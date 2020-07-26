#include <random>
#include <iostream>

#include "gc.h"
#include "Application.h"

#define MAX_ITERATIONS 1000000
#define REMOVAL_RATE 0.51

double fRandom()
{
    static std::random_device rd;
    // static std::mt19937 gen(rd());
    static std::mt19937 gen(1);
    static std::uniform_real_distribution<> dis(0.0, 1.0);

    return dis(gen);
}

int main()
{
    gc::init(900000, 25);

    gc::static_ptr<Application> application = new Application();

    for (int i = 0; i < 200; i++)
    {
        std::cout << "_list_size:" << application->_list_size << std::endl;
        // gc::debug();
        application->add_node();
    }

    std::cout << "--RANDOMIZED--" << std::endl;

    for (int i = 0; i < MAX_ITERATIONS; i++)
    {
        std::cout << "_list_size:" << application->_list_size << std::endl;
        // gc::debug();
	gc::info();
        if (fRandom() < REMOVAL_RATE)
        {
            application->add_node();
        }
        else
        {
            application->remove_node();
        }
    }
}

