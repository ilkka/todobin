import QtQuick 1.0

Row {
    id: root
    Column {
        Text { text: "Day"; anchors.horizontalCenter: parent.horizontalCenter }
        Spinner {
            id: day
            minimumValue: 1
            maximumValue: {
                switch (month.value) {
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                    return 31
                case 2:
                    // ignoring leap years...
                    return 28
                }
                return 30
            }
        }
    }
    Column {
        Text { text: "Month"; anchors.horizontalCenter: parent.horizontalCenter }
        Spinner {
            id: month
            minimumValue: 1
            maximumValue: 12
        }
    }
    Column {
        Text { text: "Year"; anchors.horizontalCenter: parent.horizontalCenter }
        Spinner {
            id: year
            minimumValue: 1970
            maximumValue: 2011
        }
    }
}
