#include "addvacancy.h"
#include "ui_addvacancy.h"
#include "database.h"
AddVacancy::AddVacancy(QWidget *parent):QMainWindow(parent),ui(new Ui::AddVacancy){
    ui->setupUi(this);
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Додати вакансію");
    ui->Money->setMinimum(1);
    ui->Money->setSuffix(" грн");
    ui->Money->setMaximum(1000000000);
    ui->textBrowser_2->setReadOnly(true);
    ui->textBrowser_3->setReadOnly(true);
    ui->textBrowser_4->setReadOnly(true);
    ui->textBrowser_5->setReadOnly(true);
    ui->textBrowser->setReadOnly(true);
    QPalette pal;
    QPixmap map;
    map.load(":/image/images/AddVacancy.png");
    map=map.scaled(479,670,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pal.setBrush(ui->centralwidget->backgroundRole(),QBrush(map));
    ui->centralwidget->setPalette(pal);
    ui->centralwidget->setAutoFillBackground(true);
}
void AddVacancy::ErrorMessage(QString Error){
    QMessageBox *msgBox=new QMessageBox();
    msgBox->setText(Error);
    msgBox->setWindowIcon(QIcon(":/image/images/Error.ico"));
    msgBox->setWindowTitle("Помилка");
    msgBox->show();
}
void AddVacancy::SetCompanyName(QString Name){
    CompanyName=Name;
}
void AddVacancy::ClearData(){
    ui->Money->setValue(0);
    ui->Vacancy->setText("");
    ui->Description->setText("");
    ui->Requirements->setText("");
}
AddVacancy::~AddVacancy(){
    delete ui;
}
void AddVacancy::on_Ok_clicked(){
    if(ui->Vacancy->text()!=""){
        Database *database=new Database();
        database->RequestForDatabase("INSERT INTO Вакансії (Посада,Зарплата,Опис,Вимоги,Компанія)"
                                     "VALUES (\""
                                     +ui->Vacancy->text()+"\",\""
                                     +QString::number(ui->Money->value())+"\",\""
                                     +ui->Description->toPlainText()+"\",\""
                                     +ui->Requirements->toPlainText()+"\",("
                                         "SELECT [ID] "
                                         "FROM [Компанія] "
                                         "WHERE [Компанія].[Назва компанії]=\""+CompanyName+"\""
                                     "))");
        delete database;
        close();
    }else ErrorMessage("Ви не ввели назву вакансії!!");
}
void AddVacancy::on_Cancel_clicked(){
    close();
}
