#include "addplaceoflearning.h"
#include "ui_addplaceoflearning.h"
AddPlaceOfLearning::AddPlaceOfLearning(QWidget *parent):QMainWindow(parent),ui(new Ui::AddPlaceOfLearning){
    ui->setupUi(this);
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Додати навчальний заклад");
    QPalette pal;
    QPixmap map;
    map.load(":/image/images/HelpBackground.png");
    map=map.scaled(539,195,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pal.setBrush(ui->centralwidget->backgroundRole(),QBrush(map));
    ui->centralwidget->setPalette(pal);
    ui->centralwidget->setAutoFillBackground(true);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Ок");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Скасувати");
    ui->DateE->setTabChangesFocus(true);
    ui->DateS->setTabChangesFocus(true);
    ui->School->setTabChangesFocus(true);
    ui->Qualification->setTabChangesFocus(true);
}
QVector<QString> AddPlaceOfLearning::GetData(){
    QVector<QString> Result;
    Result<<ui->DateS->toPlainText()<<ui->DateE->toPlainText()<<ui->School->toPlainText()<<ui->Qualification->toPlainText();
    return Result;
}
AddPlaceOfLearning::~AddPlaceOfLearning(){
    delete ui;
}
bool AddPlaceOfLearning::Validation(QString WhatValidate,QString ValidationRule){
    const std::regex RegEx(ValidationRule.toStdString());
    return std::regex_search(WhatValidate.toStdString(),RegEx);
}
void AddPlaceOfLearning::ErrorMessage(QString Error){
    QMessageBox *msgBox=new QMessageBox();
    msgBox->setText(Error);
    msgBox->setWindowIcon(QIcon(":/image/images/Error.ico"));
    msgBox->setWindowTitle("Помилка");
    msgBox->show();
}
void AddPlaceOfLearning::on_buttonBox_accepted(){
    bool ValidDate1,ValidDate2;
    ValidDate1=Validation(ui->DateS->toPlainText(),"^\\d{4}[./-]\\d{2}$");
    ValidDate2=Validation(ui->DateE->toPlainText(),"^\\d{4}[./-]\\d{2}$");
    if(ValidDate1&&ValidDate2){
        if(ui->School->toPlainText()!=""){
            close();
            emit Accessed();
        }else ErrorMessage("Ви не ввели назву навчального закладу!!");
    }else ErrorMessage("Неправильно введена одна з дат.\nПравильна форма написання дати: YYYY.MM .");
}
void AddPlaceOfLearning::on_buttonBox_rejected(){
    close();
}
