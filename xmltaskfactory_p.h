#ifndef XMLTASKFACTORY_P_H
#define XMLTASKFACTORY_P_H

#include <QXmlQuery>
#include <QList>
#include <QStateMachine>
#include <QState>
#include <QXmlName>

class Task;

class XmlTaskFactoryPrivate
{
public:
    XmlTaskFactoryPrivate() : query(), tasks(), currentTask(0), sm() {}

    QXmlQuery query;
    QList<Task*> tasks;
    Task* currentTask;
    QStateMachine sm;
    QXmlName currentElementName;
};

#endif // XMLTASKFACTORY_P_H
