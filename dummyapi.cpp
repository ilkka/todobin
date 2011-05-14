#include "dummyapi.h"

DummyApi::DummyApi(bool requireFakeAuth, QObject *parent) :
    QObject(parent), m_requireFakeAuth(requireFakeAuth), m_fakedata("qml/RTMApp/dummydata/all_tasks_response.xml")
{
}
