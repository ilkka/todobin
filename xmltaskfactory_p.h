#ifndef XMLTASKFACTORY_P_H
#define XMLTASKFACTORY_P_H

#include <QXmlQuery>
#include <QList>

class Task;

class XmlTaskFactoryPrivate
{
public:
    XmlTaskFactoryPrivate() : query(), tasks(), currentTask(0) {}

    QXmlQuery query;
    QList<Task*> tasks;
    Task* currentTask;
};

#endif // XMLTASKFACTORY_P_H
