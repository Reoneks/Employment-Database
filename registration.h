#ifndef REGISTRATION_H
#define REGISTRATION_H
#include <QMainWindow>
#include <QFileDialog>
#include <QButtonGroup>
#include "addpreviousjob.h"
#include "addplaceoflearning.h"
namespace Ui {
class Registration;
}
class Registration : public QMainWindow{
    Q_OBJECT
    int Mode;
    QString NewAccountName;
    QMessageBox *msgBox;
    AddPreviousJob *PreviousJobW;
    AddPlaceOfLearning *Learning;
    bool Validation(QString WhatValidate,QString ValidationRule);
    void ErrorMessage(QString Error);
    public:
        explicit Registration(QWidget *parent = nullptr);
        void SetMode(int Mode);
        QString GetAccountName();
        ~Registration();
    private slots:
            void on_OK_clicked();
            void on_Cancel_clicked();
            void on_LoadPhoto_clicked();
            void InsertDataInTable();
            void InsertDataInTable_1();
            void on_AddNewJob_clicked();
            void on_AddNewEduc_clicked();
    signals:
            void Finished();
            void NotFinished();
    private:
            Ui::Registration *ui;
};
#endif // REGISTRATION_H
