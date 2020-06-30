#ifndef APPLICATION_H
#define APPLICATION_H

#include "gc.h"

class ListNode;

struct Application : public gc::object
{
    gc::field<ListNode> _start_ptr;
    END_GC_FIELDS;

    int _list_size;
    Application();

    void add_node();
    void remove_node();
};

#endif
