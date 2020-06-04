#ifndef GRAPHEXCEPTION_H
#define GRAPHEXCEPTION_H

#include <QException>

class GraphException : public QException
{
public:
    GraphException();
};

#endif // GRAPHEXCEPTION_H
