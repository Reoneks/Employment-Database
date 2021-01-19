#include "admineditvacancy.h"
#include "ui_admineditvacancy.h"
#include "database.h"
AdminEditVacancy::AdminEditVacancy(QWidget *parent):QMainWindow(parent),ui(new Ui::AdminEditVacancy){
    ui->setupUi(this);
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Змінити інформацію вакансій");
    QPalette pal;
    QPixmap map;
    map.load(":/image/images/HelpBackground.png");
    map=map.scaled(369,728,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pal.setBrush(ui->centralwidget->backgroundRole(),QBrush(map));
    ui->centralwidget->setPalette(pal);
    ui->centralwidget->setAutoFillBackground(true);
    Database *database=new Database();
    QVector<QVector<QString>>Result=database->SelectRequest("SELECT [Компанія].[Назва компанії],[Вимоги],[Опис],[Посада],[Зарплата],[Вакансії].[ID] "
                                                            "FROM [Вакансії] "
                                                            "INNER JOIN [Компанія] ON [Компанія].[ID]=[Вакансії].[Компанія] "
                                                            "ORDER BY [Вакансії].[ID] DESC",6);
    delete database;
    for(int i=0;i<Result.length();++i){
        Vacancy<<new FindEmployer;
        Vacancy[i]->SetData(Result[i][0],Result[i][1],Result[i][2],Result[i][3],Result[i][4]);
        Vacancy[i]->SetID(Result[i][5]);
        Vacancy[i]->AllowEdit();
        ui->stackedWidget->addWidget(Vacancy[i]);
    }
    ui->PrevPage->setVisible(false);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Ок");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Скасувати");
}
AdminEditVacancy::~AdminEditVacancy(){
    delete ui;
}
void AdminEditVacancy::on_buttonBox_accepted(){
    Database *database=new Database();
    foreach(FindEmployer *emp, Vacancy){
        QVector<QString>Result=emp->GetData();
        database->RequestForDatabase("UPDATE [Вакансії] "
                                     "SET [Посада]=\""+Result[1]+"\","
                                         "[Вимоги]=\""+Result[3]+"\","
                                         "[Опис]=\""+Result[2]+"\","
                                         "[Зарплата]=\""+Result[0]+"\" "
                                     "WHERE [Вакансії].[ID]=\""+emp->GetID()+"\"");
    }
    delete database;
    close();
}
void AdminEditVacancy::on_buttonBox_rejected(){
    close();
}
void AdminEditVacancy::on_PrevPage_clicked(){
    if(ui->stackedWidget->currentIndex()==Vacancy.length()-1) ui->NextPage->setVisible(true);
    else if(ui->stackedWidget->currentIndex()==1) ui->PrevPage->setVisible(false);
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()-1);
}
void AdminEditVacancy::on_NextPage_clicked(){
    if(ui->stackedWidget->currentIndex()==0) ui->PrevPage->setVisible(true);
    else if(ui->stackedWidget->currentIndex()==Vacancy.length()-2) ui->NextPage->setVisible(false);
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
}
