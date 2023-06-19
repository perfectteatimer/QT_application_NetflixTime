#include "mydialog.h"
#include "ui_mydialog.h"
#include <QPushButton>
#include "content.h"
#include <QDebug>
#include <QString>
#include <QComboBox>

MyDialog::MyDialog(QTableView *_myTable, Content *model, const QString& callingFunction, QWidget *parent):
    QDialog(parent),
    ui(new Ui::MyDialog),
    callingFunction(callingFunction)
{
    modelForMyDialog = model;
    myTable = _myTable;
    ui->setupUi(this);
    idLabel = new QLabel("ID:");
    idLineEdit = new QLineEdit;
    typeLabel = new QLabel("Type:");
    typeLineEdit = new QLineEdit;
    titleLabel = new QLabel("Title:");
    titleLineEdit = new QLineEdit;
    directorleLabel = new QLabel("Director:");
    directorLineEdit = new QLineEdit;
    castLabel = new QLabel("Cast:");
    castLineEdit = new QLineEdit;
    countryLabel = new QLabel("Country:");
    countryLineEdit = new QLineEdit;
    dateAddedLabel = new QLabel("Date added:");
    dateAddedDateEdit = new QDateEdit;
    yearLabel = new QLabel("Year:");
    yearLineEdit = new QLineEdit;
    ratingLabel = new QLabel("Rating:");
    ratingComboBox = new QComboBox; // Use QComboBox for rating selection
    durationLabel = new QLabel("Duration: (Your input should be only 'x min' or 'y Season/s' where x and y numbers)");
    durationLineEdit = new QLineEdit;
    genreLabel = new QLabel("Genre:");
    genreLineEdit = new QLineEdit;
    descriptionLabel = new QLabel("Description:");
    descriptionLineEdit = new QLineEdit;

    // Create a layout for the dialog
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(idLabel);
    layout->addWidget(idLineEdit);
    layout->addWidget(typeLabel);
    layout->addWidget(typeLineEdit);
    layout->addWidget(titleLabel);
    layout->addWidget(titleLineEdit);
    layout->addWidget(directorleLabel);
    layout->addWidget(directorLineEdit);
    layout->addWidget(castLabel);
    layout->addWidget(castLineEdit);
    layout->addWidget(countryLabel);
    layout->addWidget(countryLineEdit);
    layout->addWidget(dateAddedLabel);
    layout->addWidget(dateAddedDateEdit);
    layout->addWidget(yearLabel);
    layout->addWidget(yearLineEdit);
    layout->addWidget(ratingLabel);
    layout->addWidget(ratingComboBox);
    layout->addWidget(durationLabel);
    layout->addWidget(durationLineEdit);
    layout->addWidget(genreLabel);
    layout->addWidget(genreLineEdit);
    layout->addWidget(descriptionLabel);
    layout->addWidget(descriptionLineEdit);

    ui->verticalLayout->addLayout(layout);
    QString buttonStyleSheet2 = "QPushButton { background-color: green; }";
    ui->saveButton->setStyleSheet(buttonStyleSheet2);

    setStyleSheet("background-color: black;");
    if (callingFunction == "edit")
    {
        int row = myTable->selectionModel()->selectedIndexes().first().row();
        idLineEdit->setText(modelForMyDialog->data(modelForMyDialog->index(row, 0), Qt::DisplayRole).toString());
        typeLineEdit->setText(modelForMyDialog->data(modelForMyDialog->index(row, 1), Qt::DisplayRole).toString());
        titleLineEdit->setText(modelForMyDialog->data(modelForMyDialog->index(row, 2), Qt::DisplayRole).toString());
        directorLineEdit->setText(modelForMyDialog->data(modelForMyDialog->index(row, 3), Qt::DisplayRole).toString());
        castLineEdit->setText(modelForMyDialog->data(modelForMyDialog->index(row, 4), Qt::DisplayRole).toString());
        countryLineEdit->setText(modelForMyDialog->data(modelForMyDialog->index(row, 5), Qt::DisplayRole).toString());

        QString dateString = modelForMyDialog->data(modelForMyDialog->index(row, 6), Qt::DisplayRole).toString();
        QDate dateAdded = QDate::fromString(dateString, "yyyy-MM-dd");
        dateAddedDateEdit->setDate(dateAdded);

        yearLineEdit->setText(modelForMyDialog->data(modelForMyDialog->index(row, 7), Qt::DisplayRole).toString());

        // Set the current rating in the rating ComboBox
        QString currentRating = modelForMyDialog->data(modelForMyDialog->index(row, 8), Qt::DisplayRole).toString();

        ratingComboBox->setCurrentText(currentRating);

        durationLineEdit->setText(modelForMyDialog->data(modelForMyDialog->index(row, 9), Qt::DisplayRole).toString());
        genreLineEdit->setText(modelForMyDialog->data(modelForMyDialog->index(row, 10), Qt::DisplayRole).toString());
        descriptionLineEdit->setText(modelForMyDialog->data(modelForMyDialog->index(row, 11), Qt::DisplayRole).toString());
    }

    // Populate the ratingComboBox with options
    ratingComboBox->addItem("TV-Y");
    ratingComboBox->addItem("TV-PG");
    ratingComboBox->addItem("PG");
    ratingComboBox->addItem("PG-13");
    ratingComboBox->addItem("R");
    ratingComboBox->addItem("TV-MA");
    ratingComboBox->addItem("NR");
}


