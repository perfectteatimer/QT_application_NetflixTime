#include "aboutcontent.h"
#include "ui_aboutcontent.h"

AboutContent::AboutContent(QTableView *_myTable, Content *model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutContent)
{
    QString styleSheet = "background-color: black;";
    setStyleSheet(styleSheet);
    modelForAboutContent = model;
    myTable = _myTable;
    ui->setupUi(this);
    idLabel = new QLabel(this);
    typeLabel = new QLabel(this);
    titleLabel = new QLabel(this);
    directorleLabel = new QLabel(this);
    castLabel = new QLabel(this);
    countryLabel = new QLabel(this);
    dateAddedLabel = new QLabel(this);
    yearLabel = new QLabel(this);
    ratingLabel = new QLabel(this);
    durationLabel = new QLabel(this);
    genreLabel = new QLabel(this);
    descriptionTextEdit = new QTextEdit(this);

    idLabel->setText("ID:");
    typeLabel->setText("Type:");
    titleLabel->setText("Title:");
    directorleLabel->setText("Director:");
    castLabel->setText("Cast:");
    countryLabel->setText("Country:");
    dateAddedLabel->setText("Date added:");
    yearLabel->setText("Year:");
    ratingLabel->setText("Rating:");
    durationLabel->setText("Duration:");
    genreLabel->setText("Genre:");

    int row = myTable->selectionModel()->selectedIndexes().first().row();
    idLabel->setGeometry(10, 10, 500, 30);
    typeLabel->setGeometry(10, 50, 500, 30);
    titleLabel->setGeometry(10, 90, 500, 30);
    directorleLabel->setGeometry(10, 130, 700, 30);
    castLabel->setGeometry(10, 170, 1000, 30);
    countryLabel->setGeometry(10, 210, 150, 30);
    dateAddedLabel->setGeometry(10, 250, 150, 30);
    yearLabel->setGeometry(10, 290, 150, 30);
    ratingLabel->setGeometry(10, 330, 150, 30);
    durationLabel->setGeometry(10, 370, 150, 30);
    genreLabel->setGeometry(10, 410, 150, 30);
    descriptionTextEdit->setGeometry(10, 450, 680, 200);
    descriptionTextEdit->setReadOnly(true);


    idLabel->setText(modelForAboutContent->data(modelForAboutContent->index(row, 0), Qt::DisplayRole).toString());
    typeLabel->setText(modelForAboutContent->data(modelForAboutContent->index(row, 1), Qt::DisplayRole).toString());
    titleLabel->setText(modelForAboutContent->data(modelForAboutContent->index(row, 2), Qt::DisplayRole).toString());
    directorleLabel->setText(modelForAboutContent->data(modelForAboutContent->index(row, 3), Qt::DisplayRole).toString());
    castLabel->setText(modelForAboutContent->data(modelForAboutContent->index(row, 4), Qt::DisplayRole).toString());
    countryLabel->setText(modelForAboutContent->data(modelForAboutContent->index(row, 5), Qt::DisplayRole).toString());
    dateAddedLabel->setText(modelForAboutContent->data(modelForAboutContent->index(row, 6), Qt::DisplayRole).toString());
    yearLabel->setText(modelForAboutContent->data(modelForAboutContent->index(row, 7), Qt::DisplayRole).toString());
    ratingLabel->setText(modelForAboutContent->data(modelForAboutContent->index(row, 8), Qt::DisplayRole).toString());
    durationLabel->setText(modelForAboutContent->data(modelForAboutContent->index(row, 9), Qt::DisplayRole).toString());
    genreLabel->setText(modelForAboutContent->data(modelForAboutContent->index(row, 10), Qt::DisplayRole).toString());
    descriptionTextEdit->setPlainText(modelForAboutContent->data(modelForAboutContent->index(row, 11), Qt::DisplayRole).toString());

    // Set dialog size to 700x700
    resize(700, 700);
}

AboutContent::~AboutContent()
{
    delete ui;
}

