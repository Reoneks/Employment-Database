#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "news.h"
#include "database.h"
#include "jobapplications.h"
#include "addvacancy.h"
#include "findemployer.h"
#include "privateoffice.h"
#include "changenews.h"
#include "createmail.h"
#include "userstatistics.h"
#include "resume.h"
#include "admineditvacancy.h"
MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow){
    ui->setupUi(this);
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Працевлаштування");
    QPalette pal;
    QPixmap map;
    map.load(":/image/images/MainwindowBackground.png");
    map=map.scaled(593,697,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pal.setBrush(ui->centralwidget->backgroundRole(),QBrush(map));
    ui->centralwidget->setPalette(pal);
    ui->centralwidget->setAutoFillBackground(true);
    database=new Database();
    database->RequestForDatabase("CREATE TABLE IF NOT EXISTS \"Компанія\" ("
                                     "\"ID\" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, "
                                     "\"Назва компанії\" TEXT NOT NULL UNIQUE, "
                                     "\"Email\" TEXT NOT NULL UNIQUE, "
                                     "\"Телефон\" TEXT, "
                                     "\"Сайт компанії\" TEXT, "
                                     "\"Коротко про компанію\" TEXT, "
                                     "\"Дата реєстрації\" DATE NOT NULL, "
                                     "\"Логотип\" BLOB"
                                 ")");
    database->RequestForDatabase("CREATE TABLE IF NOT EXISTS \"Рівень освіти\" ("
                                     "\"ID\" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, "
                                     "\"Освіта\" TEXT NOT NULL"
                                 ")");
    database->RequestForDatabase("CREATE TABLE IF NOT EXISTS \"Здобувач\" ("
                                     "\"ID\" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, "
                                     "\"ПІБ\" TEXT NOT NULL, "
                                     "\"Email\" TEXT NOT NULL UNIQUE, "
                                     "\"Телефон\" TEXT, "
                                     "\"Коротко про себе\" TEXT, "
                                     "\"Дата реєстрації\" DATE NOT NULL, "
                                     "\"Фото\" BLOB, "
                                     "\"Рівень освіти\" INTEGER NOT NULL DEFAULT 2 REFERENCES \"Рівень освіти\" (\"ID\")"
                                 ")");
    database->RequestForDatabase("CREATE TABLE IF NOT EXISTS \"Вакансії\" ("
                                     "\"ID\" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, "
                                     "\"Посада\" TEXT NOT NULL, "
                                     "\"Компанія\" INTEGER NOT NULL REFERENCES \"Компанія\" (\"ID\"), "
                                     "\"Вимоги\" TEXT, "
                                     "\"Опис\" TEXT, "
                                     "\"Зарплата\" INTEGER"
                                 ")");
    database->RequestForDatabase("CREATE TABLE IF NOT EXISTS \"Заявки\" ("
                                     "\"ID\" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, "
                                     "\"Здобувач\" INTEGER NOT NULL REFERENCES \"Здобувач\" (\"ID\"), "
                                     "\"Посада\" INTEGER NOT NULL REFERENCES \"Вакансії\" (\"ID\"), "
                                     "\"Текст заявки\" TEXT NOT NULL, "
                                     "\"Відповідь здобувачеві\" TEXT, "
                                     "\"Дата написання заявки\" DATE NOT NULL, "
                                     "\"Вилучено\" TEXT NOT NULL DEFAULT false"
                                 ")");
    database->RequestForDatabase("CREATE TABLE IF NOT EXISTS \"Резюме\" ("
                                     "\"ID\" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, "
                                     "\"Здобувач\" INTEGER NOT NULL UNIQUE REFERENCES \"Здобувач\" (\"ID\"), "
                                     "\"Бажана посада\" TEXT, "
                                     "\"Бажана зарплатня\" INTEGER, "
                                     "\"Короткий опис\" TEXT, "
                                     "\"Резюме\" BLOB"
                                 ")");
    database->RequestForDatabase("CREATE TABLE IF NOT EXISTS \"Освіта\" ("
                                     "\"ID\" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, "
                                     "\"Здобувач\" INTEGER NOT NULL REFERENCES \"Здобувач\" (\"ID\"), "
                                     "\"Рік початку навчання\" DATE NOT NULL, "
                                     "\"Рік завершення навчання\" DATE NOT NULL, "
                                     "\"Навчальний заклад\" TEXT NOT NULL, "
                                     "\"Кваліфікація\" TEXT"
                                 ")");
    database->RequestForDatabase("CREATE TABLE IF NOT EXISTS \"Паролі компаній\" ("
                                     "\"ID\" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, "
                                     "\"Компанія\" INTEGER NOT NULL UNIQUE REFERENCES \"Компанія\" (\"ID\"), "
                                     "\"Пароль\" TEXT NOT NULL"
                                 ")");
    database->RequestForDatabase("CREATE TABLE IF NOT EXISTS \"Паролі здобувачів\" ("
                                     "\"ID\" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, "
                                     "\"Здобувач\" INTEGER NOT NULL UNIQUE REFERENCES \"Здобувач\" (\"ID\"), "
                                     "\"Пароль\" TEXT NOT NULL"
                                 ")");
    database->RequestForDatabase("CREATE TABLE IF NOT EXISTS \"Новини проекту\" ("
                                     "\"ID\" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, "
                                     "\"Рубрика\" TEXT NOT NULL, "
                                     "\"Тема\" TEXT NOT NULL, "
                                     "\"Основний текст\" TEXT, "
                                     "\"Картинка\" BLOB"
                                 ")");
    database->RequestForDatabase("CREATE TABLE IF NOT EXISTS \"Попередні місця роботи\" ("
                                     "\"ID\" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, "
                                     "\"Здобувач\" INTEGER NOT NULL REFERENCES \"Здобувач\" (\"ID\"), "
                                     "\"Дата прийняття на роботу\" DATE NOT NULL, "
                                     "\"Дата звільнення\" DATE NOT NULL, "
                                     "\"Назва компанії\" TEXT NOT NULL, "
                                     "\"Посада\" TEXT NOT NULL, "
                                     "\"Місцезнаходження компанії\" TEXT, "
                                     "\"Посадові обовязки та досягнення\" TEXT"
                                 ")");
    QVector<QVector<QString>>Result=database->SelectRequest("SELECT [Email]"
                                                            "FROM [Здобувач]"
                                                            "WHERE [Здобувач].[Email]=\"admin\"",1);
    if(Result.length()==0)AddAdmin();
    Result=database->SelectRequest("SELECT [Освіта]"
                                   "FROM [Рівень освіти]",1);
    if(Result.length()==0)AddEduc();
    delete database;
    log=new Login();
    vacancy=new AddVacancy();
    TempJob=new JobApplications();
    TempEmplJS=new FindEmployer();
    TempEmpl=new FindEmployer();
    Leave=new QAction();
    Delete=new QAction();
    File=new QMenu();
    File->setTitle("Файл");
    Leave->setText("Вихід");
    Delete->setText("Вилучити аккаунт");
    File->addAction(Delete);
    File->addAction(Leave);
    ui->menuBar->addMenu(File);
    ui->MainTableForWidgets->viewport()->installEventFilter(this);
    ui->MainTableForWidgets->horizontalHeader()->setStretchLastSection(true);
    ui->MainTableForWidgets->horizontalHeader()->hide();
    ui->MainTableForWidgets->verticalHeader()->hide();
    ui->MainTableForWidgets->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->MainTableForWidgets->insertColumn(ui->MainTableForWidgets->columnCount());
    connect(log,SIGNAL(Accessed()),this,SLOT(OpenMainWindow()),Qt::UniqueConnection);
    connect(Leave,SIGNAL(triggered()),this,SLOT(ShowLoginForm()),Qt::UniqueConnection);
    connect(Delete,SIGNAL(triggered()),this,SLOT(AskDelete()),Qt::UniqueConnection);
    ui->lineEdit->setPlaceholderText("Пошук");
    ui->lineEdit->setAlignment(Qt::AlignRight);
    ui->lineEdit->setTextMargins(0,0,5,0);
    log->show();
}
void MainWindow::AddEduc(){
    QVector<QString>Data;
    Data<<"Початкова"<<"Середня загальна"<<"Середня професійна"<<"Вища";
    foreach(QString item,Data){
        database->RequestForDatabase("INSERT INTO [Рівень освіти](Освіта) "
                                     "VALUES(\""+item+"\")");
    }
}
void MainWindow::AddAdmin(){
    database->RequestForDatabase("INSERT INTO [Здобувач]([ПІБ],[Email],[Телефон],[Коротко про себе],[Дата реєстрації],[Рівень освіти])"
                                 "VALUES(\""
                                     "Admin\",\""
                                     "admin\",\""
                                     "0660253927\",\""
                                     "Адміністратор даного проекту\",\""
                                     "2020-03\",\""
                                     "4\""
                                 ")");
    QPixmap p;
    p.load(":/image/images/Admin.png");
    QByteArray bArray;
    QBuffer buffer(&bArray);
    buffer.open(QIODevice::WriteOnly);
    p.save(&buffer,"PNG");
    QVector<QVector<QString>>Result=database->SelectRequest("SELECT last_insert_rowid()",1);
    database->ImageAddRequest(bArray,"Здобувач","Фото"," WHERE [ID]=\""+Result[0][0]+"\"");
    database->RequestForDatabase("INSERT INTO [Паролі здобувачів]([Здобувач],[Пароль])"
                                 "VALUES(\""+
                                     Result[0][0]+"\",\""
                                     "admin\""
                                 ")");
}
void MainWindow::OpenMainWindow(){
    disconnect(log,SIGNAL(Accessed()),this,SLOT(OpenMainWindow()));
    vacancy->ClearData();
    Mode=log->GetMode();
    if(Mode=="JobSeeker"){
        ui->WhoIsLoggedIn->setCurrentIndex(0);
    }else if(Mode=="Employer"){
        ui->WhoIsLoggedIn->setCurrentIndex(1);
    }
    if(log->GetAccountName()=="admin"){
        ui->ChangeNews->setVisible(true);
        ui->CheckStatistics->setVisible(true);
        ui->RedactVacancy->setVisible(true);
        Delete->setDisabled(true);
    }else{
        ui->ChangeNews->setVisible(false);
        ui->CheckStatistics->setVisible(false);
        ui->RedactVacancy->setVisible(false);
        Delete->setDisabled(false);
    }
    database=new Database();
    HomePage();
    show();
}
void MainWindow::HomePage(){
    ui->lineEdit->setVisible(false);
    ui->widget->setVisible(false);
    ui->label->setVisible(false);
    for(int i=ui->MainTableForWidgets->rowCount()-1;i>-1;--i){
        ui->MainTableForWidgets->removeRow(i);
    }
    NewsWidget.clear();
    if(log->GetAccountName()=="admin")ui->ChangeNews->setVisible(true);
    Filled="News";
    QVector<QVector<QString>>Result=database->SelectRequest("SELECT [Рубрика],[Тема],[Основний текст],[ID] "
                                                            "FROM [Новини проекту] "
                                                            "ORDER BY [Новини проекту].[ID] DESC",4);
    for(int i=0;i<Result.length();++i){
        NewsWidget<<new News;
        NewsWidget[i]->SetImage(database->ReturnImage("Новини проекту","Картинка"," WHERE ID=\""+Result[i][3]+"\""));
        NewsWidget[i]->SetData(Result[i][0],Result[i][3],Result[i][1],Result[i][2]);
        ui->MainTableForWidgets->insertRow(ui->MainTableForWidgets->rowCount());
        ui->MainTableForWidgets->setCellWidget(ui->MainTableForWidgets->rowCount()-1,ui->MainTableForWidgets->columnCount()-1,NewsWidget[i]);
        ui->MainTableForWidgets->setRowHeight(ui->MainTableForWidgets->rowCount()-1,100);
    }
}
void MainWindow::MailAndApplication(){
    ui->lineEdit->setVisible(false);
    ui->widget->setVisible(false);
    ui->label->setVisible(false);
    for(int i=ui->MainTableForWidgets->rowCount()-1;i>-1;--i){
        ui->MainTableForWidgets->removeRow(i);
    }
    if(log->GetAccountName()=="admin")ui->ChangeNews->setVisible(false);
    Job.clear();
    QVector<QVector<QString>>Result;
    if(Mode=="Employer"){
        Result=database->SelectRequest("SELECT [Здобувач].[ПІБ],[Вакансії].[Посада],[Заявки].[Текст заявки],[Заявки].[Відповідь здобувачеві],[Здобувач].[ID],[Заявки].[ID] "
                                       "FROM [Заявки] "
                                       "INNER JOIN [Здобувач] ON [Здобувач].[ID]=[Заявки].[Здобувач] "
                                       "INNER JOIN [Вакансії] ON [Вакансії].[ID]=[Заявки].[Посада] "
                                       "INNER JOIN [Компанія] ON [Компанія].[ID]=[Вакансії].[Компанія] "
                                       "WHERE [Компанія].[Назва компанії]=\""+log->GetAccountName()+"\""
                                            "AND [Заявки].[Вилучено]=\"false\" "
                                       "ORDER BY [Заявки].[ID] DESC",6);
        Filled="JobApplications Employer";
    }
    else if(Mode=="JobSeeker"){
        Result=database->SelectRequest("SELECT [Компанія].[Назва компанії],[Вакансії].[Посада],[Заявки].[Текст заявки],[Заявки].[Відповідь здобувачеві] "
                                       "FROM [Заявки] "
                                       "INNER JOIN [Здобувач] ON [Здобувач].[ID]=[Заявки].[Здобувач] "
                                       "INNER JOIN [Вакансії] ON [Вакансії].[ID]=[Заявки].[Посада] "
                                       "INNER JOIN [Компанія] ON [Компанія].[ID]=[Вакансії].[Компанія] "
                                       "WHERE [Здобувач].[Email]=\""+log->GetAccountName()+"\" "
                                       "ORDER BY [Заявки].[ID] DESC",4);
        Filled="JobApplications JobSeeker";
    }
    for(int i=0;i<Result.length();++i){
        Job<<new JobApplications;
        if(Mode=="Employer"){
            Job[i]->SetFirstBlock("Здобувач:",Result[i][0]);
            Job[i]->SetId(Result[i][4]);
        }else if(Mode=="JobSeeker")Job[i]->SetFirstBlock("Компанія:",Result[i][0]);
        Job[i]->SetPosition(Result[i][1]);
        Job[i]->SetMainText(Result[i][2],Result[i][3]);
        ui->MainTableForWidgets->insertRow(ui->MainTableForWidgets->rowCount());
        ui->MainTableForWidgets->setCellWidget(ui->MainTableForWidgets->rowCount()-1,ui->MainTableForWidgets->columnCount()-1,Job[i]);
        ui->MainTableForWidgets->setRowHeight(ui->MainTableForWidgets->rowCount()-1,120);
    }
}
MainWindow::~MainWindow(){
    delete ui;
}
void MainWindow::on_HomePage_clicked(){
    HomePage();
}
void MainWindow::on_HomePage_2_clicked(){
    HomePage();
}
void MainWindow::on_CheckJobApplications_clicked(){
    MailAndApplication();
}
void MainWindow::on_Mail_clicked(){
    MailAndApplication();
}
void MainWindow::on_AddVacancy_clicked(){
    delete database;
    vacancy->SetCompanyName(log->GetAccountName());
    close();
    vacancy->show();
    vacancy->installEventFilter(this);
}
void MainWindow::on_PrivateOffice_2_clicked(){
    QVector<QVector<QString>>Result=database->SelectRequest("SELECT [Назва компанії],[Email],[Телефон],[Сайт компанії],[Коротко про компанію],[ID] "
                                                            "FROM [Компанія] "
                                                            "WHERE [Компанія].[Назва компанії]=\""+log->GetAccountName()+"\"",6);
    QByteArray temp=database->ReturnImage("Компанія","Логотип"," WHERE ID=\""+Result[0][5]+"\"");
    delete database;
    office=new PrivateOffice();
    office->installEventFilter(this);
    office->SetCompanyData(Result[0][0],Result[0][1],Result[0][2],Result[0][3],Result[0][4],temp);
    close();
    office->show();
}
void MainWindow::SetFindEmployerData(QVector<QVector<QString>>Result){
    for(int i=ui->MainTableForWidgets->rowCount()-1;i>-1;--i){
        ui->MainTableForWidgets->removeRow(i);
    }
    Employer.clear();
    for(int i=0;i<Result.length();++i){
        Employer<<new FindEmployer;
        Employer[i]->SetData(Result[i][0],Result[i][1],Result[i][2],Result[i][3],Result[i][4]);
        Employer[i]->SetID(Result[i][5]);
        ui->MainTableForWidgets->insertRow(ui->MainTableForWidgets->rowCount());
        ui->MainTableForWidgets->setCellWidget(ui->MainTableForWidgets->rowCount()-1,ui->MainTableForWidgets->columnCount()-1,Employer[i]);
        ui->MainTableForWidgets->setRowHeight(ui->MainTableForWidgets->rowCount()-1,123);
    }
}
void MainWindow::on_FindEmployer_clicked(){
    ui->lineEdit->setVisible(true);
    ui->widget->setVisible(true);
    ui->label->setVisible(true);
    ui->lineEdit->setText("");
    if(log->GetAccountName()=="admin")ui->ChangeNews->setVisible(false);
    database->RequestForDatabase("DELETE FROM [Заявки]"
                                 "WHERE [Заявки].[Дата написання заявки]<date('now','-5 days')");
    Filled="FindEmployer";
    QVector<QVector<QString>>Result=database->SelectRequest("SELECT [Компанія].[Назва компанії],[Вакансії].[Вимоги],[Вакансії].[Опис],[Вакансії].[Посада],[Вакансії].[Зарплата],[Компанія].[ID] "
                                                            "FROM [Вакансії] "
                                                            "INNER JOIN [Компанія] ON [Компанія].[ID]=[Вакансії].[Компанія] "
                                                            "WHERE NOT EXISTS ("
                                                                "SELECT * "
                                                                "FROM [Заявки] "
                                                                "INNER JOIN [Здобувач] ON [Здобувач].[ID]=[Заявки].[Здобувач] "
                                                                "WHERE [Вакансії].[ID]=[Заявки].[Посада] "
                                                                    "AND [Здобувач].[Email]=\""+log->GetAccountName()+"\""
                                                            ") "
                                                            "ORDER BY [Вакансії].[ID] DESC",6);
    SetFindEmployerData(Result);
}
void MainWindow::on_PrivateOffice_clicked(){
    QVector<QVector<QString>>Result=database->SelectRequest("SELECT [Здобувач].[ПІБ],[Здобувач].[Email],[Здобувач].[Телефон],[Здобувач].[Коротко про себе],[Здобувач].[ID],[Рівень освіти].[Освіта] "
                                                            "FROM [Здобувач] "
                                                            "INNER JOIN [Рівень освіти] ON [Рівень освіти].[ID]=[Здобувач].[Рівень освіти] "
                                                            "WHERE [Здобувач].[Email]=\""+log->GetAccountName()+"\"",6);
    QByteArray temp=database->ReturnImage("Здобувач","Фото"," WHERE ID=\""+Result[0][4]+"\"");
    office=new PrivateOffice();
    office->installEventFilter(this);
    office->SetUserAdditionalData(Result[0][5],
            database->SelectRequest("SELECT [Попередні місця роботи].[ID],[Попередні місця роботи].[Дата прийняття на роботу],[Попередні місця роботи].[Дата звільнення],[Попередні місця роботи].[Назва компанії],[Попередні місця роботи].[Посада],[Попередні місця роботи].[Місцезнаходження компанії],[Попередні місця роботи].[Посадові обовязки та досягнення] "
                                    "FROM [Попередні місця роботи] "
                                    "INNER JOIN [Здобувач] ON [Здобувач].[ID]=[Попередні місця роботи].[Здобувач] "
                                    "WHERE [Здобувач].[Email]=\""+Result[0][1]+"\"",7),
            database->SelectRequest("SELECT [Освіта].[ID],[Освіта].[Рік початку навчання],[Освіта].[Рік завершення навчання],[Освіта].[Навчальний заклад],[Освіта].[Кваліфікація] "
                                    "FROM [Освіта] "
                                    "INNER JOIN [Здобувач] ON [Здобувач].[ID]=[Освіта].[Здобувач] "
                                    "WHERE [Здобувач].[Email]=\""+Result[0][1]+"\"",5));
    delete database;
    office->SetJobSeekerData(Result[0][0],Result[0][1],Result[0][2],Result[0][3],temp);
    close();
    office->show();
}
void MainWindow::FullSizeWidget(QWidget *WidgetFromTable,QString Mode,QSize size){
    CentralWidget=new QWidget();
    QVBoxLayout* box = new QVBoxLayout;
    box->addWidget(WidgetFromTable);
    WidgetFromTable->setMinimumSize(size);
    if(Mode=="Employer"){
        button=new QPushButton("Написати лист");
        box->addWidget(button);
        connect(button,SIGNAL(clicked()),this,SLOT(StartCreateMail()),Qt::UniqueConnection);
        button1=new QPushButton("Вилучити лист");
        box->addWidget(button1);
        connect(button1,SIGNAL(clicked()),this,SLOT(AskDelete()),Qt::UniqueConnection);
    }else if(Mode=="Vacancy"){
        button=new QPushButton("Змінити информацию");
        box->addWidget(button);
        connect(button,SIGNAL(clicked()),this,SLOT(StartChangeVacancy()),Qt::UniqueConnection);
        button2=new QPushButton("Вилучити вакансию");
        box->addWidget(button2);
        connect(button2,SIGNAL(clicked()),this,SLOT(AskDelete()),Qt::UniqueConnection);
    }else if(Mode=="JobSeeker"){
        button=new QPushButton("Вилучити лист");
        box->addWidget(button);
        connect(button,SIGNAL(clicked()),this,SLOT(AskDelete()),Qt::UniqueConnection);
    }else if(Mode=="EmployerMail"){
        button=new QPushButton("Написати лист");
        box->addWidget(button);
        connect(button,SIGNAL(clicked()),this,SLOT(StartCreateMail()),Qt::UniqueConnection);
    }
    CentralWidget->setLayout(box);
    CentralWidget->setWindowTitle("Перегляд");
    CentralWidget->show();
    QPalette pal;
    QPixmap map;
    map.load(":/image/images/HelpBackground.png");
    map=map.scaled(CentralWidget->width(),CentralWidget->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pal.setBrush(CentralWidget->backgroundRole(),QBrush(map));
    CentralWidget->setPalette(pal);
    CentralWidget->setAutoFillBackground(true);
}
void MainWindow::DeleteMailC(){
    disconnect(button,SIGNAL(clicked()),this,SLOT(StartCreateMail()));
    disconnect(Yes,SIGNAL(clicked()),this,SLOT(DeleteMailC()));
    mainWindow1->close();
    database->RequestForDatabase("UPDATE [Заявки] "
                                 "SET [Вилучено]=\"true\" "
                                 "WHERE [Заявки].[Здобувач]=\""+DataToCreateMail[4]+"\" "
                                 "AND [Заявки].[Посада]=("
                                                               "SELECT [Вакансії].[ID] "
                                                               "FROM [Вакансії] "
                                                               "INNER JOIN [Компанія] ON [Компанія].[ID]=[Вакансії].[Компанія] "
                                                               "WHERE [Вакансії].[Посада]=\""+DataToCreateMail[2]+"\" "
                                                                   "AND [Компанія].[Назва компанії]=\""+DataToCreateMail[1].toLower()+"\""
                                                           ")");
    CentralWidget->close();
    MailAndApplication();
}
void MainWindow::DeleteMailJS(){
    disconnect(Yes,SIGNAL(clicked()),this,SLOT(DeleteMailJS()));
    mainWindow1->close();
    database->RequestForDatabase("DELETE FROM [Заявки] "
                                 "WHERE [Заявки].[Здобувач]=("
                                                                 "SELECT [ID] "
                                                                 "FROM [Здобувач] "
                                                                 "WHERE [Здобувач].[Email]=\""+DataToCreateMail[1]+"\""
                                                            ") "
                                "AND [Заявки].[Посада]=("
                                                                "SELECT [Вакансії].[ID] "
                                                                "FROM [Вакансії] "
                                                                "INNER JOIN [Компанія] ON [Компанія].[ID]=[Вакансії].[Компанія] "
                                                                "WHERE [Вакансії].[Посада]=\""+DataToCreateMail[2]+"\" "
                                                                    "AND [Компанія].[Назва компанії]=\""+DataToCreateMail[3].toLower()+"\""
                                                         ")");
    CentralWidget->close();
    MailAndApplication();
}
void MainWindow::StartCreateMail(){
    disconnect(button,SIGNAL(clicked()),this,SLOT(StartCreateMail()));
    delete database;
    mail=new CreateMail();
    if(DataToCreateMail.length()==4)DataToCreateMail.append("");
    mail->SetData(DataToCreateMail[0],DataToCreateMail[1],DataToCreateMail[2],DataToCreateMail[3],DataToCreateMail[4]);
    CentralWidget->close();
    close();
    mail->show();
    mail->installEventFilter(this);
}
bool MainWindow::eventFilter(QObject *object, QEvent *event){
    if(object==office){
        if(event->type()==QCloseEvent::Close){
            if(office->GetLogOut())ShowLoginForm1();
            else{
                OpenMainWindow();
            }
        }
    }else if(object==mail||object==news||object==vacancy||object==resume||object==AdminEdit){
        if(event->type()==QCloseEvent::Close){
            OpenMainWindow();
        }
    }else if (object == this->ui->MainTableForWidgets->viewport()){
        if(event->type()==QEvent::MouseButtonDblClick){
            QMouseEvent *ms = static_cast<QMouseEvent *>(event);
            if(ms->buttons() & Qt::LeftButton){
                QItemSelectionModel *select=ui->MainTableForWidgets->selectionModel();
                int row=select->currentIndex().row();
                if(Filled=="JobApplications JobSeeker"){
                    JobApplications *Temp=new JobApplications();
                    Temp->operator=(*Job[row]);
                    Temp->SetInternalData();
                    DataToCreateMail.clear();
                    DataToCreateMail<<"";
                    DataToCreateMail.append(Temp->GetData(log->GetAccountName()));
                    FullSizeWidget(Temp,"JobSeeker",QSize(350,435));
                }else if(Filled=="JobApplications Employer"){
                    TempJob->operator=(*Job[row]);
                    TempJob->SetInternalData();
                    connect(TempJob,SIGNAL(OpenInfo()),this,SLOT(OpenInfo()),Qt::UniqueConnection);
                    DataToCreateMail.clear();
                    DataToCreateMail<<"Работодатель";
                    DataToCreateMail.append(TempJob->GetData(log->GetAccountName()));
                    DataToCreateMail.append(TempJob->GetId());
                    QVector<QVector<QString>>Result=database->SelectRequest("SELECT [Резюме].[Бажана посада],[Резюме].[Бажана зарплатня],[Резюме].[Короткий опис] "
                                                                            "FROM [Резюме] "
                                                                            "WHERE [Резюме].[Здобувач]=\""+TempJob->GetId()+"\"",3);
                    QByteArray FileDataBD;
                    if(Result.length()==0){
                        QVector<QString>Temp;
                        for(int i=0;i<3;++i){
                            Temp<<"";
                        }
                        Result<<Temp;
                    }else{
                        FileDataBD=database->ReturnImage("Резюме","Резюме"," WHERE [Резюме].[Здобувач]=\""+TempJob->GetId()+"\"");
                    }
                    TempJob->SetResumeData(Result[0][0],Result[0][1],Result[0][2],FileDataBD);
                    FullSizeWidget(TempJob,"Employer",QSize(350,435));
                }else if(Filled=="News"){
                    News *Temp=new News();
                    Temp->operator=(*NewsWidget[row]);
                    Temp->SetInternalData();
                    FullSizeWidget(Temp,"",QSize(350,339));
                }else if(Filled=="FindEmployer"){
                    TempEmplJS->operator=(*Employer[row]);
                    TempEmplJS->SetInternalData();
                    connect(TempEmplJS,SIGNAL(OpenInfo()),this,SLOT(OpenInfo()),Qt::UniqueConnection);
                    DataToCreateMail.clear();
                    DataToCreateMail<<"Здобувач";
                    DataToCreateMail.append(TempEmplJS->GetData(log->GetAccountName()));
                    FullSizeWidget(TempEmplJS,"EmployerMail",QSize(350,631));
                }else if(Filled=="CheckVacancy"){
                    TempEmpl->operator=(*Employer[row]);
                    TempEmpl->SetInternalData();
                    TempEmpl->AllowEdit();
                    FullSizeWidget(TempEmpl,"Vacancy",QSize(350,631));
                }
            }
        }
    }
    return QObject::eventFilter(object, event);
}
void MainWindow::OpenInfo(){
    auto obj=QObject::sender();
    if(obj==TempJob){
        QVector<QVector<QString>>Result=database->SelectRequest("SELECT [Здобувач].[ПІБ],[Здобувач].[Email],[Здобувач].[Телефон],[Здобувач].[Коротко про себе],[Рівень освіти].[Освіта] "
                                                                "FROM [Здобувач] "
                                                                "INNER JOIN [Рівень освіти] ON [Рівень освіти].[ID]=[Здобувач].[Рівень освіти] "
                                                                "WHERE [Здобувач].[ID]=\""+TempJob->GetId()+"\"",5);
        QByteArray temp=database->ReturnImage("Здобувач","Фото"," WHERE ID=\""+TempJob->GetId()+"\"");
        InfoOffice=new PrivateOffice();
        InfoOffice->OnlyRead("Company");
        InfoOffice->SetUserAdditionalData(Result[0][4],
                database->SelectRequest("SELECT [Попередні місця роботи].[ID],[Попередні місця роботи].[Дата прийняття на роботу],[Попередні місця роботи].[Дата звільнення],[Попередні місця роботи].[Назва компанії],[Попередні місця роботи].[Посада],[Попередні місця роботи].[Місцезнаходження компанії],[Попередні місця роботи].[Посадові обовязки та досягнення] "
                                        "FROM [Попередні місця роботи] "
                                        "INNER JOIN [Здобувач] ON [Здобувач].[ID]=[Попередні місця роботи].[Здобувач] "
                                        "WHERE [Здобувач].[Email]=\""+Result[0][1]+"\"",7),
                database->SelectRequest("SELECT [Освіта].[ID],[Освіта].[Рік початку навчання],[Освіта].[Рік завершення навчання],[Освіта].[Навчальний заклад],[Освіта].[Кваліфікація] "
                                        "FROM [Освіта] "
                                        "INNER JOIN [Здобувач] ON [Здобувач].[ID]=[Освіта].[Здобувач] "
                                        "WHERE [Здобувач].[Email]=\""+Result[0][1]+"\"",5));
        InfoOffice->SetJobSeekerData(Result[0][0],Result[0][1],Result[0][2],Result[0][3],temp);
        InfoOffice->show();
    }else if(obj==TempEmplJS){
        QVector<QVector<QString>>Result=database->SelectRequest("SELECT [Назва компанії],[Email],[Телефон],[Сайт компанії],[Коротко про компанію] "
                                                                "FROM [Компанія] "
                                                                "WHERE [Компанія].[ID]=\""+TempEmplJS->GetID()+"\"",5);
        QByteArray temp=database->ReturnImage("Компанія","Логотип"," WHERE ID=\""+TempEmplJS->GetID()+"\"");
        InfoOffice=new PrivateOffice();
        InfoOffice->OnlyRead();
        InfoOffice->SetCompanyData(Result[0][0],Result[0][1],Result[0][2],Result[0][3],Result[0][4],temp);
        InfoOffice->show();
    }
}
void MainWindow::ShowLoginForm(){
    delete database;
    ShowLoginForm1();
}
void MainWindow::ShowLoginForm1(){
    delete log;
    log=new Login();
    connect(log,SIGNAL(Accessed()),this,SLOT(OpenMainWindow()),Qt::UniqueConnection);
    close();
    log->show();
}
void MainWindow::DeleteAccount(){
    disconnect(Yes,SIGNAL(clicked()),this,SLOT(StartDeleteVacancy()));
    disconnect(No,SIGNAL(clicked()),this,SLOT(BreakDelete()));
    mainWindow1->close();
    if(Mode=="JobSeeker"){
        database->RequestForDatabase("DELETE FROM [Заявки] "
                                     "WHERE [Заявки].[ID] IN ("
                                       "SELECT [Заявки].[ID] "
                                       "FROM [Заявки] "
                                       "INNER JOIN [Здобувач] ON [Здобувач].[ID]=[Заявки].[Здобувач] "
                                       "WHERE [Здобувач].[Email]=\""+log->GetAccountName()+"\""
                                     ");");
        database->RequestForDatabase("DELETE FROM [Паролі здобувачів] "
                                     "WHERE [Паролі здобувачів].[ID] IN ("
                                       "SELECT [Паролі здобувачів].[ID] "
                                       "FROM [Паролі здобувачів] "
                                       "INNER JOIN [Здобувач] ON [Здобувач].[ID]=[Паролі здобувачів].[Здобувач] "
                                       "WHERE [Здобувач].[Email]=\""+log->GetAccountName()+"\""
                                     ");");
        database->RequestForDatabase("DELETE FROM [Попередні місця роботи] "
                                     "WHERE [Попередні місця роботи].[ID] IN ("
                                       "SELECT [Попередні місця роботи].[ID] "
                                       "FROM [Попередні місця роботи] "
                                       "INNER JOIN [Здобувач] ON [Здобувач].[ID]=[Попередні місця роботи].[Здобувач] "
                                       "WHERE [Здобувач].[Email]=\""+log->GetAccountName()+"\""
                                     ");");
        database->RequestForDatabase("DELETE FROM [Освіта] "
                                     "WHERE [Освіта].[ID] IN ("
                                       "SELECT [Освіта].[ID] "
                                       "FROM [Освіта] "
                                       "INNER JOIN [Здобувач] ON [Здобувач].[ID]=[Освіта].[Здобувач] "
                                       "WHERE [Здобувач].[Email]=\""+log->GetAccountName()+"\""
                                     ");");
        database->RequestForDatabase("DELETE FROM [Здобувач] "
                                     "WHERE [Здобувач].[Email]=\""+log->GetAccountName()+"\"");
    }else if(Mode=="Employer"){
        database->RequestForDatabase("DELETE FROM [Заявки] "
                                     "WHERE [Заявки].[ID] IN ("
                                       "SELECT [Заявки].[ID] "
                                       "FROM [Заявки] "
                                       "INNER JOIN [Вакансії] ON [Вакансії].[ID]=[Заявки].[Посада] "
                                       "INNER JOIN [Компанія] ON [Компанія].[ID]=[Вакансії].[Компанія] "
                                       "WHERE [Компанія].[Назва компанії]=\""+log->GetAccountName()+"\""
                                     ");");
        database->RequestForDatabase("DELETE FROM [Вакансії] "
                                     "WHERE [Вакансії].[ID] IN ("
                                       "SELECT [Вакансії].[ID] "
                                       "FROM [Вакансії] "
                                       "INNER JOIN [Компанія] ON [Компанія].[ID]=[Вакансії].[Компанія] "
                                       "WHERE [Компанія].[Назва компанії]=\""+log->GetAccountName()+"\""
                                     ");");
        database->RequestForDatabase("DELETE FROM [Паролі компаній] "
                                     "WHERE [Паролі компаній].[ID] IN ("
                                       "SELECT [Паролі компаній].[ID] "
                                       "FROM [Паролі компаній] "
                                       "INNER JOIN [Компанія] ON [Компанія].[ID]=[Паролі компаній].[Компанія] "
                                       "WHERE [Компанія].[Назва компанії]=\""+log->GetAccountName()+"\""
                                     ");");
        database->RequestForDatabase("DELETE FROM [Компанія] "
                                     "WHERE [Компанія].[Назва компанії]=\""+log->GetAccountName()+"\"");
    }
    ShowLoginForm();
}
void MainWindow::on_ChangeNews_clicked(){
    delete database;
    news=new ChangeNews();
    news->installEventFilter(this);
    news->SetNews(NewsWidget);
    close();
    news->show();
}
void MainWindow::on_Vacancy_clicked(){
    ui->lineEdit->setVisible(false);
    ui->widget->setVisible(false);
    ui->label->setVisible(false);
    for(int i=ui->MainTableForWidgets->rowCount()-1;i>-1;--i){
        ui->MainTableForWidgets->removeRow(i);
    }
    Employer.clear();
    Filled="CheckVacancy";
    QVector<QVector<QString>>Result=database->SelectRequest("SELECT [Компанія].[Назва компанії],[Вимоги],[Опис],[Посада],[Зарплата],[Вакансії].[ID] "
                                                            "FROM [Вакансії] "
                                                            "INNER JOIN [Компанія] ON [Компанія].[ID]=[Вакансії].[Компанія] "
                                                            "WHERE [Компанія].[Назва компанії]=\""+log->GetAccountName()+"\" "
                                                            "ORDER BY [Вакансії].[ID] DESC",6);
    for(int i=0;i<Result.length();++i){
        Employer<<new FindEmployer;
        Employer[i]->SetData(Result[i][0],Result[i][1],Result[i][2],Result[i][3],Result[i][4]);
        Employer[i]->Employer();
        Employer[i]->SetID(Result[i][5]);
        ui->MainTableForWidgets->insertRow(ui->MainTableForWidgets->rowCount());
        ui->MainTableForWidgets->setCellWidget(ui->MainTableForWidgets->rowCount()-1,ui->MainTableForWidgets->columnCount()-1,Employer[i]);
        ui->MainTableForWidgets->setRowHeight(ui->MainTableForWidgets->rowCount()-1,123);
    }
}
void MainWindow::StartChangeVacancy(){
    disconnect(button,SIGNAL(clicked()),this,SLOT(StartChangeVacancy()));
    CentralWidget->close();
    QVector<QString>Result=TempEmpl->GetData();
    database->RequestForDatabase("UPDATE [Вакансії] "
                                 "SET [Посада]=\""+Result[1]+"\","
                                     "[Вимоги]=\""+Result[3]+"\","
                                     "[Опис]=\""+Result[2]+"\","
                                     "[Зарплата]=\""+Result[0]+"\" "
                                 "WHERE [Вакансії].[ID]=\""+TempEmpl->GetID()+"\"");
    emit on_Vacancy_clicked();
}
void MainWindow::AskDelete(){
    hlayout=new QGridLayout();
    label=new QLabel("Ви впевнені?");
    mainWindow1=new QWidget();
    Yes=new QPushButton("Так");
    No=new QPushButton("Ні");
    hlayout->addWidget(label,0,0);
    hlayout->addWidget(Yes,1,0);
    hlayout->addWidget(No,1,1);
    auto obj=QObject::sender();
    if(obj==Delete)connect(Yes,SIGNAL(clicked()),this,SLOT(DeleteAccount()),Qt::UniqueConnection);
    else if(obj==button1){
        disconnect(button1,SIGNAL(clicked()),this,SLOT(AskDelete()));
        connect(Yes,SIGNAL(clicked()),this,SLOT(DeleteMailC()),Qt::UniqueConnection);
    }else if(obj==button){
        disconnect(button,SIGNAL(clicked()),this,SLOT(AskDelete()));
        connect(Yes,SIGNAL(clicked()),this,SLOT(DeleteMailJS()),Qt::UniqueConnection);
    }else if(obj==button2){
        disconnect(button2,SIGNAL(clicked()),this,SLOT(AskDelete()));
        connect(Yes,SIGNAL(clicked()),this,SLOT(StartDeleteVacancy()),Qt::UniqueConnection);
    }
    connect(No,SIGNAL(clicked()),this,SLOT(BreakDelete()),Qt::UniqueConnection);
    mainWindow1->setLayout(hlayout);
    mainWindow1->setWindowTitle("Видалення");
    mainWindow1->installEventFilter(this);
    mainWindow1->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    mainWindow1->show();
}
void MainWindow::BreakDelete(){
    mainWindow1->close();
}
void MainWindow::StartDeleteVacancy(){
    disconnect(Yes,SIGNAL(clicked()),this,SLOT(StartDeleteVacancy()));
    CentralWidget->close();
    mainWindow1->close();
    database->RequestForDatabase("DELETE FROM [Заявки] "
                                 "WHERE [Заявки].[ID] IN ("
                                   "SELECT [Заявки].[ID] "
                                   "FROM [Заявки] "
                                   "INNER JOIN [Вакансії] ON [Вакансії].[ID]=[Заявки].[Посада] "
                                   "WHERE [Вакансії].[ID]=\""+TempEmpl->GetID()+"\""
                                 ");");
    database->RequestForDatabase("DELETE FROM [Вакансії] "
                                 "WHERE [Вакансії].[ID]=\""+TempEmpl->GetID()+"\"");
    emit on_Vacancy_clicked();
}
void MainWindow::on_CheckStatistics_clicked(){
    user=new UserStatistics();
    user->LoadData(database->SelectRequest("SELECT [Дата реєстрації] "
                                           "FROM [Здобувач] "
                                           "WHERE [Дата реєстрації]>date('now','start of year')",1),
                   database->SelectRequest("SELECT [Дата реєстрації] "
                                           "FROM [Компанія] "
                                           "WHERE [Дата реєстрації]>date('now','start of year')",1));
    user->show();
}
void MainWindow::on_lineEdit_textChanged(const QString &arg1){
    if(arg1=="")on_FindEmployer_clicked();
    else{
        QButtonGroup group;
        QList<QRadioButton *> allButtons = ui->widget->findChildren<QRadioButton *>();
        for(int i=0;i<allButtons.size();++i){
            group.addButton(allButtons[i],i);
        }
        QVector<QVector<QString>>Result;
        if(group.checkedButton()->text()=="Пошук за зарплатою"){
            if(arg1[0]==">"||arg1[0]=="<"){
                QString temp;
                for(int i=0;i<arg1.length();++i){
                    if(i!=0)temp.append(arg1[i]);
                }
                Result=database->SelectRequest("SELECT [Компанія].[Назва компанії],[Вакансії].[Вимоги],[Вакансії].[Опис],[Вакансії].[Посада],[Вакансії].[Зарплата],[Компанія].[ID] "
                                               "FROM [Вакансії] "
                                               "INNER JOIN [Компанія] ON [Компанія].[ID]=[Вакансії].[Компанія] "
                                               "WHERE NOT EXISTS ("
                                                   "SELECT * "
                                                   "FROM [Заявки] "
                                                   "INNER JOIN [Здобувач] ON [Здобувач].[ID]=[Заявки].[Здобувач] "
                                                   "WHERE [Вакансії].[ID]=[Заявки].[Посада] "
                                                       "AND [Здобувач].[Email]=\""+log->GetAccountName()+"\""
                                               ") "
                                               "AND [Вакансії].[Зарплата]"+arg1[0]+"\""+temp+"\" "
                                               "ORDER BY [Вакансії].[ID] DESC",6);
            }else{
                Result=database->SelectRequest("SELECT [Компанія].[Назва компанії],[Вакансії].[Вимоги],[Вакансії].[Опис],[Вакансії].[Посада],[Вакансії].[Зарплата],[Компанія].[ID] "
                                               "FROM [Вакансії] "
                                               "INNER JOIN [Компанія] ON [Компанія].[ID]=[Вакансії].[Компанія] "
                                               "WHERE NOT EXISTS ("
                                                   "SELECT * "
                                                   "FROM [Заявки] "
                                                   "INNER JOIN [Здобувач] ON [Здобувач].[ID]=[Заявки].[Здобувач] "
                                                   "WHERE [Вакансії].[ID]=[Заявки].[Посада] "
                                                       "AND [Здобувач].[Email]=\""+log->GetAccountName()+"\""
                                               ") "
                                               "AND [Вакансії].[Зарплата]=\""+arg1+"\" "
                                               "ORDER BY [Вакансії].[ID] DESC",6);
            }
        }else{
            QVector<QVector<QString>>Temp=database->SelectRequest("SELECT [Компанія].[Назва компанії],[Вакансії].[Вимоги],[Вакансії].[Опис],[Вакансії].[Посада],[Вакансії].[Зарплата],[Компанія].[ID] "
                                                                  "FROM [Вакансії] "
                                                                  "INNER JOIN [Компанія] ON [Компанія].[ID]=[Вакансії].[Компанія] "
                                                                  "WHERE NOT EXISTS ("
                                                                      "SELECT * "
                                                                      "FROM [Заявки] "
                                                                      "INNER JOIN [Здобувач] ON [Здобувач].[ID]=[Заявки].[Здобувач] "
                                                                      "WHERE [Вакансії].[ID]=[Заявки].[Посада] "
                                                                          "AND [Здобувач].[Email]=\""+log->GetAccountName()+"\""
                                                                  ") "
                                                                  "ORDER BY [Вакансії].[ID] DESC",6);
            int id;
            if(group.checkedButton()->text()=="Пошук за назвою вакансії")id=3;
            else id=0;
            foreach(QVector<QString> i,Temp){
                if(database->SelectRequest("SELECT \""+i[id].toUpper()+"\" LIKE '%"+arg1.toUpper()+"%'",1)[0][0]=="1"){
                    Result<<i;
                }
            }
        }
        SetFindEmployerData(Result);
    }
}
void MainWindow::on_AddResume_clicked(){
    QVector<QVector<QString>>Result=database->SelectRequest("SELECT [ID] "
                                                            "FROM [Здобувач] "
                                                            "WHERE [Здобувач].[Email]=\""+log->GetAccountName()+"\"",1);
    delete database;
    resume=new Resume();
    resume->installEventFilter(this);
    resume->SetData(Result[0][0]);
    close();
    resume->show();
}
void MainWindow::on_RedactVacancy_clicked(){
    delete database;
    AdminEdit=new AdminEditVacancy();
    AdminEdit->installEventFilter(this);
    close();
    AdminEdit->show();
}
