import QtQuick 1.0

XmlListModel {
    source: "./all_tasks_response.xml"
    query: "/rsp/tasks/list/taskseries"

    XmlRole {
        name: "title"
        query: "@name/string()"
    }
}
