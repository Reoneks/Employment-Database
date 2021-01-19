#include "resume.h"
#include "ui_resume.h"
#include "database.h"
Resume::Resume(QWidget *parent):QMainWindow(parent),ui(new Ui::Resume){
    ui->setupUi(this);
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Резюме");
    QPalette pal;
    QPixmap map;
    map.load(":/image/images/HelpBackground.png");
    map=map.scaled(540,318,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pal.setBrush(ui->centralwidget->backgroundRole(),QBrush(map));
    ui->centralwidget->setPalette(pal);
    ui->centralwidget->setAutoFillBackground(true);
    ui->Job->setTabChangesFocus(true);
    ui->ShortText->setTabChangesFocus(true);
    ui->Ok->setVisible(false);
    ui->MoneyText->setVisible(false);
    ui->MoneyText->setReadOnly(true);
    ui->textBrowser_5->setReadOnly(true);
    ui->textBrowser_6->setReadOnly(true);
    ui->textBrowser_16->setReadOnly(true);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Ок");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Скасувати");
    connect(ui->Ok,SIGNAL(clicked()),this,SLOT(on_buttonBox_rejected()),Qt::UniqueConnection);
    Mode="";
    ui->DownloadResume->setStyleSheet("#DownloadResume{border-image: url(:/image/images/Download.png);} QToolTip{border: 2px solid darkkhaki; padding: 5px; border-radius: 1px;}");
}
Resume::~Resume(){
    delete ui;
}
void Resume::ReadOnly(){
    ui->buttonBox->setVisible(false);
    ui->Ok->setVisible(true);
    ui->Money->setVisible(false);
    ui->MoneyText->setVisible(true);
    ui->LoadResume->setVisible(false);
    ui->Job->setReadOnly(true);
    ui->ShortText->setReadOnly(true);
}
void Resume::SetData(QString ID){
    this->ID=ID;
    Database *database=new Database();
    QVector<QVector<QString>>Result=database->SelectRequest("SELECT [Резюме].[Бажана посада],[Резюме].[Бажана зарплатня],[Резюме].[Короткий опис] "
                                                            "FROM [Резюме] "
                                                            "WHERE [Резюме].[Здобувач]=\""+ID+"\"",3);
    if(Result.length()!=0){
        ui->Job->setPlainText(Result[0][0]);
        ui->Money->setValue(Result[0][1].toInt());
        ui->ShortText->setPlainText(Result[0][2]);
        QByteArray FileDataDb=database->ReturnImage("Резюме","Резюме"," WHERE [Резюме].[Здобувач]=\""+ID+"\"");
        if(FileDataDb.length()==0){
            ui->DownloadResume->setStyleSheet("#DownloadResume{border-image: url(:/image/images/DownloadCancel.png);} QToolTip{border: 2px solid darkkhaki; padding: 5px; border-radius: 1px;}");
            ui->DownloadResume->setToolTip("Файл не був завантажений");
            ui->DownloadResume->setEnabled(false);
        }
    }else{
        ui->DownloadResume->setStyleSheet("#DownloadResume{border-image: url(:/image/images/DownloadCancel.png);} QToolTip{border: 2px solid darkkhaki; padding: 5px; border-radius: 1px;}");
        ui->DownloadResume->setToolTip("Файл не був завантажений");
        ui->DownloadResume->setEnabled(false);
    }
    delete database;
}
void Resume::SetData(QString Job,QString Money,QString Text,QByteArray FileData){
    ui->Job->setPlainText(Job);
    ui->MoneyText->setPlainText(Money);
    ui->ShortText->setPlainText(Text);
    this->FileData=FileData;
    if(FileData.length()==0){
        ui->DownloadResume->setStyleSheet("#DownloadResume{border-image: url(:/image/images/DownloadCancel.png);} QToolTip{border: 2px solid darkkhaki; padding: 5px; border-radius: 1px;}");
        ui->DownloadResume->setToolTip("Файл не був завантажений");
        ui->DownloadResume->setEnabled(false);
    }
    Mode="ReadOnly";
}
void Resume::on_buttonBox_accepted(){
    Database *database=new Database();
    QVector<QVector<QString>>Temp=database->SelectRequest("SELECT [ID] FROM [Резюме] WHERE [Резюме].[Здобувач]=\""+ID+"\"",1);
    QByteArray FileDataDb;
    if(Temp.length()!=0)FileDataDb=database->ReturnImage("Резюме","Резюме"," WHERE [Резюме].[Здобувач]=\""+ID+"\"");
    database->RequestForDatabase("REPLACE INTO [Резюме]([Здобувач],[Бажана посада],[Бажана зарплатня],[Короткий опис])"
                                 "VALUES(\""+
                                     ID+"\",\""+
                                     ui->Job->toPlainText()+"\",\""+
                                     QString::number(ui->Money->value())+"\",\""+
                                     ui->ShortText->toPlainText()+"\""
                                 ");");
    if(array.length()!=0)database->ImageAddRequest(array,"Резюме","Резюме"," WHERE [Резюме].[Здобувач]=\""+ID+"\"");
    else if(FileDataDb.length()!=0)database->ImageAddRequest(FileDataDb,"Резюме","Резюме"," WHERE [Резюме].[Здобувач]=\""+ID+"\"");
    delete database;
    close();
}
void Resume::on_buttonBox_rejected(){
    close();
}
void Resume::on_LoadResume_clicked(){
    QString fileName = QFileDialog::getOpenFileName(this,tr("Load document"),"",tr("Document (*.doc;*.docx);;All Files (*)"));
    if(fileName!=""){
        QFile file(fileName);
        file.open(QIODevice::ReadOnly);
        array.clear();
        array = file.readAll();
        if(array.length()!=0){
            ErrorMessage("Файл успішно збережений",":/image/images/Ok.ico","Успіх");
        }else{
            ErrorMessage("Помилка збереження файлу",":/image/images/Error.ico","Помилка");
        }
        file.close();
    }else{
        ErrorMessage("Помилка збереження файлу",":/image/images/Error.ico","Помилка");
    }
}
void Resume::on_DownloadResume_clicked(){
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save document"),"",tr("*.docx"));
        if(fileName!=""){
            QFile file(fileName);
            if(!file.open(QIODevice::WriteOnly)){
                ui->DownloadResume->setStyleSheet("#DownloadResume{border-image: url(:/image/images/DownloadCancel.png);} QToolTip{border: 2px solid darkkhaki; padding: 5px; border-radius: 1px;}");
                ui->DownloadResume->setToolTip("Помилка збереження файлу");
            }else{
                if(Mode=="ReadOnly"){
                    file.write(FileData);
                }else{
                    Database *database=new Database();
                    QByteArray FileDataDB=database->ReturnImage("Резюме","Резюме"," WHERE [Резюме].[Здобувач]=\""+ID+"\"");
                    delete database;
                    file.write(FileDataDB);
                }
                file.close();
                ui->DownloadResume->setStyleSheet("#DownloadResume{border-image: url(:/image/images/DownloadAccept.png);} QToolTip{border: 2px solid darkkhaki; padding: 5px; border-radius: 1px;}");
                ui->DownloadResume->setToolTip("Файл успішно збережений");
            }
        }else{
            ui->DownloadResume->setStyleSheet("#DownloadResume{border-image: url(:/image/images/DownloadCancel.png);} QToolTip{border: 2px solid darkkhaki; padding: 5px; border-radius: 1px;}");
            ui->DownloadResume->setToolTip("Помилка збереження файлу");
        }
}
void Resume::ErrorMessage(QString Error, QString Icon, QString Title){
    msgBox=new QMessageBox();
    msgBox->setText(Error);
    msgBox->setWindowIcon(QIcon(Icon));
    msgBox->setWindowTitle(Title);
    msgBox->show();
}
