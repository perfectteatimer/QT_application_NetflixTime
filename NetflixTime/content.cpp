#include "content.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QMessageBox>

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
        data.dateAdded = values[6];
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

bool Content::removeRow(int row, const QModelIndex &parent)
{
    if (row < 0 || row >= listWithAllData.size())
        return false;

    beginRemoveRows(parent, row, row);
    listWithAllData.removeAt(row);
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


//void Content::sortByDateAdded()
//{
//    std::sort(listWithAllData.begin(), listWithAllData.end(), [](const TableData& a, const TableData& b) {
//        return a.dateAdded < b.dateAdded;
//    });

//    emit dataChanged(createIndex(0, 0), createIndex(rowCount() - 1, columnCount() - 1));
//}

void Content::sortByYear()
{
    std::sort(listWithAllData.begin(), listWithAllData.end(), [](const TableData& a, const TableData& b) {
        return a.year < b.year;
    });

    emit dataChanged(createIndex(0, 0), createIndex(rowCount() - 1, columnCount() - 1));
}

//void Content::sortByRating()
//{
//    std::sort(listWithAllData.begin(), listWithAllData.end(), [](const TableData& a, const TableData& b) {
//        return a.rating < b.rating;
//    });

//    emit dataChanged(createIndex(0, 0), createIndex(rowCount() - 1, columnCount() - 1));
//}

//void Content::sortByDuration()
//{
//    std::sort(listWithAllData.begin(), listWithAllData.end(), [](const TableData& a, const TableData& b) {
//        return a.year < b.year;
//    });

//    emit dataChanged(createIndex(0, 0), createIndex(rowCount() - 1, columnCount() - 1));
//}



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
            << data.country << data.dateAdded
            << QString::number(data.year) << data.rating
            << data.duration << data.genre
            << data.description;
        stream << row.join(";") << "\n";
    }

    file.close();
    QMessageBox::information(nullptr, "Export done", "Data exported to CSV file.");

}


