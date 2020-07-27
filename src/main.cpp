#include <random>
#include <iostream>

#include "gc.h"
#include "Application.h"
#include "ScopedTimer.hpp"

#define MAX_ITERATIONS 1000000
#define SMALL_LIST_SIZE 2000
#define MEDIUM_LIST_SIZE 4500
#define LARGE_LIST_SIZE 9000

void modifyList(gc::static_ptr<Application> application, const int list_size, const timer_group list_version);

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

    //AutoGarbage Program
    {
	scoped_timer t(timer_group::AGC_PROGRAM);
	std::cout << "Starting small list" << std::endl;
	modifyList(application, SMALL_LIST_SIZE, AGC_LOOP_SMALL);
	std::cout << "GC after small list: ";
        gc::info();
	std::cout << "Starting medium list" << std::endl;
	modifyList(application, MEDIUM_LIST_SIZE, AGC_LOOP_MEDIUM);
	std::cout << "GC after medium list: ";
        gc::info();
	std::cout << "Starting large list" << std::endl;
	modifyList(application, LARGE_LIST_SIZE, AGC_LOOP_LARGE);
	std::cout << "GC after large list: ";
        gc::info();
    }

    scoped_timer::print_info();
    gc::info();
}

void modifyList(gc::static_ptr<Application> application, const int list_size, const timer_group list_version)
{

    for (int i = 0; i < MAX_ITERATIONS; i++)
    {
        scoped_timer t(list_version);

	double removal_rate = (double)(application->_list_size) / (list_size * 2);

        if (fRandom() > removal_rate)
        {
            application->add_node();
        }
        else
        {
            application->remove_node();
        }
    }
}

