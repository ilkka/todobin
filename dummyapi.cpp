#include "dummyapi.h"

DummyApi::DummyApi(bool requireFakeAuth, QObject *parent) :
    QObject(parent), m_requireFakeAuth(requireFakeAuth), m_fakedata("qml/todobin/dummydata/all_tasks_response.xml")
{
}
