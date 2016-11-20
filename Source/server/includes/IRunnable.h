/*
** Created by Gaston Siffert
*/

#ifndef IRUNNABLE_H
#define IRUNNABLE_H

/*
** Interface used to describe a running process
*/
class IRunnable
{
public:
    virtual void run() = 0;
};

#endif //IRUNNABLE_H
