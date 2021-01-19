#include "registration.h"
#include "ui_registration.h"
#include "database.h"
Registration::Registration(QWidget *parent):QMainWindow(parent),ui(new Ui::Registration){
    ui->setupUi(this);
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Реєстрація");
    QPalette pal;
    QPixmap map;
    map.load(":/image/images/MainwindowBackground.png");
    map=map.scaled(547,529,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pal.setBrush(ui->centralwidget->backgroundRole(),QBrush(map));
    ui->centralwidget->setPalette(pal);
    ui->centralwidget->setAutoFillBackground(true);
    ui->Email->setTabChangesFocus(true);
    ui->Password->setTabChangesFocus(true);
    ui->JobSeeker->setTabChangesFocus(true);
    ui->TelephoneC->setTabChangesFocus(true);
    ui->CompanyName->setTabChangesFocus(true);
    ui->CompanySite->setTabChangesFocus(true);
    ui->TelephoneJS->setTabChangesFocus(true);
    ui->ShortlyAboutMyself->setTabChangesFocus(true);
    ui->ShortlyAboutCompany->setTabChangesFocus(true);
    ui->PreviousJob->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->PreviousJob->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->PreviousJob->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->PreviousEduc->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->PreviousEduc->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->PreviousEduc->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->PreviousEduc->horizontalHeader()->setStretchLastSection(true);
    ui->radioButton_2->setChecked(true);
}
void Registration::SetMode(int Mode){
    this->Mode=Mode;
    ui->stackedWidget->setCurrentIndex(Mode);
    if(Mode==0)ui->OK->setText("Далі");
}
Registration::~Registration(){
    delete ui;
}
QString Registration::GetAccountName(){
    return NewAccountName;
}
void Registration::on_OK_clicked(){
    bool ValidEmail,ValidTelephone;
    QString Telephone;
    ValidEmail=Validation(ui->Email->toPlainText().toLower(),"^[_a-z0-9-]+(\\.[_a-z0-9-]+)*@[a-z0-9-]+(\\.[a-z0-9-]+)*(\\.[a-z]{2,4})$");
    if(Mode==0)Telephone=ui->TelephoneJS->toPlainText();
    else Telephone=ui->TelephoneC->toPlainText();
    ValidTelephone=Validation(Telephone,"^\\+?\\d{1,3}?[- .]?\\(?(?:\\d{2,3})\\)?[- .]?\\d\\d\\d[- .]?\\d\\d\\d\\d$");
    if(ValidEmail&&(ValidTelephone||(Telephone=="-"))){
        if((ui->JobSeeker->toPlainText()=="")&&(ui->CompanyName->toPlainText()==""))ErrorMessage("Ви не ввели ПІБ/Назву компанії");
        else{
            if(ui->Password->toPlainText()=="")ErrorMessage("Ви не ввели пароль");
            else{
                if(ui->OK->text()=="Далі"){
                    ui->OK->setText("Ок");
                    ui->stackedWidget->setCurrentIndex(2);
                }else{
                    Database *database=new Database();
                    bool Error;
                    QPixmap map1;
                    if(ui->Photo->pixmap()==nullptr) map1.load(":/image/images/Лого.png");
                    else map1=*ui->Photo->pixmap();
                    QByteArray bArray;
                    QBuffer buffer(&bArray);
                    buffer.open(QIODevice::WriteOnly);
                    map1.save(&buffer,"PNG");
                    if(Mode==0){
                        NewAccountName=ui->Email->toPlainText().toLower();
                        QButtonGroup group;
                        QList<QRadioButton *> allButtons = ui->stackedWidget->findChildren<QRadioButton *>();
                        for(int i=0;i<allButtons.size();++i){
                            group.addButton(allButtons[i],i);
                        }
                        database->RequestForDatabase("INSERT INTO Здобувач(ПІБ,Email,Телефон,[Коротко про себе],[Дата реєстрації],[Рівень освіти]) "
                                                     "VALUES(\""+
                                                         ui->JobSeeker->toPlainText()+"\",\""+
                                                         ui->Email->toPlainText().toLower()+"\",\""+
                                                         ui->TelephoneJS->toPlainText()+"\",\""+
                                                         ui->ShortlyAboutMyself->toPlainText()+"\",\""+
                                                         QDate::currentDate().toString("yyyy-MM")+"\",("
                                                             "SELECT [ID] "
                                                             "FROM [Рівень освіти] "
                                                             "WHERE [Рівень освіти].[Освіта]=\""+group.checkedButton()->text()+"\""
                                                     "))");
                        Error=database->ReturnError();
                        if(!Error){
                            QVector<QVector<QString>>Result=database->SelectRequest("SELECT last_insert_rowid()",1);
                            database->RequestForDatabase("INSERT INTO [Паролі здобувачів](Здобувач,Пароль) "
                                                         "VALUES(\""+Result[0][0]+"\",\""+
                                                            ui->Password->toPlainText()
                                                         +"\")");
                            for(int i=0;i<ui->PreviousJob->rowCount();++i){
                                QVector<QString> TableData;
                                for(int u=0;u<6;++u){
                                    TableData<<ui->PreviousJob->item(i,u)->text();
                                }
                                database->RequestForDatabase("INSERT INTO [Попередні місця роботи]([Здобувач],[Дата прийняття на роботу],[Дата звільнення],[Назва компанії],[Посада],[Місцезнаходження компанії],[Посадові обовязки та досягнення]) "
                                                             "VALUES(\""+
                                                                Result[0][0]+"\",\""+
                                                                TableData[0]+"\",\""+
                                                                TableData[1]+"\",\""+
                                                                TableData[2]+"\",\""+
                                                                TableData[3]+"\",\""+
                                                                TableData[4]+"\",\""+
                                                                TableData[5]
                                                             +"\")");
                            }
                            for(int i=0;i<ui->PreviousEduc->rowCount();++i){
                                QVector<QString> TableData;
                                for(int u=0;u<4;++u){
                                    TableData<<ui->PreviousEduc->item(i,u)->text();
                                }
                                database->RequestForDatabase("INSERT INTO [Освіта]([Здобувач],[Рік початку навчання],[Рік завершення навчання],[Навчальний заклад],[Кваліфікація]) "
                                                             "VALUES(\""+
                                                                Result[0][0]+"\",\""+
                                                                TableData[0]+"\",\""+
                                                                TableData[1]+"\",\""+
                                                                TableData[2]+"\",\""+
                                                                TableData[3]
                                                             +"\")");
                            }
                            database->ImageAddRequest(bArray,"Здобувач","Фото"," WHERE [Здобувач].[Email]=\""+ui->Email->toPlainText().toLower()+"\"");
                        }
                    }else{
                        NewAccountName=ui->CompanyName->toPlainText().toLower();
                        database->RequestForDatabase("INSERT INTO Компанія([Назва компанії],Email,Телефон,[Сайт компанії],[Коротко про компанію],[Дата реєстрації]) "
                                                     "VALUES(\""+
                                                         ui->CompanyName->toPlainText().toLower()+"\",\""+
                                                         ui->Email->toPlainText()+"\",\""+
                                                         ui->TelephoneC->toPlainText()+"\",\""+
                                                         ui->CompanySite->toPlainText()+"\",\""+
                                                         ui->ShortlyAboutCompany->toPlainText()+"\",\""+
                                                         QDate::currentDate().toString("yyyy-MM")
                                                     +"\")");
                        Error=database->ReturnError();
                        if(!Error){
                            database->RequestForDatabase("INSERT INTO [Паролі компаній](Компанія,Пароль) "
                                                         "VALUES(last_insert_rowid(),\""+
                                                            ui->Password->toPlainText()
                                                         +"\")");
                            database->ImageAddRequest(bArray,"Компанія","Логотип"," WHERE [Компанія].[Назва компанії]=\""+ui->CompanyName->toPlainText().toLower()+"\"");
                        }
                    }
                    delete database;
                    if(!Error){
                        close();
                        emit Finished();
                    }
                }
            }
        }
    }else{
        if(!ValidEmail&&!ValidTelephone&&(Telephone!="-")){
            ErrorMessage("Телефон і Email введені неправильно.\nЯкщо не хочете вводити телефон, то поставте -");
            ui->Email->setText("");
            ui->TelephoneC->setText("");
            ui->TelephoneJS->setText("");
        }
        else if(!ValidEmail){
            ErrorMessage("Email введений неправильно.");
            ui->Email->setText("");
        }
        else if(!ValidTelephone&&(Telephone!="-")){
            ErrorMessage("Телефон введений неправильно.\nЯкщо не хочете вводити телефон, то поставте -");
            ui->TelephoneC->setText("");
            ui->TelephoneJS->setText("");
        }
    }
}
void Registration::on_Cancel_clicked(){
    close();
    emit NotFinished();
}
bool Registration::Validation(QString WhatValidate,QString ValidationRule){
    const std::regex RegEx(ValidationRule.toStdString());
    return std::regex_search(WhatValidate.toStdString(),RegEx);
}
void Registration::on_LoadPhoto_clicked(){
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"),"/",tr("Images (*.png *.xpm *.jpg)"));
    if(filePath!=""){
        QPixmap image;
        image.load(filePath);
        image=image.scaled(131,131,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        ui->Photo->setPixmap(image);
    }
}
void Registration::ErrorMessage(QString Error){
    msgBox=new QMessageBox();
    msgBox->setText(Error);
    msgBox->setWindowIcon(QIcon(":/image/images/Error.ico"));
    msgBox->setWindowTitle("Помилка");
    msgBox->show();
}
void Registration::InsertDataInTable(){
    QVector<QString> TableData=PreviousJobW->GetData();
    delete PreviousJobW;
    ui->PreviousJob->insertRow(ui->PreviousJob->rowCount());
    for(int i=0;i<TableData.length();++i){
        QTableWidgetItem *item=new QTableWidgetItem;
        item->setText(TableData[i]);
        ui->PreviousJob->setItem(ui->PreviousJob->rowCount()-1,i,item);
    }
}
void Registration::InsertDataInTable_1(){
    QVector<QString> TableData=Learning->GetData();
    delete Learning;
    ui->PreviousEduc->insertRow(ui->PreviousEduc->rowCount());
    for(int i=0;i<TableData.length();++i){
        QTableWidgetItem *item=new QTableWidgetItem;
        item->setText(TableData[i]);
        ui->PreviousEduc->setItem(ui->PreviousEduc->rowCount()-1,i,item);
    }
}
void Registration::on_AddNewJob_clicked(){
    PreviousJobW=new AddPreviousJob();
    PreviousJobW->show();
    connect(PreviousJobW,SIGNAL(Accessed()),this,SLOT(InsertDataInTable()),Qt::UniqueConnection);
}
void Registration::on_AddNewEduc_clicked(){
    Learning=new AddPlaceOfLearning();
    Learning->show();
    connect(Learning,SIGNAL(Accessed()),this,SLOT(InsertDataInTable_1()),Qt::UniqueConnection);
}
