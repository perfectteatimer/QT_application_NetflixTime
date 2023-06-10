#ifndef MYDIALOG_H
#define MYDIALOG_H
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QString>
#include <QInputDialog>

#include <QDialog>

#include "content.h"
#include <QTableView>

namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QTableView *_myTable = nullptr, Content *model = nullptr, const QString& callingFunction = "",  QWidget *parent = nullptr);
    ~MyDialog();


//    void setIdLineEditText(const QString& text);
//    void setTypeLineEditText(const QString& text);
//    void setTitleLineEditText(const QString& text);
//    void setDirectorLineEditText(const QString& text);
//    void setCastLineEditText(const QString& text);
//    void setCountryLineEditText(const QString& text);
//    void setDateAddedLineEditText(const QString& text);
//    void setYearLineEditText(const int& text);
//    void setRatingLineEditText(const QString& text);
//    void setDurationLineEditText(const QString& text);
//    void setGenreLineEditText(const QString& text);
//    void setDescriptionLineEditText(const QString& text);

private slots:
    void on_saveButton_clicked();

    // Create labels and input fields for each data field
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
    QLineEdit* dateAddedLineEdit;
    QLabel* yearLabel;
    QLineEdit* yearLineEdit;
    QLabel* ratingLabel;
    QLineEdit* ratingLineEdit;
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
    QString callingFunction; // New member variable to store the calling function

};

#endif // MYDIALOG_H
