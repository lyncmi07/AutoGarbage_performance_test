#ifndef LIST_NODE_H
#define LIST_NODE_H

#include "gc.h"

class Application;

struct ListNode : public gc::object
{
    gc::field<ListNode> _back;
    gc::field<ListNode> _fwd;
    gc::field<Application> _app;
    END_GC_FIELDS;

    int _id;
    inline static int _next_id = 0;

    ListNode(gc::static_ptr<Application> app);

    void addAfter(gc::static_ptr<ListNode> back);
    void unlink();
};


#endif
