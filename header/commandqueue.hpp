#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <queue>

#include "header/command.hpp"

class Queue {
    public :
                                    Queue();
        void                        push(const Command& data);
        Command                     pop();
        bool                        isEmpty() const;

    private:
        std::queue<Command>         m_queue;

};
#endif
