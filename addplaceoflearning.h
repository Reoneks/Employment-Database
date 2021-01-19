#ifndef ADDPLACEOFLEARNING_H
#define ADDPLACEOFLEARNING_H
#include <QMainWindow>
#include <regex>
#include <QMessageBox>
#include <QPushButton>
namespace Ui {
class AddPlaceOfLearning;
}
class AddPlaceOfLearning : public QMainWindow{
    Q_OBJECT
    bool Validation(QString WhatValidate,QString ValidationRule);
    void ErrorMessage(QString Error);
    public:
        explicit AddPlaceOfLearning(QWidget *parent = nullptr);
        QVector<QString> GetData();
        ~AddPlaceOfLearning();
    signals:
        void Accessed();
    private slots:
        void on_buttonBox_accepted();
        void on_buttonBox_rejected();
    private:
        Ui::AddPlaceOfLearning *ui;
};
#endif // ADDPLACEOFLEARNING_H
