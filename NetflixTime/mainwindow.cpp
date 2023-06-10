#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>
#include <QPainter>
#include <QtGlobal>
#include <QEvent>
#include <QVBoxLayout>
#include <QTimer>
#include <QTime>
#include <QFileDialog>
#include <QMessageBox>

//#include "content.h"


//#include "content.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    model = new Content;
    model->loadCSV(":/resource/datasetNetflixForQt.csv");
    ui->setupUi(this);
    aboutWindow = new informationAppWindow();
    connect(aboutWindow, &informationAppWindow::firstWindow, this, &MainWindow::show);

    dataWindow = new Data(model);
    connect(dataWindow, &Data::secondWindow, this, &MainWindow::show);

    editDataWindow = new EditData(model);
    connect(editDataWindow, &EditData::thirdWindow, this, &MainWindow::show);

    QString styleSheet = "background-color: black;";
    setStyleSheet(styleSheet);
    QString buttonStyleSheet = "QPushButton { background-color: olive; }";
    ui->dataButton->setStyleSheet(buttonStyleSheet);
    ui->infoButton->setStyleSheet(buttonStyleSheet);
    ui->editDataButton->setStyleSheet(buttonStyleSheet);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dataButton_clicked()
{
    dataWindow->show();
    this->close();
}


void MainWindow::on_infoButton_clicked()
{
    aboutWindow->show();
    this->close();
}



void MainWindow::on_editDataButton_clicked()
{
    editDataWindow->show();
    this->close();
}



void MainWindow::on_actionView_logo_triggered()
{
    QDialog* logoDialog = new QDialog(this);
    logoDialog->setStyleSheet("background-color: black;");

    QLabel* logoLabel = new QLabel(logoDialog);
    logoLabel->setFixedSize(600, 600);
    logoLabel->setAlignment(Qt::AlignCenter);

    // Override the paintEvent of the QLabel to draw the logo
    logoLabel->setAttribute(Qt::WA_TranslucentBackground);
    logoLabel->setAttribute(Qt::WA_NoSystemBackground);
    logoLabel->installEventFilter(this);

    // Set the dialog properties
    logoDialog->setWindowTitle("NetflixTime Logo");
    logoDialog->setFixedSize(600, 600);

    // Create a layout and add the label to it
    QVBoxLayout* layout = new QVBoxLayout(logoDialog);
    layout->addWidget(logoLabel);

    // Set the layout for the dialog
    logoDialog->setLayout(layout);

    // Start a timer to update the dots' positions every 100 milliseconds
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, logoLabel, [logoLabel]() {
        logoLabel->update();
    });
    timer->start(100);

    // Show the dialog
    logoDialog->exec();
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::Paint)
    {
        QLabel* label = qobject_cast<QLabel*>(obj);
        if (label)
        {
            QPainter painter(label);
            painter.setRenderHint(QPainter::Antialiasing);

            // Draw the background white dots
            QPen pen(Qt::white, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);  // Rounded dots
            painter.setPen(pen);

            // Adjust the dot density and movement speed
            int dotDensity = 20;  // Increase for fewer dots, decrease for more dots
            int dotSpeed = 100;  // Increase for slower movement, decrease for faster movement

            // Calculate the dot positions based on time
            int time = QTime::currentTime().msec() / dotSpeed;
            srand(time);
            for (int x = 0; x < label->width(); x += dotDensity)
            {
                for (int y = 0; y < label->height(); y += dotDensity)
                {
                    if (rand() % 5 == 0) // Randomly skip some dots for a more scattered effect
                        painter.drawPoint(x, y);
                }
            }

            // Set the font and color for the logo
            QFont font("Copperplate, Papyrus, fantasy", 90, QFont::Bold);
            painter.setFont(font);
            painter.setPen(Qt::red);

            // Draw the logo text
            QString logoText = "NetflixTime";
            QRectF logoRect(label->rect().x(), label->rect().y() + label->rect().height() * 0.2, label->rect().width(), label->rect().height() * 0.4);
            painter.drawText(logoRect, Qt::AlignAbsolute, logoText);

            // Set the font and color for the additional text
            QFont smallFont("Brush Script MT", 40);
            painter.setFont(smallFont);
            painter.setPen(Qt::white);

            // Draw the additional text
            QString additionalText = "It's time to enjoy...";
            QRectF textRect(label->rect().x(), label->rect().y() + label->rect().height() * 0.7, label->rect().width(), label->rect().height() * 0.3);
            painter.drawText(textRect, Qt::AlignCenter, additionalText);

            return true;
        }
    }
    return QObject::eventFilter(obj, event);
}

void MainWindow::on_actionDownload_CSV_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save CSV File"), "", tr("CSV Files (*.csv)"));

    // Check if a file is not empty
    if (!filePath.isEmpty())
    {
        model->writeDataToCSV(filePath);
        QMessageBox::information(this, "File Exported", "Data was exported succesfully");
    }
    else
        QMessageBox::information(this, "Error", "Data can not be exported");

}



