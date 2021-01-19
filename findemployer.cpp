#include "findemployer.h"
#include "ui_findemployer.h"
FindEmployer::FindEmployer(QWidget *parent):QWidget(parent),ui(new Ui::FindEmployer){
    ui->setupUi(this);
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Знайти роботодавця");
    ui->Salary->setReadOnly(true);
    ui->Company->setReadOnly(true);
    ui->Vacancy->setReadOnly(true);
    ui->Description->setReadOnly(true);
    ui->Requirements->setReadOnly(true);
    ui->textBrowser_2->setReadOnly(true);
    ui->textBrowser_3->setReadOnly(true);
    ui->textBrowser_4->setReadOnly(true);
    ui->textBrowser_5->setReadOnly(true);
    ui->textBrowser_6->setReadOnly(true);
    ui->pushButton->setStyleSheet("#pushButton{border-image: url(:/image/images/Magnifier.png);} QToolTip{border: 2px solid darkkhaki; padding: 5px; border-radius: 1px;}");
    ui->pushButton->setDisabled(true);
}
QString FindEmployer::GetID(){
    return ID;
}
void FindEmployer::SetID(QString ID){
    this->ID=ID;
}
void FindEmployer::SetData(QString Company, QString Requirements, QString Description, QString Vacancy, QString Salary){
    this->Salary=Salary;
    Company[0]=Company[0].toUpper();
    this->Company=Company;
    this->Vacancy=Vacancy;
    this->Description=Description;
    this->Requirements=Requirements;
    ui->Salary->setText(Salary+" грн");
    ui->Company->setText(Company);
    ui->Vacancy->setText(Vacancy);
    ui->Description->setPlainText(Description);
    ui->Requirements->setPlainText(Requirements);
}
void FindEmployer::SetInternalData(){
    ui->pushButton->setDisabled(false);
    ui->Salary->setText(Salary+" грн");
    ui->Company->setText(Company);
    ui->Vacancy->setText(Vacancy);
    ui->Description->setPlainText(Description);
    ui->Requirements->setPlainText(Requirements);
}
QVector<QString> FindEmployer::GetData(QString Account){
    QVector<QString>Data;
    Data<<Account;
    Data<<Vacancy;
    Data<<Company.toLower();
    return Data;
}
QVector<QString> FindEmployer::GetData(){
    QVector<QString>Data;
    Data<<ui->Salary->text().split(" ")[0]<<ui->Vacancy->text()<<ui->Description->toPlainText()<<ui->Requirements->toPlainText();
    return Data;
}
QString FindEmployer::GetVacancyName(){
    return ui->Company->text().toLower();
}
void FindEmployer::Employer(){
    ui->pushButton->setVisible(false);
    ui->Company->resize(171,31);
}
void FindEmployer::AllowEdit(){
    ui->pushButton->setVisible(false);
    ui->Company->resize(171,31);
    ui->Salary->setReadOnly(false);
    ui->Vacancy->setReadOnly(false);
    ui->Description->setReadOnly(false);
    ui->Requirements->setReadOnly(false);
}
FindEmployer::~FindEmployer(){
    delete ui;
}
void FindEmployer::on_pushButton_clicked(){
    emit OpenInfo();
}
