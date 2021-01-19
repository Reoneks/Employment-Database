#ifndef PRIVATEOFFICE_H
#define PRIVATEOFFICE_H
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <regex>
#include "addpreviousjob.h"
#include "addplaceoflearning.h"
namespace Ui {
class PrivateOffice;
}
class PrivateOffice : public QMainWindow{
    Q_OBJECT
    void StartEditing();
    QString CompanyName,JobSeekerEmail;
    bool LogOut;
    QMessageBox *msgBox;
    AddPreviousJob *PreviousJobW;
    AddPlaceOfLearning *Learning;
    bool Validation(QString WhatValidate,QString ValidationRule);
    void ErrorMessage(QString Error);
    public:
        explicit PrivateOffice(QWidget *parent = nullptr);
        void SetJobSeekerData(QString JobSeeker,QString Email,QString Telephone,QString Text,QByteArray Photo);
        void SetCompanyData(QString Company,QString Email,QString Telephone,QString Site,QString Text,QByteArray Logo);
        bool GetLogOut();
        void OnlyRead(QString CompanyOrJobSeeker="");
        void SetUserAdditionalData(QString Education,QVector<QVector<QString>> Data,QVector<QVector<QString>> Data1);
        ~PrivateOffice();
    private slots:
        void on_Ok_clicked();
        void on_Cancel_clicked();
        void on_Edit_clicked();
        void on_Ok_2_clicked();
        void InsertDataInTable();
        void InsertDataInTable_1();
        void on_Cancel_2_clicked();
        void on_LoadNewAvatar_2_clicked();
        void on_LoadNewAvatar_clicked();
        void on_NextPage_clicked();
        void on_AddNewJob_clicked();
        void on_AddNewEduc_clicked();
    private:
        Ui::PrivateOffice *ui;
};
#endif // PRIVATEOFFICE_H
