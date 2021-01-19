#ifndef JOBAPPLICATIONS_H
#define JOBAPPLICATIONS_H
#include <QWidget>
#include <QFileDialog>
namespace Ui {
class JobApplications;
}
class JobApplications : public QWidget{
    Q_OBJECT
    QString CompanyOrJobSeeker,Title,Position,MainText,MainText2,Text1,Text2,ID,Job,Money,Text;
    QByteArray FileData;
    public:
        explicit JobApplications(QWidget *parent = nullptr);
        void SetFirstBlock(QString CompanyOrJobSeeker,QString Title);
        void SetPosition(QString Position);
        void SetMainText(QString MainText, QString MainText2);
        void SetId(QString Id);
        void SetResumeData(QString Job,QString Money,QString Text,QByteArray FileData);
        QString GetId();
        void SetInternalData();
        QVector<QString> GetData(QString Account);
        JobApplications& operator = (const JobApplications& right){
            if(this==&right){
                return *this;
            }
            CompanyOrJobSeeker=right.CompanyOrJobSeeker;
            Title=right.Title;
            Position=right.Position;
            MainText=right.MainText;
            MainText2=right.MainText2;
            Text1=right.Text1;
            Text2=right.Text2;
            ID=right.ID;
            Job=right.Job;
            Money=right.Money;
            Text=right.Text;
            FileData=right.FileData;
            return *this;
        }
        ~JobApplications();
    signals:
        void OpenInfo();
    private slots:
        void on_pushButton_clicked();
        void on_DownloadDoc_clicked();
    private:
        Ui::JobApplications *ui;
};
#endif // JOBAPPLICATIONS_H
