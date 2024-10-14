#include "header/commandqueue.hpp"

Queue::Queue() : m_queue()
{

}

void Queue::push(const Command& data)
{
    m_queue.push(data);
}

Command Queue::pop()
{
    Command command;
    if(!isEmpty()) { command =  m_queue.front(); }
    else { command.action = CommandType::noAction; }
    m_queue.pop();
    return command;
}

bool Queue::isEmpty() const
{
    return m_queue.empty();
}

