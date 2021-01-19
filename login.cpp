#include "login.h"
#include "ui_login.h"
#include "database.h"
Login::Login(QWidget *parent):QMainWindow(parent),ui(new Ui::Login){
    ui->setupUi(this);
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Увійти");
    QPalette pal;
    QPixmap map;
    map.load(":/image/images/MainwindowBackground.png");
    map=map.scaled(519,259,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pal.setBrush(ui->centralwidget->backgroundRole(),QBrush(map));
    ui->centralwidget->setPalette(pal);
    ui->centralwidget->setAutoFillBackground(true);
    ui->PasswordLine->setEchoMode(QLineEdit::Password);
    ui->stackedWidget->setCurrentIndex(0);
    ui->PasswordLine->installEventFilter(this);
    ui->LoginLine->installEventFilter(this);
    ui->ShowPassword->setStyleSheet("#ShowPassword{border-image: url(:/image/images/Eye.png) 0 0 0 0 stretch stretch;} QToolTip{border: 2px solid darkkhaki; padding: 5px; border-radius: 1px;}");
}
Login::~Login(){
    delete ui;
}
QString Login::GetMode(){
    return Mode;
}
QString Login::GetAccountName(){
    return NameOfAccount;
}
void Login::on_AccountLogin_clicked(){
    ui->stackedWidget->setCurrentIndex(1);
}
void Login::on_Ok_clicked(){
        QString TextFromLoginLine=ui->LoginLine->text().toLower();
        Database *database=new Database();
        QVector<QVector<QString>>Result=database->SelectRequest("SELECT [Компанія].[Назва компанії],[Паролі компаній].[Пароль] "
                                                                "FROM [Компанія] "
                                                                "INNER JOIN [Паролі компаній] ON [Паролі компаній].[Компанія]=[Компанія].[ID] "
                                                                "WHERE [Компанія].[Назва компанії]=\""+TextFromLoginLine+"\"",2);
        if(Result.length()!=1){
            Result=database->SelectRequest("SELECT [Здобувач].[Email],[Паролі здобувачів].[Пароль] "
                                           "FROM [Здобувач] "
                                           "INNER JOIN [Паролі здобувачів] ON [Паролі здобувачів].[Здобувач]=[Здобувач].[ID] "
                                           "WHERE [Здобувач].[Email]=\""+TextFromLoginLine+"\"",2);
            if(Result.length()!=1){
                ErrorMessage("Неправильно введені аккаунт або пароль");
                delete database;
                ui->LoginLine->setText("");
                ui->PasswordLine->setText("");
            }else if(Result[0][0]==TextFromLoginLine&&Result[0][1]==ui->PasswordLine->text()){
                NameOfAccount=TextFromLoginLine;
                Mode="JobSeeker";
                delete database;
                close();
                emit Accessed();
            }else{
                ErrorMessage("Неправильно введені аккаунт або пароль");
                delete database;
                ui->LoginLine->setText("");
                ui->PasswordLine->setText("");
            }
        }else if(Result[0][0]==TextFromLoginLine&&Result[0][1]==ui->PasswordLine->text()){
            NameOfAccount=TextFromLoginLine;
            Mode="Employer";
            delete database;
            close();
            emit Accessed();
        }else{
            ErrorMessage("Неправильно введені аккаунт або пароль");
            delete database;
            ui->LoginLine->setText("");
            ui->PasswordLine->setText("");
        }
}
void Login::ErrorMessage(QString Error){
    msgBox=new QMessageBox();
    msgBox->setText(Error);
    msgBox->setWindowIcon(QIcon(":/image/images/Error.ico"));
    msgBox->setWindowTitle("Помилка");
    msgBox->show();
}
void Login::on_Cancel_clicked(){
    ui->stackedWidget->setCurrentIndex(0);
    ui->LoginLine->setText("");
    ui->PasswordLine->setText("");
}
void Login::MainPage(){
    delete reg;
    ui->stackedWidget->setCurrentIndex(0);
    ui->LoginLine->setText("");
    ui->PasswordLine->setText("");
    show();
}
void Login::FinishRegistration(){
    NameOfAccount=reg->GetAccountName();
    delete reg;
    close();
    emit Accessed();
}
void Login::RegistrationStart(int Mode){
    if(RegMode!="Registration"){
        ui->stackedWidget->setCurrentIndex(1);
    }else{
        RegMode="";
        close();
        reg=new Registration();
        reg->SetMode(Mode);
        reg->show();
        connect(reg,SIGNAL(Finished()),this,SLOT(FinishRegistration()),Qt::UniqueConnection);
        connect(reg,SIGNAL(NotFinished()),this,SLOT(MainPage()),Qt::UniqueConnection);
    }
}
void Login::on_JobSeeker_clicked(){
    Mode="JobSeeker";
    RegistrationStart(0);
}
void Login::on_Employer_clicked(){
    Mode="Employer";
    RegistrationStart(1);
}
void Login::on_Registration_clicked(){
    RegMode="Registration";
    ui->stackedWidget->setCurrentIndex(2);
}
bool Login::eventFilter(QObject *object, QEvent *event){
    if(object==ui->LoginLine&&event->type()==QEvent::KeyPress){
        QKeyEvent *e = static_cast<QKeyEvent*>(event);
        if(e->key()==Qt::Key_Return||e->key()==Qt::Key_Enter){
            emit on_Ok_clicked();
        }
    }else if(object==ui->PasswordLine&&event->type()==QEvent::KeyPress){
        QKeyEvent *e = static_cast<QKeyEvent*>(event);
        if(e->key()==Qt::Key_Return||e->key()==Qt::Key_Enter){
            emit on_Ok_clicked();
        }
    }
    return QObject::eventFilter(object, event);
}
void Login::on_ShowPassword_clicked(){
    if(ui->PasswordLine->echoMode()==QLineEdit::Password){
        ui->PasswordLine->setEchoMode(QLineEdit::Normal);
        ui->ShowPassword->setToolTip("Приховати пароль");
    }
    else{
        ui->PasswordLine->setEchoMode(QLineEdit::Password);
        ui->ShowPassword->setToolTip("Показати пароль");
    }
}
