#include "database.h"
Database::Database(){
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName("Employment_DB.sqlite");
    Error=false;
    if (!sdb.open()) {
        DatabaseIsOpened=false;
        ErrorMessage("Помилка. Неможливо відкрити базу даних. Зв'яжіться з розробником.");
    }else DatabaseIsOpened=true;
}
QVector<QVector<QString>> Database::SelectRequest(QString request,int columns){
    QVector<QVector<QString>> ResultOfRequest;
    if(DatabaseIsOpened){
        QSqlQuery query;
        query.prepare(request);
        if(!query.exec())ErrorMessage("Помилка вилучення даних: "+query.lastError().text());
        else{
            while(query.next()){
                QVector<QString> Temp;
                for(int i=0;i<columns;++i){
                    Temp<<query.value(i).toString();
                }
                ResultOfRequest<<Temp;
            }
        }
    }
    return ResultOfRequest;
}
bool Database::ReturnError(){
    return Error;
}
void Database::RequestForDatabase(QString request){
    QSqlQuery query;
    query.prepare(request);
    if(!query.exec()){
        ErrorMessage("Помилка додавання/оновлення даних: "+query.lastError().text());
        Error=true;
    }
}
Database::~Database(){
    QString qs;
    {
        qs.append(QSqlDatabase::database().connectionName());
    }
    QSqlDatabase::removeDatabase(qs);
}
void Database::ImageAddRequest(QByteArray array,QString Table,QString ColumnName,QString AdditionalConditions){
    QSqlQuery query;
    query.prepare("UPDATE ["+Table+"] "
                  "SET ["+ColumnName+"] = :imageData"+AdditionalConditions);
    query.bindValue(":imageData",array);
    if(!query.exec())ErrorMessage("Помилка додавання картинки в таблицю: "+query.lastError().text());
}
QByteArray Database::ReturnImage(QString Table, QString ColumnName, QString AdditionalConditions){
    QSqlQuery query;
    query.prepare("SELECT ["+ColumnName+"] "
                  "FROM ["+Table+"]"+AdditionalConditions);
    if(!query.exec())ErrorMessage("Помилка вилучення картинки з таблиці: "+query.lastError().text());
    query.next();
    QByteArray b=query.value(0).toByteArray();
    return b;
}
void Database::ErrorMessage(QString Error){
    msgBox=new QMessageBox();
    msgBox->setText(Error);
    msgBox->setWindowIcon(QIcon(":/image/images/Error.ico"));
    msgBox->setWindowTitle("Помилка");
    msgBox->show();
}
