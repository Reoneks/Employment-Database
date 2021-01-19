#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QCloseEvent>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Login;
class News;
class Database;
class JobApplications;
class AddVacancy;
class FindEmployer;
class PrivateOffice;
class CreateMail;
class ChangeNews;
class UserStatistics;
class Resume;
class AdminEditVacancy;

class MainWindow : public QMainWindow{
        Q_OBJECT
        Login *log;
        AddVacancy *vacancy;
        UserStatistics *user;
        Database *database;
        Resume *resume;
        PrivateOffice *office,*InfoOffice;
        CreateMail *mail;
        AdminEditVacancy *AdminEdit;
        QGridLayout *hlayout;
        QLabel *label;
        QPushButton *Yes,*No;
        QWidget *mainWindow1;
        QVector<JobApplications*> Job;
        QVector<News*> NewsWidget;
        QVector<FindEmployer*> Employer;
        QString Mode;
        QString Filled;
        QWidget *CentralWidget;
        ChangeNews *news;
        QPushButton *button,*button1,*button2;
        QMenu *File;
        QAction *Leave,*Delete;
        FindEmployer *TempEmpl,*TempEmplJS;
        JobApplications *TempJob;
        void HomePage();
        void MailAndApplication();
        void FullSizeWidget(QWidget *WidgetFromTable,QString Mode,QSize size);
        void SetFindEmployerData(QVector<QVector<QString>>Result);
        void AddAdmin();
        void AddEduc();
        QVector<QString> DataToCreateMail;
    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
    protected:
        virtual bool eventFilter(QObject *watched,QEvent *event);
    private slots:
        void OpenMainWindow();
        void on_HomePage_clicked();
        void on_HomePage_2_clicked();
        void on_CheckJobApplications_clicked();
        void on_Mail_clicked();
        void on_AddVacancy_clicked();
        void on_PrivateOffice_2_clicked();
        void on_FindEmployer_clicked();
        void on_PrivateOffice_clicked();
        void StartCreateMail();
        void ShowLoginForm();
        void ShowLoginForm1();
        void DeleteAccount();
        void on_ChangeNews_clicked();
        void on_Vacancy_clicked();
        void StartChangeVacancy();
        void StartDeleteVacancy();
        void on_CheckStatistics_clicked();
        void AskDelete();
        void BreakDelete();
        void OpenInfo();
        void DeleteMailC();
        void DeleteMailJS();
        void on_lineEdit_textChanged(const QString &arg1);
        void on_AddResume_clicked();
        void on_RedactVacancy_clicked();

private:
        Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
