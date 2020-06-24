#include <random>
#include "gc.h"
#include <iostream>

#define MAX_ITERATIONS 10000
#define REMOVAL_RATE 0.46

class ListNode;

int list_size = 0;
gc::static_ptr<ListNode>* _start_ptr = nullptr;


struct ListNode : public gc::object
{
    gc::field<ListNode> _back;
    gc::field<ListNode> _fwd;
    END_GC_FIELDS;

    int _id;
    inline static int _next_id;

    ListNode():
        _back(nullptr),
        _fwd(nullptr),
        _id(ListNode::_next_id++)
    {
    }

  ;  void addAfter(gc::static_ptr<ListNode> back)
    {
        _back = back;
        _fwd = back->_fwd;
        back->_fwd = this;
    }

    void unlink()
    {
        if (_back != nullptr)
        {
            _back->_fwd = _fwd;
        }
        else
        {
            *_start_ptr = _fwd;
        }

        if (_fwd != nullptr) _fwd->_back = _back;
    }
};

void add_node();
void remove_node();

double fRandom()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(0.0, 1.0);

    return dis(gen);
}

int main()
{
    gc::init(4096, 25);
    gc::static_ptr<ListNode> _local_start_ptr;
    _start_ptr = &_local_start_ptr;

    ListNode::_next_id = 0;
    *_start_ptr = new ListNode();
    list_size++;

    for (int i = 0; i < 200; i++)
    {
        std::cout << "list_size:" << list_size << std::endl;
        add_node();
    }

    for (int i = 0; i < MAX_ITERATIONS; i++)
    {
        std::cout << "list_size:" << list_size << std::endl;
        if (fRandom() < REMOVAL_RATE)
        {
            add_node();
        }
        else
        {
            remove_node();
        }
    }
}

void add_node()
{
    int position = fRandom() * list_size;
    std::cout << "Adding to position " << position << " of " << list_size << std::endl;

    gc::static_ptr<ListNode> node = *_start_ptr;

    for(unsigned int i = 0; i < position; i++)
    {
        node = node->_fwd;
    }

    gc::static_ptr<ListNode> new_node = new ListNode();
    new_node->addAfter(node);

    list_size++;
}

void remove_node()
{
    int position = fRandom() * list_size;
    std::cout << "Removing from position " << position << " of " << list_size << std::endl;

    gc::static_ptr<ListNode> node = *_start_ptr;
    for(unsigned int i = 0; i < position; i++)
    {
        node = node->_fwd;
    }

    node->unlink();

    list_size--;
}
