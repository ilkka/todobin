#ifndef XMLTASKFACTORY_P_H
#define XMLTASKFACTORY_P_H

#include <QXmlQuery>
#include <QList>
#include <QStateMachine>
#include <QState>
#include <QString>
#include <QXmlName>

class Task;

class XmlTaskFactoryPrivate
{
public:
    XmlTaskFactoryPrivate() : currentTask(0) {}

    QXmlQuery query;
    Task* currentTask;
    QStateMachine sm;
    QString lastTextNodeContents;
    QXmlName currentElementName;
};

#endif // XMLTASKFACTORY_P_H
