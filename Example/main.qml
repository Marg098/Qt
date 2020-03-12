import QtQuick 1.1

//Главное окно
Rectangle {
    width: 300
    height: 300
    anchors.fill:parent
    //Кнопка
    Rectangle {
        id: button
        x: parent.width / 2 - button.width / 2;
        y: parent.height / 2 - button.height / 2;
        //Размер, цвет, текст кнопки
        width:100
        height:30
        color:"blue"
        Text{
            id:buttonLabel
            text:"Пуск"
            anchors.centerIn: parent;
        }
        //Действие мыши
        MouseArea{
            anchors.fill: parent
            id: mouseArea
            onClicked: window.functionC()
        }

    }
    //Строка ввода
    Rectangle{
        id: textinputRect //Имя строки ввода
         x: parent.width / 2 - button.width / 2;
         y: parent.height / 2 - button.height / 2+40;
         //Размер строки ввода
         width:100
         height:18
         color:"gray"
         TextInput{
             id: textinput
             objectName: "textinput"
             color:"#151515";
             selectionColor: "blue"
             font.pixelSize:12;
             width:parent.width-4
             anchors.centerIn: parent
             focus: true
             text:"1"
         }
    }
    //Поле вывода
    Rectangle{
        id: memoRect
        x: parent.width / 2 - button.width / 2;
        y: parent.height / 2 - button.height / 2+70;
        width:100
        height:35
        color:"gray"
        TextEdit{
            id: memo
            objectName:"memo"
            wrapMode: TextEdit.Wrap
            width:parent.width;
            readOnly:true
        }
    }
}

