#include "ListNode.h"
#include "Application.h"

ListNode::ListNode(gc::static_ptr<Application> app):
    _back(nullptr),
    _fwd(nullptr),
    _app(app),
    _id(ListNode::_next_id++)
{
}

void ListNode::addAfter(gc::static_ptr<ListNode> back)
{
    _back = back;
    _fwd = _back->_fwd;

    _back->_fwd = this;
    if (_fwd != nullptr) _fwd->_back = this;
}

void ListNode::unlink()
{
    if (_back != nullptr)
    {
        _back->_fwd = _fwd;
    }
    else
    {
        _app->_start_ptr = _fwd;
    }

    if (_fwd != nullptr) _fwd->_back = _back;
}
