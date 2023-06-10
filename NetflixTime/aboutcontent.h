#ifndef ABOUTCONTENT_H
#define ABOUTCONTENT_H

#include "content.h"
#include <QDialog>
#include "content.h"
#include <QTableView>
#include <QLabel>
#include <QTextEdit>

namespace Ui {
class AboutContent;
}

class AboutContent : public QDialog
{
    Q_OBJECT

public:
    explicit AboutContent(QTableView *_myTable = nullptr, Content *model = nullptr, QWidget *parent = nullptr);
    ~AboutContent();

private slots:

private:
    Ui::AboutContent *ui;
    Content *modelForAboutContent;
    QTableView *myTable;

    QLabel* idLabel;
    QLabel* typeLabel;
    QLabel* titleLabel;
    QLabel* directorleLabel;
    QLabel* castLabel;
    QLabel* countryLabel;
    QLabel* dateAddedLabel;
    QLabel* yearLabel;
    QLabel* ratingLabel;
    QLabel* durationLabel;
    QLabel* genreLabel;
    QTextEdit* descriptionTextEdit;
};

#endif // ABOUTCONTENT_H
