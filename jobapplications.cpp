#include "jobapplications.h"
#include "resume.h"
#include "ui_jobapplications.h"
JobApplications::JobApplications(QWidget *parent):QWidget(parent),ui(new Ui::JobApplications){
    ui->setupUi(this);
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Вакансії");
    ui->plainTextEdit->setReadOnly(true);
    ui->plainTextEdit_2->setReadOnly(true);
    ui->plainTextEdit_3->setReadOnly(true);
    ui->plainTextEdit_4->setReadOnly(true);
    ui->plainTextEdit_5->setReadOnly(true);
    ui->plainTextEdit_6->setReadOnly(true);
    ui->plainTextEdit_7->setReadOnly(true);
    ui->plainTextEdit_8->setReadOnly(true);
    ui->pushButton->setStyleSheet("#pushButton{border-image: url(:/image/images/Magnifier.png);} QToolTip{border: 2px solid darkkhaki; padding: 5px; border-radius: 1px;}");
    ui->DownloadDoc->setStyleSheet("#DownloadDoc{border-image: url(:/image/images/Document.png);} QToolTip{border: 2px solid darkkhaki; padding: 5px; border-radius: 1px;}");
    ui->pushButton->setDisabled(true);
    ui->DownloadDoc->setVisible(false);
}
void JobApplications::SetId(QString Id){
    ID=Id;
}
QString JobApplications::GetId(){
    return ID;
}
void JobApplications::SetFirstBlock(QString CompanyOrJobSeeker,QString Title){
    this->CompanyOrJobSeeker=CompanyOrJobSeeker;
    if(CompanyOrJobSeeker!="Здобувач:"){
        ui->pushButton->setVisible(false);
        ui->plainTextEdit_2->resize(221,31);
        Text1="Ваш лист:";
        Text2="Відповідь роботодавця:";
    }else{
        Text1="Лист здобувача:";
        Text2="Ваша відповідь:";
    }
    ui->plainTextEdit_6->setPlainText(Text1);
    ui->plainTextEdit_7->setPlainText(Text2);
    Title[0]=Title[0].toUpper();
    this->Title=Title;
    ui->plainTextEdit->setPlainText(CompanyOrJobSeeker);
    ui->plainTextEdit_2->setPlainText(Title);
}
void JobApplications::SetPosition(QString Position){
    this->Position=Position;
    ui->plainTextEdit_4->setPlainText(Position);
}
void JobApplications::SetMainText(QString MainText, QString MainText2){
    this->MainText=MainText;
    this->MainText2=MainText2;
    ui->plainTextEdit_5->setPlainText(MainText);
    ui->plainTextEdit_8->setPlainText(MainText2);
}
void JobApplications::SetInternalData(){
    ui->pushButton->setDisabled(false);
    ui->plainTextEdit->setPlainText(CompanyOrJobSeeker);
    if(CompanyOrJobSeeker!="Здобувач:"){
        ui->pushButton->setVisible(false);
        ui->plainTextEdit_2->resize(221,31);
    }else{
        ui->DownloadDoc->setVisible(true);
    }
    ui->plainTextEdit_2->setPlainText(Title);
    ui->plainTextEdit_4->setPlainText(Position);
    ui->plainTextEdit_5->setPlainText(MainText);
    ui->plainTextEdit_6->setPlainText(Text1);
    ui->plainTextEdit_7->setPlainText(Text2);
    ui->plainTextEdit_8->setPlainText(MainText2);
}
QVector<QString> JobApplications::GetData(QString Account){
    QVector<QString> Data;
    Data<<Account;
    Data<<Position;
    Data<<Title;
    return Data;
}
JobApplications::~JobApplications(){
    delete ui;
}
void JobApplications::on_pushButton_clicked(){
    emit OpenInfo();
}
void JobApplications::on_DownloadDoc_clicked(){
    Resume *resume=new Resume();
    resume->SetData(Job,Money,Text,FileData);
    resume->ReadOnly();
    resume->show();
}
void JobApplications::SetResumeData(QString Job, QString Money, QString Text, QByteArray FileData){
    this->Job=Job;
    this->Money=Money;
    this->Text=Text;
    this->FileData=FileData;
}
