#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QString>
#include <QInputDialog>
#include <QDialog>
#include <QDate>
#include <QTableView>
#include <QDateEdit>
#include <QComboBox>


#include "content.h"

namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QTableView *_myTable = nullptr, Content *model = nullptr, const QString& callingFunction = "",  QWidget *parent = nullptr);
    ~MyDialog();

private slots:
    void on_saveButton_clicked();

private:
    QLabel* idLabel;
    QLineEdit* idLineEdit;
    QLabel* typeLabel;
    QLineEdit* typeLineEdit;
    QLabel* titleLabel;
    QLineEdit* titleLineEdit;
    QLabel* directorleLabel;
    QLineEdit* directorLineEdit;
    QLabel* castLabel;
    QLineEdit* castLineEdit;
    QLabel* countryLabel;
    QLineEdit* countryLineEdit;
    QLabel* dateAddedLabel;
    QDateEdit* dateAddedDateEdit;
    QLabel* yearLabel;
    QLineEdit* yearLineEdit;
    QLabel* ratingLabel;
    QComboBox* ratingComboBox;
    QLabel* durationLabel;
    QLineEdit* durationLineEdit;
    QLabel* genreLabel;
    QLineEdit* genreLineEdit;
    QLabel* descriptionLabel;
    QLineEdit* descriptionLineEdit;

private:
    Ui::MyDialog *ui;
    Content *modelForMyDialog;
    QTableView *myTable;
    QString callingFunction;
};

#endif // MYDIALOG_H
