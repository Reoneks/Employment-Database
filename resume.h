#ifndef RESUME_H
#define RESUME_H
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
namespace Ui {
class Resume;
}
class Resume : public QMainWindow{
    Q_OBJECT
    QString ID;
    QByteArray array,FileData;
    QString Mode;
    QMessageBox *msgBox;
    void ErrorMessage(QString Error,QString Icon,QString Title);
    public:
        explicit Resume(QWidget *parent = nullptr);
        void SetData(QString ID);
        void SetData(QString Job,QString Money,QString Text,QByteArray FileData);
        void ReadOnly();
        ~Resume();
    private slots:
        void on_buttonBox_accepted();
        void on_buttonBox_rejected();
        void on_LoadResume_clicked();
        void on_DownloadResume_clicked();
    private:
        Ui::Resume *ui;
};
#endif // RESUME_H
