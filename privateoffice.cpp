#include "privateoffice.h"
#include "ui_privateoffice.h"
#include "database.h"
PrivateOffice::PrivateOffice(QWidget *parent):QMainWindow(parent),ui(new Ui::PrivateOffice){
    ui->setupUi(this);
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Особистий кабінет");
    LogOut=false;
    ui->Email->setReadOnly(true);
    ui->Email_2->setReadOnly(true);
    ui->JobSeeker->setReadOnly(true);
    ui->Telephone->setReadOnly(true);
    ui->CompanyName->setReadOnly(true);
    ui->CompanySite->setReadOnly(true);
    ui->Telephone_2->setReadOnly(true);
    ui->textBrowser->setReadOnly(true);
    ui->textBrowser_1->setReadOnly(true);
    ui->textBrowser_2->setReadOnly(true);
    ui->textBrowser_3->setReadOnly(true);
    ui->textBrowser_4->setReadOnly(true);
    ui->textBrowser_5->setReadOnly(true);
    ui->textBrowser_6->setReadOnly(true);
    ui->textBrowser_7->setReadOnly(true);
    ui->textBrowser_8->setReadOnly(true);
    ui->textBrowser_9->setReadOnly(true);
    ui->textBrowser_10->setReadOnly(true);
    ui->textBrowser_11->setReadOnly(true);
    ui->EditEduc->setVisible(false);
    ui->AddNewJob->setVisible(false);
    ui->AddNewEduc->setVisible(false);
    ui->ShortlyAboutMyself->setReadOnly(true);
    ui->CompanyBriefly->setReadOnly(true);
    ui->Ok->setVisible(false);
    ui->Cancel->setVisible(false);
    ui->LoadNewAvatar->setVisible(false);
    ui->Ok_2->setVisible(false);
    ui->Cancel_2->setVisible(false);
    ui->LoadNewAvatar_2->setVisible(false);
    ui->Email->setTabChangesFocus(true);
    ui->Email_2->setTabChangesFocus(true);
    ui->JobSeeker->setTabChangesFocus(true);
    ui->Telephone->setTabChangesFocus(true);
    ui->CompanyName->setTabChangesFocus(true);
    ui->CompanySite->setTabChangesFocus(true);
    ui->Telephone_2->setTabChangesFocus(true);
    ui->ShortlyAboutMyself->setTabChangesFocus(true);
    ui->CompanyBriefly->setTabChangesFocus(true);
    ui->Education->setReadOnly(true);
    ui->PreviousEduc->horizontalHeader()->setStretchLastSection(true);
    ui->Data->hideColumn(0);
    ui->Data->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->PreviousEduc->hideColumn(0);
    ui->PreviousEduc->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->Edit->setStyleSheet("#Edit{border-image: url(:/image/images/Edit.png) 0 0 0 0 stretch stretch;} QToolTip{border: 2px solid darkkhaki; padding: 5px; border-radius: 1px;}");
    ui->NextPage->setStyleSheet("#NextPage{border-image: url(:/image/images/ArrowRight.png);} QToolTip{border: 2px solid darkkhaki; padding: 5px; border-radius: 1px;}");
    ui->NextPage->setVisible(false);
    ui->Data->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->Data->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->PreviousEduc->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->PreviousEduc->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    QPalette pal;
    QPixmap map;
    map.load(":/image/images/MainwindowBackground.png");
    map=map.scaled(387,644,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pal.setBrush(ui->centralwidget->backgroundRole(),QBrush(map));
    ui->centralwidget->setPalette(pal);
    ui->centralwidget->setAutoFillBackground(true);
}
bool PrivateOffice::GetLogOut(){
    return LogOut;
}
void PrivateOffice::SetJobSeekerData(QString JobSeeker, QString Email, QString Telephone, QString Text, QByteArray Photo){
    ui->stackedWidget->setCurrentIndex(1);
    JobSeekerEmail=Email;
    if(Email=="admin")ui->Edit->setVisible(false);
    Email[0]=Email[0].toUpper();
    ui->Email_2->setText(Email);
    ui->JobSeeker->setText(JobSeeker);
    ui->Telephone_2->setText(Telephone);
    ui->ShortlyAboutMyself->setText(Text);
    ui->NextPage->setVisible(true);
    if(Photo.length()>0){
        QPixmap image;
        image.loadFromData(Photo);
        image=image.scaled(131,131,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        ui->JobSeekerPhoto->setPixmap(image);
    }
}
void PrivateOffice::OnlyRead(QString CompanyOrJobSeeker){
    ui->Edit->setVisible(false);
    if(CompanyOrJobSeeker=="Company")ui->NextPage->setVisible(true);
    ui->textBrowser->setVisible(false);
    setWindowTitle("Інформація про користувача");
}
void PrivateOffice::SetCompanyData(QString Company,QString Email,QString Telephone,QString Site,QString Text,QByteArray Logo){
    ui->stackedWidget->setCurrentIndex(0);
    ui->Email->setText(Email);
    ui->NextPage->setVisible(false);
    ui->Telephone->setText(Telephone);
    CompanyName=Company;
    Company[0]=Company[0].toUpper();
    ui->CompanyName->setText(Company);
    ui->CompanySite->setText(Site);
    ui->CompanyBriefly->setText(Text);
    if(Logo.length()>0){
        QPixmap image;
        image.loadFromData(Logo);
        image=image.scaled(131,131,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        ui->CompanyLogo->setPixmap(image);
    }
}
PrivateOffice::~PrivateOffice(){
    delete ui;
}
bool PrivateOffice::Validation(QString WhatValidate,QString ValidationRule){
    const std::regex RegEx(ValidationRule.toStdString());
    return std::regex_search(WhatValidate.toStdString(),RegEx);
}
void PrivateOffice::on_Ok_clicked(){
    bool ValidEmail,ValidTelephone;
    ValidEmail=Validation(ui->Email->toPlainText().toLower(),"^[_a-z0-9-]+(\\.[_a-z0-9-]+)*@[a-z0-9-]+(\\.[a-z0-9-]+)*(\\.[a-z]{2,4})$");
    ValidTelephone=Validation(ui->Telephone->toPlainText(),"^\\+?\\d{1,3}?[- .]?\\(?(?:\\d{2,3})\\)?[- .]?\\d\\d\\d[- .]?\\d\\d\\d\\d$");
    if(ValidEmail&&(ValidTelephone||(ui->Telephone->toPlainText()=="-"))){
        if(ui->CompanyName->toPlainText()!=""){
            Database *database=new Database();
            StartEditing();
            database->RequestForDatabase("UPDATE [Компанія] "
                                         "SET [Назва компанії]=\""+ui->CompanyName->toPlainText().toLower()+"\","
                                             "[Email]=\""+ui->Email->toPlainText()+"\","
                                             "[Телефон]=\""+ui->Telephone->toPlainText()+"\","
                                             "[Сайт компанії]=\""+ui->CompanySite->toPlainText()+"\","
                                             "[Коротко про компанію]=\""+ui->CompanyBriefly->toPlainText()+"\" "
                                         "WHERE [Компанія].[Назва компанії]=\""+CompanyName+"\"");
            QPixmap map1=*ui->CompanyLogo->pixmap();
            QByteArray bArray;
            QBuffer buffer(&bArray);
            buffer.open(QIODevice::WriteOnly);
            map1.save(&buffer,"PNG");
            database->ImageAddRequest(bArray,"Компанія","Логотип"," WHERE [Компанія].[Назва компанії]=\""+ui->CompanyName->toPlainText().toLower()+"\"");
            delete database;
            if(CompanyName!=ui->CompanyName->toPlainText().toLower()){
                LogOut=true;
                close();
            }
        }else ErrorMessage("Ви не ввели назву компанії");
    }else{
        if(!ValidEmail&&!ValidTelephone&&(ui->Telephone->toPlainText()!="-")){
            ErrorMessage("Телефон і Email введені неправильно.\nЯкщо не хочете вводити телефон, то поставте -");
            ui->Email->setText("");
            ui->Telephone->setText("");
        }
        else if(!ValidEmail){
            ErrorMessage("Email введений неправильно.");
            ui->Email->setText("");
        }
        else if(!ValidTelephone&&(ui->Telephone->toPlainText()!="-")){
            ErrorMessage("Телефон введений неправильно.\nЯкщо не хочете вводити телефон, то поставте -");
            ui->Telephone->setText("");
        }
    }
}
void PrivateOffice::ErrorMessage(QString Error){
    msgBox=new QMessageBox();
    msgBox->setText(Error);
    msgBox->setWindowIcon(QIcon(":/image/images/Error.ico"));
    msgBox->setWindowTitle("Помилка");
    msgBox->show();
}
void PrivateOffice::on_Cancel_clicked(){
    StartEditing();
}
void PrivateOffice::on_Edit_clicked(){
    ui->Edit->setVisible(false);
    ui->Ok->setVisible(true);
    ui->Cancel->setVisible(true);
    ui->LoadNewAvatar->setVisible(true);
    ui->Ok_2->setVisible(true);
    ui->Cancel_2->setVisible(true);
    ui->LoadNewAvatar_2->setVisible(true);
    ui->Email->setReadOnly(false);
    ui->Email_2->setReadOnly(false);
    ui->JobSeeker->setReadOnly(false);
    ui->Telephone->setReadOnly(false);
    ui->CompanyName->setReadOnly(false);
    ui->CompanySite->setReadOnly(false);
    ui->Telephone_2->setReadOnly(false);
    ui->ShortlyAboutMyself->setReadOnly(false);
    ui->CompanyBriefly->setReadOnly(false);
    ui->EditEduc->setVisible(true);
    ui->Education->setVisible(false);
    ui->AddNewJob->setVisible(true);
    ui->AddNewEduc->setVisible(true);
    ui->Data->setEditTriggers(QAbstractItemView::EditTrigger::AllEditTriggers);
    ui->PreviousEduc->setEditTriggers(QAbstractItemView::EditTrigger::AllEditTriggers);
    ui->EditEduc->clear();
    ui->EditEduc->addItem(ui->Education->toPlainText());
    if(ui->Education->toPlainText()!="Початкова")ui->EditEduc->addItem("Початкова");
    if(ui->Education->toPlainText()!="Середня загальна")ui->EditEduc->addItem("Середня загальна");
    if(ui->Education->toPlainText()!="Середня професійна")ui->EditEduc->addItem("Середня професійна");
    if(ui->Education->toPlainText()!="Вища")ui->EditEduc->addItem("Вища");
}
void PrivateOffice::on_Ok_2_clicked(){
    bool ValidEmail,ValidTelephone;
    ValidEmail=Validation(ui->Email_2->toPlainText().toLower(),"^[_a-z0-9-]+(\\.[_a-z0-9-]+)*@[a-z0-9-]+(\\.[a-z0-9-]+)*(\\.[a-z]{2,4})$");
    ValidTelephone=Validation(ui->Telephone_2->toPlainText(),"^\\+?\\d{1,3}?[- .]?\\(?(?:\\d{2,3})\\)?[- .]?\\d\\d\\d[- .]?\\d\\d\\d\\d$");
    if(ValidEmail&&(ValidTelephone||(ui->Telephone_2->toPlainText()=="-"))){
        if(ui->JobSeeker->toPlainText()!=""){
            Database *database=new Database();
            StartEditing();
            database->RequestForDatabase("UPDATE [Здобувач] "
                                         "SET [ПІБ]=\""+ui->JobSeeker->toPlainText()+"\","
                                             "[Email]=\""+ui->Email_2->toPlainText().toLower()+"\","
                                             "[Телефон]=\""+ui->Telephone_2->toPlainText()+"\","
                                             "[Коротко про себе]=\""+ui->ShortlyAboutMyself->toPlainText()+"\","
                                             "[Рівень освіти]=("
                                                    "SELECT [Рівень освіти].[ID] "
                                                    "FROM [Рівень освіти] "
                                                    "WHERE [Рівень освіти].[Освіта]=\""+ui->EditEduc->currentText()+"\""
                                                ") "
                                         "WHERE [Здобувач].[Email]=\""+JobSeekerEmail+"\"");
            ui->Education->setPlainText(ui->EditEduc->currentText());
            QPixmap map1=*ui->JobSeekerPhoto->pixmap();
            QByteArray bArray;
            QBuffer buffer(&bArray);
            buffer.open(QIODevice::WriteOnly);
            map1.save(&buffer,"PNG");
            database->ImageAddRequest(bArray,"Здобувач","Фото"," WHERE [Здобувач].[Email]=\""+ui->Email_2->toPlainText().toLower()+"\"");
            for(int i=0;i<ui->Data->rowCount();++i){
                QVector<QString> TableData;
                for(int u=0;u<7;++u){
                    TableData<<ui->Data->item(i,u)->text();
                }
                bool ValidDate1,ValidDate2;
                ValidDate1=Validation(TableData[1],"^\\d{4}[./-]\\d{2}$");
                ValidDate2=Validation(TableData[2],"^\\d{4}[./-]\\d{2}$");
                if(ValidDate1&&ValidDate2){
                    if(TableData[3]!=""){
                        if(TableData[4]!=""){
                            if(TableData[0]!="?"){
                                database->RequestForDatabase("UPDATE [Попередні місця роботи] "
                                                             "SET [Здобувач]=("
                                                                    "SELECT [ID] "
                                                                    "FROM [Здобувач] "
                                                                    "WHERE [Здобувач].[Email]=\""+JobSeekerEmail+"\""
                                                                 "),"
                                                                 "[Дата прийняття на роботу]=\""+TableData[1]+"\","
                                                                 "[Дата звільнення]=\""+TableData[2]+"\","
                                                                 "[Назва компанії]=\""+TableData[3]+"\","
                                                                 "[Посада]=\""+TableData[4]+"\","
                                                                 "[Місцезнаходження компанії]=\""+TableData[5]+"\","
                                                                 "[Посадові обовязки та досягнення]=\""+TableData[6]+"\" "
                                                            "WHERE [ID]=\""+TableData[0]+"\"");
                            }else{
                                database->RequestForDatabase("INSERT INTO [Попередні місця роботи]([Здобувач],[Дата прийняття на роботу],[Дата звільнення],[Назва компанії],[Посада],[Місцезнаходження компанії],[Посадові обовязки та досягнення]) "
                                                             "VALUES(("
                                                                         "SELECT [ID] "
                                                                         "FROM [Здобувач] "
                                                                         "WHERE [Здобувач].[Email]=\""+JobSeekerEmail+"\""
                                                                    "),\""+
                                                                    TableData[1]+"\",\""+
                                                                    TableData[2]+"\",\""+
                                                                    TableData[3]+"\",\""+
                                                                    TableData[4]+"\",\""+
                                                                    TableData[5]+"\",\""+
                                                                    TableData[6]
                                                             +"\")");
                            }
                        }else ErrorMessage("Ви не ввели назву посади!! ("+QString::number(i+1)+" рядок)");
                    }else ErrorMessage("Ви не ввели назву компанії!! ("+QString::number(i+1)+" рядок)");
                }else ErrorMessage("Неправильно введена одна з дат ("+QString::number(i+1)+" рядок).\nПравильна форма написання дати: YYYY.MM .");
            }
            for(int i=0;i<ui->PreviousEduc->rowCount();++i){
                QVector<QString> TableData;
                for(int u=0;u<5;++u){
                    TableData<<ui->PreviousEduc->item(i,u)->text();
                }
                bool ValidDate1,ValidDate2;
                ValidDate1=Validation(TableData[1],"^\\d{4}[./-]\\d{2}$");
                ValidDate2=Validation(TableData[2],"^\\d{4}[./-]\\d{2}$");
                if(ValidDate1&&ValidDate2){
                    if(TableData[3]!=""){
                        if(TableData[0]!="?"){
                            database->RequestForDatabase("UPDATE [Освіта] "
                                                         "SET [Здобувач]=("
                                                                "SELECT [ID] "
                                                                "FROM [Здобувач] "
                                                                "WHERE [Здобувач].[Email]=\""+JobSeekerEmail+"\""
                                                             "),"
                                                             "[Рік початку навчання]=\""+TableData[1]+"\","
                                                             "[Рік завершення навчання]=\""+TableData[2]+"\","
                                                             "[Навчальний заклад]=\""+TableData[3]+"\","
                                                             "[Кваліфікація]=\""+TableData[4]+"\" "
                                                        "WHERE [ID]=\""+TableData[0]+"\"");
                        }else{
                            database->RequestForDatabase("INSERT INTO [Освіта]([Здобувач],[Рік початку навчання],[Рік завершення навчання],[Навчальний заклад],[Кваліфікація]) "
                                                         "VALUES(("
                                                                     "SELECT [ID] "
                                                                     "FROM [Здобувач] "
                                                                     "WHERE [Здобувач].[Email]=\""+JobSeekerEmail+"\""
                                                                "),\""+
                                                                TableData[1]+"\",\""+
                                                                TableData[2]+"\",\""+
                                                                TableData[3]+"\",\""+
                                                                TableData[4]
                                                         +"\")");
                        }
                    }else ErrorMessage("Ви не ввели назву навчального закладу!! ("+QString::number(i+1)+" рядок)");
                }else ErrorMessage("Неправильно введена одна з дат ("+QString::number(i+1)+" рядок).\nПравильна форма написання дати: YYYY.MM .");
            }
            for(int i=ui->Data->rowCount()-1;i>-1;--i){
                ui->Data->removeRow(i);
            }
            for(int i=ui->PreviousEduc->rowCount()-1;i>-1;--i){
                ui->PreviousEduc->removeRow(i);
            }
            QVector<QVector<QString>> Data=database->SelectRequest("SELECT [Попередні місця роботи].[ID],[Попередні місця роботи].[Дата прийняття на роботу],[Попередні місця роботи].[Дата звільнення],[Попередні місця роботи].[Назва компанії],[Попередні місця роботи].[Посада],[Попередні місця роботи].[Місцезнаходження компанії],[Попередні місця роботи].[Посадові обовязки та досягнення] "
                                                                   "FROM [Попередні місця роботи] "
                                                                   "INNER JOIN [Здобувач] ON [Здобувач].[ID]=[Попередні місця роботи].[Здобувач] "
                                                                   "WHERE [Здобувач].[Email]=\""+JobSeekerEmail+"\"",7);
            QVector<QVector<QString>> Data1= database->SelectRequest("SELECT [Освіта].[ID],[Освіта].[Рік початку навчання],[Освіта].[Рік завершення навчання],[Освіта].[Навчальний заклад],[Освіта].[Кваліфікація] "
                                                                     "FROM [Освіта] "
                                                                     "INNER JOIN [Здобувач] ON [Здобувач].[ID]=[Освіта].[Здобувач] "
                                                                     "WHERE [Здобувач].[Email]=\""+JobSeekerEmail+"\"",5);
            for(int i=0;i<Data.length();++i){
                ui->Data->insertRow(ui->Data->rowCount());
                for(int u=0;u<7;++u){
                    QTableWidgetItem *item=new QTableWidgetItem;
                    item->setText(Data[i][u]);
                    ui->Data->setItem(i,u,item);
                }
            }
            for(int i=0;i<Data1.length();++i){
                ui->PreviousEduc->insertRow(ui->PreviousEduc->rowCount());
                for(int u=0;u<5;++u){
                    QTableWidgetItem *item=new QTableWidgetItem;
                    item->setText(Data1[i][u]);
                    ui->PreviousEduc->setItem(i,u,item);
                }
            }
            delete database;
            if(JobSeekerEmail!=ui->Email_2->toPlainText().toLower()){
                LogOut=true;
                close();
            }
        }else ErrorMessage("Ви не ввели ПІБ");
    }else{
        if(!ValidEmail&&!ValidTelephone&&(ui->Telephone_2->toPlainText()!="-")){
            ErrorMessage("Телефон і Email введені неправильно.\nЯкщо не хочете вводити телефон, то поставте -");
            ui->Email_2->setText("");
            ui->Telephone_2->setText("");
        }
        else if(!ValidEmail){
            ErrorMessage("Email введений неправильно.");
            ui->Email_2->setText("");
        }
        else if(!ValidTelephone&&(ui->Telephone_2->toPlainText()!="-")){
            ErrorMessage("Телефон введений неправильно.\nЯкщо не хочете вводити телефон, то поставте -");
            ui->Telephone_2->setText("");
        }
    }
}
void PrivateOffice::on_Cancel_2_clicked(){
    StartEditing();
}
void PrivateOffice::StartEditing(){
    ui->Edit->setVisible(true);
    ui->Ok->setVisible(false);
    ui->Cancel->setVisible(false);
    ui->LoadNewAvatar->setVisible(false);
    ui->Ok_2->setVisible(false);
    ui->Cancel_2->setVisible(false);
    ui->LoadNewAvatar_2->setVisible(false);
    ui->Email->setReadOnly(true);
    ui->Email_2->setReadOnly(true);
    ui->JobSeeker->setReadOnly(true);
    ui->Telephone->setReadOnly(true);
    ui->CompanyName->setReadOnly(true);
    ui->CompanySite->setReadOnly(true);
    ui->Telephone_2->setReadOnly(true);
    ui->ShortlyAboutMyself->setReadOnly(true);
    ui->CompanyBriefly->setReadOnly(true);
    ui->EditEduc->setVisible(false);
    ui->Education->setVisible(true);
    ui->AddNewJob->setVisible(false);
    ui->AddNewEduc->setVisible(false);
    ui->Data->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->PreviousEduc->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
void PrivateOffice::on_LoadNewAvatar_2_clicked(){
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"),"/",tr("Images (*.png *.xpm *.jpg)"));
    if(filePath!=""){
        QPixmap image;
        image.load(filePath);
        image=image.scaled(131,131,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        ui->JobSeekerPhoto->setPixmap(image);
    }
}

void PrivateOffice::on_LoadNewAvatar_clicked(){
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"),"/",tr("Images (*.png *.xpm *.jpg)"));
    if(filePath!=""){
        QPixmap image;
        image.load(filePath);
        image=image.scaled(131,131,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        ui->CompanyLogo->setPixmap(image);
    }
}
void PrivateOffice::on_NextPage_clicked(){
    if(ui->stackedWidget->currentIndex()==2){
        ui->stackedWidget->setCurrentIndex(1);
        ui->NextPage->setStyleSheet("#NextPage{border-image: url(:/image/images/ArrowRight.png);} QToolTip{border: 2px solid darkkhaki; padding: 5px; border-radius: 1px;}");
        ui->NextPage->setToolTip("Наступна сторінка");
        if(windowTitle()=="Особистий кабінет")ui->Edit->setVisible(true);
    }else{
        ui->stackedWidget->setCurrentIndex(2);
        ui->NextPage->setStyleSheet("#NextPage{border-image: url(:/image/images/ArrowLeft.png);} QToolTip{border: 2px solid darkkhaki; padding: 5px; border-radius: 1px;}");
        ui->NextPage->setToolTip("Попередня сторінка");
        ui->Edit->setVisible(false);
    }
}
void PrivateOffice::SetUserAdditionalData(QString Education, QVector<QVector<QString>> Data, QVector<QVector<QString>> Data1){
    ui->Education->setPlainText(Education);
    for(int i=0;i<Data.length();++i){
        ui->Data->insertRow(ui->Data->rowCount());
        for(int u=0;u<7;++u){
            QTableWidgetItem *item=new QTableWidgetItem;
            item->setText(Data[i][u]);
            ui->Data->setItem(i,u,item);
        }
    }
    for(int i=0;i<Data1.length();++i){
        ui->PreviousEduc->insertRow(ui->PreviousEduc->rowCount());
        for(int u=0;u<5;++u){
            QTableWidgetItem *item=new QTableWidgetItem;
            item->setText(Data1[i][u]);
            ui->PreviousEduc->setItem(i,u,item);
        }
    }
}
void PrivateOffice::InsertDataInTable(){
    QVector<QString> TableData=PreviousJobW->GetData();
    delete PreviousJobW;
    ui->Data->insertRow(ui->Data->rowCount());
    for(int i=0;i<TableData.length()+1;++i){
        QTableWidgetItem *item=new QTableWidgetItem;
        if(i!=0)item->setText(TableData[i-1]);
        else item->setText("?");
        ui->Data->setItem(ui->Data->rowCount()-1,i,item);
    }
}
void PrivateOffice::InsertDataInTable_1(){
    QVector<QString> TableData=Learning->GetData();
    delete Learning;
    ui->PreviousEduc->insertRow(ui->PreviousEduc->rowCount());
    for(int i=0;i<TableData.length()+1;++i){
        QTableWidgetItem *item=new QTableWidgetItem;
        if(i!=0)item->setText(TableData[i-1]);
        else item->setText("?");
        ui->PreviousEduc->setItem(ui->PreviousEduc->rowCount()-1,i,item);
    }
}
void PrivateOffice::on_AddNewJob_clicked(){
    PreviousJobW=new AddPreviousJob();
    PreviousJobW->show();
    connect(PreviousJobW,SIGNAL(Accessed()),this,SLOT(InsertDataInTable()),Qt::UniqueConnection);
}
void PrivateOffice::on_AddNewEduc_clicked(){
    Learning=new AddPlaceOfLearning();
    Learning->show();
    connect(Learning,SIGNAL(Accessed()),this,SLOT(InsertDataInTable_1()),Qt::UniqueConnection);
}
