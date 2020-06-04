#ifndef NODNOTFOUND_H
#define NODNOTFOUND_H

#include "exception/graphexception.h"

class NodeNotFound : public GraphException
{
public:
    NodeNotFound();
};

#endif // NODNOTFOUND_H
