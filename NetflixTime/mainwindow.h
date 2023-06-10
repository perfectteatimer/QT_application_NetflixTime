#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "informationappwindow.h"
#include "data.h"
#include "editdata.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_dataButton_clicked();
    void on_infoButton_clicked();
    void on_editDataButton_clicked();

    void on_actionView_logo_triggered();
    void on_actionDownload_CSV_triggered();

protected:
    bool eventFilter(QObject* obj, QEvent* event); // Added eventFilter declaration

private:
    Ui::MainWindow *ui;
    informationAppWindow *aboutWindow;
    Data *dataWindow;
    EditData *editDataWindow;
    Content* model;
};

#endif // MAINWINDOW_H
