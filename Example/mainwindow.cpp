#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui = new QDeclarativeView;
    ui->setSource(QUrl("qrc:/main.qml"));
    setCentralWidget(ui);
    ui->setResizeMode(QDeclarativeView::SizeRootObjectToView);
    Root = ui->rootObject();
    ui->rootContext()->setContextProperty("window", this);
}
void MainWindow::functionC(){
    QObject* textinput = Root->findChild<QObject*>("textinput");
    QObject* memo = Root->findChild<QObject*>("memo");
    QString str;
    str = (textinput->property("text")).toString();
    int a;
    a = str.toInt();
    a++;
    QString str2;
    str2 = QString::number(a);
    memo->setProperty("text", str+"+1="+str2);
}

MainWindow::~MainWindow()
{
    delete ui;
}
