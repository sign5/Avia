#ifndef FILEFORMATEXCEPTION_H
#define FILEFORMATEXCEPTION_H

#include "exception/graphexception.h"
#include <QString>

class FileFormatException : public GraphException
{
protected:
    QString file_name;
    QString func_name;
public:
    FileFormatException(const QString file_name, const QString func_name);
    const QString getFileName() const;
    const QString getFuncName() const;
};

#endif // FILEFORMATEXCEPTION_H
