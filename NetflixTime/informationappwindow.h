#ifndef INFORMATIONAPPWINDOW_H
#define INFORMATIONAPPWINDOW_H

#include <QDialog>
#include <QLabel>

namespace Ui {
class informationAppWindow;
}

class informationAppWindow : public QDialog
{
    Q_OBJECT

public:
    explicit informationAppWindow(QWidget *parent = nullptr);
    ~informationAppWindow();

signals:
    void firstWindow();

private slots:
    void on_backToMainwindow_clicked();


private:
    Ui::informationAppWindow *ui;


};

#endif // INFORMATIONAPPWINDOW_H
