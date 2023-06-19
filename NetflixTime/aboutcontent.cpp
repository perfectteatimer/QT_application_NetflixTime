#include "aboutcontent.h"
#include "QtWidgets/qboxlayout.h"
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

    QVBoxLayout* layout = new QVBoxLayout(this);

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

    int row = myTable->selectionModel()->selectedIndexes().first().row();
    idLabel->setText("ID: " + modelForAboutContent->data(modelForAboutContent->index(row, 0), Qt::DisplayRole).toString());
    typeLabel->setText("Type: "+ modelForAboutContent->data(modelForAboutContent->index(row, 1), Qt::DisplayRole).toString());
    titleLabel->setText("Title: " + modelForAboutContent->data(modelForAboutContent->index(row, 2), Qt::DisplayRole).toString());
    directorleLabel->setText("Director: " + modelForAboutContent->data(modelForAboutContent->index(row, 3), Qt::DisplayRole).toString());
    castLabel->setText("Cast: " + modelForAboutContent->data(modelForAboutContent->index(row, 4), Qt::DisplayRole).toString());
    countryLabel->setText("Country: " + modelForAboutContent->data(modelForAboutContent->index(row, 5), Qt::DisplayRole).toString());
    dateAddedLabel->setText("Date added: " + modelForAboutContent->data(modelForAboutContent->index(row, 6), Qt::DisplayRole).toString());
    yearLabel->setText("Year: " + modelForAboutContent->data(modelForAboutContent->index(row, 7), Qt::DisplayRole).toString());
    ratingLabel->setText("Rating: " + modelForAboutContent->data(modelForAboutContent->index(row, 8), Qt::DisplayRole).toString());
    durationLabel->setText("Duration: "+ modelForAboutContent->data(modelForAboutContent->index(row, 9), Qt::DisplayRole).toString());
    genreLabel->setText("Genre: " + modelForAboutContent->data(modelForAboutContent->index(row, 10), Qt::DisplayRole).toString());
    descriptionTextEdit->setPlainText("Description: "+ modelForAboutContent->data(modelForAboutContent->index(row, 11), Qt::DisplayRole).toString());

    layout->addWidget(idLabel);
    layout->addWidget(typeLabel);
    layout->addWidget(titleLabel);
    layout->addWidget(directorleLabel);
    layout->addWidget(castLabel);
    layout->addWidget(countryLabel);
    layout->addWidget(dateAddedLabel);
    layout->addWidget(yearLabel);
    layout->addWidget(ratingLabel);
    layout->addWidget(durationLabel);
    layout->addWidget(genreLabel);
    layout->addWidget(descriptionTextEdit);

    descriptionTextEdit->setReadOnly(true);

    // Set dialog size
    resize(200, 200);
}

AboutContent::~AboutContent()
{
    delete ui;
}
