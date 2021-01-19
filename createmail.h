#ifndef CREATEMAIL_H
#define CREATEMAIL_H
#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
namespace Ui {
class CreateMail;
}
class CreateMail : public QMainWindow{
    Q_OBJECT
    QString CompanyOrJobSeeker,ID;
    public:
        explicit CreateMail(QWidget *parent = nullptr);
        void SetData(QString CompanyOrJobSeeker,QString Title,QString Position,QString To,QString ID="");
        ~CreateMail();
    private slots:
        void on_buttonBox_accepted();
        void on_buttonBox_rejected();
private:
        Ui::CreateMail *ui;
};
#endif // CREATEMAIL_H
