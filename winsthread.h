#ifndef WINSTHREAD_H
#define WINSTHREAD_H

#include <QObject>

class WinsThread : public QObject
{
    Q_OBJECT
public:
    WinsThread(QObject *parent = NULL);
    ~WinsThread();
};

#endif // WINSTHREAD_H
