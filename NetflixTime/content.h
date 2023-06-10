#ifndef CONTENT_H
#define CONTENT_H

#include <QAbstractTableModel>
#include <QList>


struct TableData {
    QString showID;
    QString type;
    QString title;
    QString director;
    QString cast;
    QString country;
    QString dateAdded;
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
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());
    bool addData(const TableData& data);
    bool updateData(const QModelIndex &index, const TableData& newData);

    void writeDataToCSV(const QString& filePath);

    QList<TableData> getListWithAllData() const;

    // Sorting functions:
//    void sortByDateAdded();
    void sortByYear();
//    void sortByRating();
//    void sortByDuration();



private:
    QList<TableData> listWithAllData;

};

#endif // CONTENT_H
