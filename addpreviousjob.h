#ifndef ADDPREVIOUSJOB_H
#define ADDPREVIOUSJOB_H
#include <QMainWindow>
#include <regex>
#include <QMessageBox>
#include <QPushButton>
namespace Ui {
class AddPreviousJob;
}
class AddPreviousJob : public QMainWindow{
    Q_OBJECT
    QString DateS,DateE,Company,Job,Place,Text;
    bool Validation(QString WhatValidate,QString ValidationRule);
    void ErrorMessage(QString Error);
    void SetData();
    public:
        explicit AddPreviousJob(QWidget *parent = nullptr);
        QVector<QString> GetData();
        ~AddPreviousJob();
    private slots:
        void on_buttonBox_accepted();
        void on_buttonBox_rejected();
    signals:
         void Accessed();
    private:
        Ui::AddPreviousJob *ui;
};
#endif // ADDPREVIOUSJOB_H
