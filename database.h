#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql>
#include <QMessageBox>
class Database{
    bool DatabaseIsOpened;
    void ErrorMessage(QString Error);
    QMessageBox *msgBox;
    bool Error;
    public:
        Database();
        bool ReturnError();
        QVector<QVector<QString>> SelectRequest(QString request,int columns);
        void RequestForDatabase(QString request);
        void ImageAddRequest(QByteArray array,QString Table,QString ColumnName,QString AdditionalConditions="");
        QByteArray ReturnImage(QString Table,QString ColumnName,QString AdditionalConditions="");
        ~Database();
};
#endif // DATABASE_H
