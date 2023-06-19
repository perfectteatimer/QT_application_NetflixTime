#include "editdata.h"
#include "ui_editdata.h"
#include "content.h"
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QString>
#include <QInputDialog>
#include "QDebug"

#include <QModelIndexList>
#include <QSet>
#include <QList>
#include <algorithm>

#include "mydialog.h"


EditData::EditData(Content *content, QWidget *parent):
    QDialog(parent),
    ui(new Ui::EditData)
{
    ui->setupUi(this);
    this->setWindowTitle("Edit data");
    modelForEditData = content; // Initialize the Content model
    ui->tableView->setModel(modelForEditData);
    QString styleSheet = "background-color: black;";
    setStyleSheet(styleSheet);


    QString buttonStyleSheet = "QPushButton { background-color: red; }";
    ui->deleteContentBtn->setStyleSheet(buttonStyleSheet);

    QString buttonStyleSheet2 = "QPushButton { background-color: green; }";
    ui->addContentBtn->setStyleSheet(buttonStyleSheet2);

    QString buttonStyleSheet4 = "QPushButton { background-color: purple; }";
    ui->editContentBtn->setStyleSheet(buttonStyleSheet4);

    QString buttonStyleSheet5 = "QPushButton { background-color: olive; }";
    ui->backMainBtn->setStyleSheet(buttonStyleSheet5);

}


EditData::~EditData()
{
    delete ui;
}

void EditData::on_backMainBtn_clicked()
{
    this->close();
    emit thirdWindow();
}

void EditData::on_addContentBtn_clicked()
{
    MyDialog add(ui->tableView, modelForEditData, "add");
    add.setWindowTitle("Add content");
    add.exec();
}


void EditData::on_editContentBtn_clicked()
{
    if (!ui->tableView->selectionModel()->hasSelection())
    {
        QMessageBox::warning(this, "No Selection", "Please select an item to edit.");
        return;
    }
    else
    {
        MyDialog edit(ui->tableView, modelForEditData, "edit");
        edit.setWindowTitle("Edit content");
        edit.exec();
    }

}

// переделал для вторника 20го июня
void EditData::on_deleteContentBtn_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty())
    {
        return; // No items selected, nothing to delete
    }

    // Collect unique row indexes to delete
    QSet<int> rowsToDelete;
    for (const QModelIndex& index : selectedIndexes)
    {
        rowsToDelete.insert(index.row());
    }

    // Convert the set of row indexes to a list for deletion
    QList<int> rowsList(rowsToDelete.begin(), rowsToDelete.end());
    std::sort(rowsList.begin(), rowsList.end(), std::greater<int>()); // Sort in descending order

    // Remove rows from the model
    for (int row : rowsList)
    {
        modelForEditData->removeRow(row);
    }

    ui->tableView->update();
}










