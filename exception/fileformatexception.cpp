#include "fileformatexception.h"

FileFormatException::FileFormatException(const QString file_name, const QString func_name) {
    this->file_name = file_name;
    this->func_name = func_name;
}

const QString FileFormatException::getFileName() const {
    return file_name;
}

const QString FileFormatException::getFuncName() const {
    return func_name;
}
