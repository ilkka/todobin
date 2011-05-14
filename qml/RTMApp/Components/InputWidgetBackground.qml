import QtQuick 1.0

Rectangle {
    gradient: Gradient {
        GradientStop {
            position: 0.00;
            color: "#dedede";
        }
        GradientStop {
            position: 1.00;
            color: "#f0f0f0";
        }
    }

    border.color: "#555555"
    border.width: 1
    radius: 8
}