MyDialog::~MyDialog()
{
    delete ui;
}

void MyDialog::on_saveButton_clicked()
{
    TableData newData;
    newData.showID = idLineEdit->text();
    newData.type = typeLineEdit->text();
    newData.title = titleLineEdit->text();
    newData.director = directorLineEdit->text();
    newData.cast = castLineEdit->text();
    newData.country = countryLineEdit->text();

    // Get the selected date from the QDateEdit widget
    newData.dateAdded = dateAddedDateEdit->date();

    newData.year = yearLineEdit->text().toInt();
    newData.duration = durationLineEdit->text();
    newData.genre = genreLineEdit->text();
    newData.description = descriptionLineEdit->text();
    QString yearString = QString::number(newData.year);

    int intShowID = newData.showID.toInt();
    int intType = newData.type.toInt();
    int intTitle = newData.title.toInt();
    int intDirector = newData.director.toInt();
    int intCast = newData.cast.toInt();
    int intCountry = newData.country.toInt();
    int intDuration = newData.duration.toInt();
    int intGenre = newData.genre.toInt();
    int intDescription = newData.description.toInt();

    bool durationAns = Content().isValidDuration(newData.duration);

    if (callingFunction == "add")
    {
        // Check if any required fields are empty
        if (newData.showID.isEmpty() || newData.type.isEmpty() || newData.title.isEmpty() || newData.director.isEmpty() || newData.cast.isEmpty()
            || newData.country.isEmpty() || yearString.isEmpty() || newData.duration.isEmpty()
            || newData.genre.isEmpty() || newData.description.isEmpty())
        {
            QMessageBox messageBox(this);
            messageBox.setWindowTitle("Empty Fields");
            messageBox.setText("Please fill in all the required fields.");

            // Apply a style sheet to change the "OK" button color
            messageBox.setStyleSheet("QPushButton { background-color: green; }");
            messageBox.exec();
            return;
        }
        else if (intShowID != 0 || intTitle != 0 || intType != 0 || intDirector != 0 || intCast != 0 || intCountry != 0
         != 0 || intDirector != 0 || intDuration != 0 || intGenre != 0 || (yearString == "0" || yearString.length() != 4) || intDescription != 0 || durationAns == false)
        {
            QMessageBox messageBox(this);
            messageBox.setWindowTitle("Error fields");
            messageBox.setText("Everything except the 'Year' field should be a string. Also follow the example how to fill duration line. The 'Year' field should be an integer and valid year. Please change the input data.");
            // Apply a style sheet to change the "OK" button color
            messageBox.setStyleSheet("QPushButton { background-color: green; }");
            messageBox.exec();
            return;
        }
        else
        {
            // Set the current rating in the newData object
            newData.rating = ratingComboBox->currentText();

            // Check if the rating is selected
            if (newData.rating.isEmpty())
            {
                QMessageBox messageBox(this);
                messageBox.setWindowTitle("Empty Rating");
                messageBox.setText("Please select a rating from the list.");
                // Apply a style sheet to change the "OK" button color
                messageBox.setStyleSheet("QPushButton { background-color: green; }");
                messageBox.exec();
                return;
            }

            modelForMyDialog->addData(newData);
        }
    }
    if (callingFunction == "edit")
    {
        // Set the current rating in the newData object
        newData.rating = ratingComboBox->currentText();

        if (intShowID != 0 || intTitle != 0 || intType != 0 || intDirector != 0 || intCast != 0 || intCountry != 0
            || intDirector != 0 || intDuration != 0 || intGenre != 0 || (yearString == "0" || yearString.length() != 4) || intDescription != 0 || durationAns == false)
        {
            QMessageBox messageBox(this);
            messageBox.setWindowTitle("Error fields");
            messageBox.setText("Everything except the 'Year' field should be a string. The 'Year' field should be an integer and valid year. Also follow the example how to fill duration line. Please change the input data.");
            // Apply a style sheet to change the "OK" button color
            messageBox.setStyleSheet("QPushButton { background-color: green; }");
            messageBox.exec();
            return;
        }
        else
            modelForMyDialog->updateData(myTable->selectionModel()->selectedIndexes().first(), newData);
    }
    close();
}
