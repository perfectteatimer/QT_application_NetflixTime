
#include "informationappwindow.h"
#include "ui_informationappwindow.h"

informationAppWindow::informationAppWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::informationAppWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Information");

    QString styleSheet = "background-color: black;";
    setStyleSheet(styleSheet);

    QString buttonStyleSheet = "QPushButton { background-color: olive; }";
    ui->backToMainwindow->setStyleSheet(buttonStyleSheet);
}

informationAppWindow::~informationAppWindow()
{
    delete ui;
}

void informationAppWindow::on_backToMainwindow_clicked()
{
    this->close();
    emit firstWindow();
}

