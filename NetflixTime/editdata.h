#ifndef EDITDATA_H
#define EDITDATA_H

#include <QDialog>
#include "content.h"


namespace Ui {
class EditData;
}

class EditData : public QDialog
{
    Q_OBJECT

public:
    explicit EditData(Content* model = nullptr,QWidget *parent = nullptr);
    ~EditData();

signals:
    void thirdWindow();

private slots:
    void on_backMainBtn_clicked();
    void on_addContentBtn_clicked();
    void on_editContentBtn_clicked();
    void on_deleteContentBtn_clicked();


private:
    Ui::EditData *ui;
    Content *modelForEditData;
};

#endif // EDITDATA_H


