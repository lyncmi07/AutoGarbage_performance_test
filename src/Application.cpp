#include "Application.h"
#include "ListNode.h"

double fRandom();

Application::Application():
    _start_ptr(new ListNode(this)),
    _list_size(0)
{
}

void Application::add_node()
{
    int position = fRandom() * _list_size;
    std::cout << "Adding to position " << position << " of " << _list_size << std::endl;
    
    gc::static_ptr<ListNode> node(_start_ptr);
    
    for(unsigned int i = 0; i < position; i++)
    {
        node = node->_fwd;
    }
    
    gc::static_ptr<ListNode> new_node = new ListNode(this);
    new_node->addAfter(node);
    
    _list_size++;
}

void Application::remove_node()
{
    int position = fRandom() * _list_size;
    std::cout << "Removing from position " << position << " of " << _list_size << std::endl;
    
    gc::static_ptr<ListNode> node(_start_ptr);
    for(unsigned int i = 0; i < position; i++)
    {
        node = node->_fwd;
    }
    
    node->unlink();
    
    _list_size--;
}
