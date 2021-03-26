#ifndef COMMON_H
#define COMMON_H
#include <QString>

struct T_item
{
    int parentId;//max 2^64
    int id;
    int pos;//
    QString value;
};

#endif // COMMON_H
