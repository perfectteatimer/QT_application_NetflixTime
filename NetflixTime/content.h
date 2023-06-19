#ifndef CONTENT_H
#define CONTENT_H

#include <QAbstractTableModel>
#include <QList>
#include <QDate>



struct TableData {
    QString showID;
    QString type;
    QString title;
    QString director;
    QString cast;
    QString country;
    QDate dateAdded;
    int year;
    QString rating;
    QString duration;
    QString genre;
    QString description;
};

class Content : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit Content(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool loadCSV(const QString& filePath);
    void clearData();

    // для защиты 20го июня
    bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

    bool addData(const TableData& data);
    bool updateData(const QModelIndex &index, const TableData& newData);

    void writeDataToCSV(const QString& filePath);

    QList<TableData> getListWithAllData() const;

    // Sorting functions:
    void sortByDateAdded(); //для защиты

    void sortByYear();
    void sortByRating();
    void sortByDuration();

    bool isValidDuration(const QString& duration) const;


private:
    QList<TableData> listWithAllData;

};

#endif // CONTENT_H
