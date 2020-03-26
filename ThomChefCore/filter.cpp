#include "filter.h"

Filter::Filter()
{

}

void Filter::filterUpdated()
{
    emit updated();
}
