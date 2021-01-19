#include "addpreviousjob.h"
#include "ui_addpreviousjob.h"
AddPreviousJob::AddPreviousJob(QWidget *parent):QMainWindow(parent),ui(new Ui::AddPreviousJob){
    ui->setupUi(this);
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Додати попередню роботу");
    QPalette pal;
    QPixmap map;
    map.load(":/image/images/HelpBackground.png");
    map=map.scaled(540,486,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pal.setBrush(ui->centralwidget->backgroundRole(),QBrush(map));
    ui->centralwidget->setPalette(pal);
    ui->centralwidget->setAutoFillBackground(true);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Ок");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Скасувати");
    ui->DateE->setTabChangesFocus(true);
    ui->DateS->setTabChangesFocus(true);
    ui->Job->setTabChangesFocus(true);
    ui->Text->setTabChangesFocus(true);
    ui->Place->setTabChangesFocus(true);
    ui->Company->setTabChangesFocus(true);
}
AddPreviousJob::~AddPreviousJob(){
    delete ui;
}
bool AddPreviousJob::Validation(QString WhatValidate,QString ValidationRule){
    const std::regex RegEx(ValidationRule.toStdString());
    return std::regex_search(WhatValidate.toStdString(),RegEx);
}
void AddPreviousJob::SetData(){
    DateS=ui->DateS->toPlainText();
    DateE=ui->DateE->toPlainText();
    Company=ui->Company->toPlainText();
    Job=ui->Job->toPlainText();
    Place=ui->Place->toPlainText();
    Text=ui->Text->toPlainText();
}
QVector<QString> AddPreviousJob::GetData(){
    QVector<QString> Result;
    Result<<DateS<<DateE<<Company<<Job<<Place<<Text;
    return Result;
}
void AddPreviousJob::ErrorMessage(QString Error){
    QMessageBox *msgBox=new QMessageBox();
    msgBox->setText(Error);
    msgBox->setWindowIcon(QIcon(":/image/images/Error.ico"));
    msgBox->setWindowTitle("Помилка");
    msgBox->show();
}
void AddPreviousJob::on_buttonBox_accepted(){
    bool ValidDate1,ValidDate2;
    ValidDate1=Validation(ui->DateS->toPlainText(),"^\\d{4}[./-]\\d{2}$");
    ValidDate2=Validation(ui->DateE->toPlainText(),"^\\d{4}[./-]\\d{2}$");
    if(ValidDate1&&ValidDate2){
        if(ui->Company->toPlainText()!=""){
            if(ui->Job->toPlainText()!=""){
                SetData();
                close();
                emit Accessed();
            }else ErrorMessage("Ви не ввели назву посади!!");
        }else ErrorMessage("Ви не ввели назву компанії!!");
    }else ErrorMessage("Неправильно введена одна з дат.\nПравильна форма написання дати: YYYY.MM .");
}
void AddPreviousJob::on_buttonBox_rejected(){
    close();
}
