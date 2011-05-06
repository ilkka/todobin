#ifndef XMLTASKFACTORY_P_H
#define XMLTASKFACTORY_P_H

#include <QXmlQuery>
#include <QList>

class Task;

class XmlTaskFactoryPrivate
{
public:
    QXmlQuery query;
    QList<Task*> tasks;
};

#endif // XMLTASKFACTORY_P_H
