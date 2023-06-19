 #include "content.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QMessageBox>
#include <QtAlgorithms>
#include <QDate>

#include <QDebug>


Content::Content(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant Content::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0: return "ID";
        case 1: return "Type";
        case 2: return "Title";
        case 3: return "Director";
        case 4: return "Cast";
        case 5: return "Country";
        case 6: return "Date Added";
        case 7: return "Year";
        case 8: return "Rating";
        case 9: return "Duration";
        case 10: return "Genre";
        case 11: return "Description";
        }
    }

    return QVariant();
}

int Content::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return listWithAllData.count();
}

int Content::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 12;
}

QVariant Content::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        const TableData &data = listWithAllData.at(index.row());
        switch (index.column())
        {
        case 0: return data.showID;
        case 1: return data.type;
        case 2: return data.title;
        case 3: return data.director;
        case 4: return data.cast;
        case 5: return data.country;
        case 6: return data.dateAdded;
        case 7: return data.year;
        case 8: return data.rating;
        case 9: return data.duration;
        case 10: return data.genre;
        case 11: return data.description;
        }
    }
    return QVariant();
}


bool Content::loadCSV(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file:" << file.errorString();
        return false;
    }

    clearData();

    QTextStream stream(&file);
    stream.readLine();

    while (!stream.atEnd())
    {
        QString line = stream.readLine();
        QStringList values = line.split(';');
        TableData data;
        data.showID = values[0];
        data.type = values[1];
        data.title = values[2];
        data.director = values[3];
        data.cast = values[4];
        data.country = values[5];
        data.dateAdded = QDate::fromString(values[6], "MMMM d, yyyy");
        data.year = values[7].toInt();
        data.rating = values[8];
        data.duration = values[9];
        data.genre = values[10];
        data.description = values[11];
        listWithAllData.append(data);
    }

    beginResetModel();
    endResetModel();

    return true;
}

void Content::clearData()
{
    listWithAllData.clear();
}



// переделал для защиты 20 июня
bool Content::removeRows(int row, int count, const QModelIndex& parent)
{
    Q_UNUSED(parent);

    if (row < 0 || count <= 0 || (row + count) > listWithAllData.size())
        return false;

    beginRemoveRows(QModelIndex(), row, row + count - 1);

    for (int i = 0; i < count; ++i)
    {
        listWithAllData.removeAt(row);
    }

    endRemoveRows();

    return true;
}

bool Content::addData(const TableData& data)
{
    int row = listWithAllData.size();

    beginInsertRows(QModelIndex(), row, row);
    listWithAllData.append(data);
    endInsertRows();

    return true;
}


void Content::sortByDateAdded()
{
    std::sort(listWithAllData.begin(), listWithAllData.end(), [](const TableData& a, const TableData& b) {
        return a.dateAdded < b.dateAdded;
    });

    emit dataChanged(createIndex(0, 0), createIndex(rowCount() - 1, columnCount() - 1));
}

void Content::sortByYear()
{
    std::sort(listWithAllData.begin(), listWithAllData.end(), [](const TableData& a, const TableData& b) {
        return a.year < b.year;
    });

    emit dataChanged(createIndex(0, 0), createIndex(rowCount() - 1, columnCount() - 1));
}

// для защиты сделал
void Content::sortByRating()
{
    std::sort(listWithAllData.begin(), listWithAllData.end(), [](const TableData& a, const TableData& b) {
        // Custom comparator function based on rating order
        QStringList ratingOrder = { "TV-Y", "TV-PG", "PG", "PG-13", "R", "TV-MA", "NR" };

        // Get the index of ratings in the custom order
        int indexA = ratingOrder.indexOf(a.rating);
        int indexB = ratingOrder.indexOf(b.rating);

        // Compare the ratings based on the index
        return indexA < indexB;
    });

    // Emit the dataChanged signal to notify the view about the sorted data
    emit dataChanged(createIndex(0, 0), createIndex(rowCount() - 1, columnCount() - 1));
}

void Content::sortByDuration()
{
    std::sort(listWithAllData.begin(), listWithAllData.end(), [](const TableData& a, const TableData& b) {
        QString durationA = a.duration;
        QString durationB = b.duration;

        // Extract the numeric values and units from durationA
        int valueA = durationA.split(" ").first().toInt();
        QString unitA = durationA.split(" ").last();

        // Extract the numeric values and units from durationB
        int valueB = durationB.split(" ").first().toInt();
        QString unitB = durationB.split(" ").last();

        // Handle the "min" unit
        if (unitA == "min" && unitB == "min")
            return valueA < valueB;

        // Handle the "Season" or "Seasons" unit
        if ((unitA == "Season" || unitA == "Seasons") && (unitB == "Season" || unitB == "Seasons"))
            return valueA < valueB;

        // Handle the case when one duration is in minutes and the other is in seasons
        if (unitA == "min")
            return true;

        return false;
    });

    emit dataChanged(createIndex(0, 0), createIndex(rowCount() - 1, columnCount() - 1));
}

bool Content::isValidDuration(const QString& duration) const
{
    // Duration format: "x min" or "x Seasons" or "1 Season"
    QStringList parts = duration.split(" ");
    if (parts.size() != 2)
        return false;

    QString value = parts[0];
    QString unit = parts[1];

    // Check if the value is a valid integer
    bool isValueInt;
    value.toInt(&isValueInt);
    if (!isValueInt)
        return false;

    // Check if the unit is "min" or "Season" or "Seasons"
    if (unit != "min" && unit != "Season" && unit != "Seasons")
        return false;

    return true;
}


bool Content::updateData(const QModelIndex& index, const TableData& newData)
{
    if (!index.isValid() || index.row() < 0 || index.row() >= listWithAllData.size())
        return false;

    listWithAllData[index.row()] = newData;
    emit dataChanged(index, index, { Qt::DisplayRole });

    return true;
}

QList<TableData> Content::getListWithAllData() const
{
    return listWithAllData;
}

void Content::writeDataToCSV(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(nullptr, "Error", "Failed to open file for adding");
        return;
    }

    QTextStream stream(&file);

    // Write the header line
    QStringList header;
    header << "ID" << "Type" << "Title" << "Director" << "Cast"
           << "Country" << "Date added" << "Year"
           << "Rating" << "Duration" << "Genre"
           << "Description";
    stream << header.join(";") << "\n";
    // Write the data rows
    for (const TableData& data: listWithAllData)
    {
        QStringList row;
        row << data.showID << data.type << data.title
            << data.director << data.cast
            << data.country << data.dateAdded.toString("MMMM d, yyyy")
            << QString::number(data.year) << data.rating
            << data.duration << data.genre
            << data.description;
        stream << row.join(";") << "\n";
    }

    file.close();
    QMessageBox::information(nullptr, "Export done", "Data exported to CSV file.");
}


