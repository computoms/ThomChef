#ifndef FILTER_H
#define FILTER_H

#include <QObject>
#include "recipe.h"

class Filter : public QObject
{
    Q_OBJECT
public:
    Filter();

    virtual bool isInFilter(const Recipe &recipe) const = 0;

protected:
    void filterUpdated();

signals:
    void updated();
};

#endif // FILTER_H
