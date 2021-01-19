#ifndef LOGIN_H
#define LOGIN_H
#include <QMainWindow>
#include <QKeyEvent>
#include "registration.h"
namespace Ui{
class Login;
}
class Login : public QMainWindow{
    Q_OBJECT
    QString Mode,RegMode;
    QString NameOfAccount;
    QMessageBox *msgBox;
    Registration *reg;
    void RegistrationStart(int Mode);
    void ErrorMessage(QString Error);
    public:
        explicit Login(QWidget *parent = nullptr);
        QString GetMode();
        QString GetAccountName();
        ~Login();
    private slots:
        void on_AccountLogin_clicked();
        void on_Ok_clicked();
        void on_Cancel_clicked();
        void on_JobSeeker_clicked();
        void on_Employer_clicked();
        void on_Registration_clicked();
        void MainPage();
        void FinishRegistration();
        void on_ShowPassword_clicked();
    protected:
        virtual bool eventFilter(QObject *watched,QEvent *event);
    signals:
         void Accessed();
    private:
        Ui::Login *ui;
};
#endif // LOGIN_H
