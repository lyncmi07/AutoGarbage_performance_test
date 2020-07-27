#include <random>
#include <iostream>

#include "gc.h"
#include "Application.h"
#include "ScopedTimer.hpp"

#define MAX_ITERATIONS 1000000
#define LIST_APPROX_SIZE 2000

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
    scoped_timer::init_timers();
    gc::init(900000, 25);

    gc::static_ptr<Application> application = new Application();

    for (int i = 0; i < 200; i++)
    {
        std::cout << "_list_size:" << application->_list_size << std::endl;
        // gc::debug();
        application->add_node();
    }

    std::cout << "--RANDOMIZED--" << std::endl;

    {
	scoped_timer t(timer_group::AGC_PROGRAM);
        for (int i = 0; i < MAX_ITERATIONS; i++)
        {
	    scoped_timer t1(timer_group::AGC_LOOP);

	    double removal_rate = (double)(application->_list_size) / (LIST_APPROX_SIZE * 2);

            if (fRandom() > removal_rate)
            {
		scoped_timer t2(timer_group::AGC_NODE_ADD);
                application->add_node();
            }
            else
            {
		scoped_timer t2(timer_group::AGC_NODE_REMOVE);
                application->remove_node();
            }
        }
    }

    scoped_timer::print_info();
}

