#include "data.h"
#include "ui_data.h"
#include "content.h"
#include <QSortFilterProxyModel>
#include <QMessageBox>
#include "aboutcontent.h"


Data::Data(Content* content, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Data)
{
    ui->setupUi(this);
    this->setWindowTitle("Data");
    modelForData = content;
    ui->tableView->setModel(modelForData);
    QString styleSheet = "background-color: black;";
    setStyleSheet(styleSheet);

    QString buttonStyleSheet = "QPushButton { background-color: olive; }";
    ui->mainPgBtn->setStyleSheet(buttonStyleSheet);

    QString buttonStyleSheet2 = "QPushButton { background-color: dark blue; }";
    ui->aboutPictureBtn->setStyleSheet(buttonStyleSheet2);


    // Connect the sort buttons' stateChanged signal to the corresponding slots
    connect(ui->sortByDateAdded, &QCheckBox::stateChanged, this, &Data::on_sortByDateAdded_stateChanged);
    connect(ui->sortByYear, &QCheckBox::stateChanged, this, &Data::on_sortByYear_stateChanged);
    connect(ui->sortByRating, &QCheckBox::stateChanged, this, &Data::on_sortByRating_stateChanged);
    connect(ui->sortByDuration, &QCheckBox::stateChanged, this, &Data::on_sortByDuration_stateChanged);
}

Data::~Data()
{
    delete ui;
}

void Data::on_mainPgBtn_clicked()
{
    this->close();
    emit secondWindow();
}

void Data::on_sortByDateAdded_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked)
        modelForData->sortByDateAdded();

}

void Data::on_sortByYear_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked)
        modelForData->sortByYear();
}

void Data::on_sortByRating_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked)
        modelForData->sortByRating();
}


void Data::on_sortByDuration_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked)
        modelForData->sortByDuration();

}

void Data::on_aboutPictureBtn_clicked()
{
    if (!ui->tableView->selectionModel()->hasSelection())
    {
        QMessageBox::warning(this, "No Selection", "Please select an item.");
        return;
    }
    else
    {
        AboutContent about(ui->tableView, modelForData);
        about.setWindowTitle("About picture");
        about.exec();
    }


}

