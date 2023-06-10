#ifndef DATA_H
#define DATA_H

#include <QDialog>
#include "content.h"


namespace Ui {
class Data;
}

class Data : public QDialog
{
    Q_OBJECT

public:
    explicit Data(Content* model = nullptr, QWidget *parent = nullptr);
    ~Data();

signals:
    void secondWindow();

private slots:
    void on_mainPgBtn_clicked();

    void on_sortByDateAdded_stateChanged(int arg1);

    void on_sortByYear_stateChanged(int arg1);

    void on_sortByRating_stateChanged(int arg1);

    void on_sortByDuration_stateChanged(int arg1);

    void on_aboutPictureBtn_clicked();

private:
    Ui::Data *ui;
    Content *modelForData;
};

#endif // DATA_H
