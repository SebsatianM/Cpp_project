#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QFileInfo>
#include <QDebug>
#include "ui_mainwindow.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase mydb;

    void connClose()
    {
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }
    bool connOpen()
    {
        mydb =QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("/home/sebastian/Pulpit/DB/mydb.project");

        if (!mydb.open())
        {
            qDebug()<<("Nie połączono z bazą danych");
            return false;
        }
        else
        {
             //qDebug()<<("Prawidłowo połączono z bazą danych");
             return true;
        }
    }

    void loadTractorListToComboBox()
    {
        connOpen();

        QSqlQueryModel *modal=new QSqlQueryModel();
        QSqlQuery* query = new QSqlQuery(mydb);

        query->prepare("SELECT name from tractors");
        query->exec();
        modal->setQuery(*query);
        ui->wt_t_name_comboBox->setModel(modal);

        connClose();

        //qDebug()<<(modal->rowCount());


    }
    void loadFieldsToEditList()
    {
        connOpen();

        QSqlQueryModel *modal=new QSqlQueryModel();
        QSqlQuery* query = new QSqlQuery(mydb);

        query->prepare("SELECT name from fields");
        query->exec();

        modal->setQuery(*query);
        ui->f_name_list->setModel(modal);

        connClose();


    }
    void loadTractorsToEditList()
    {
        connOpen();

        QSqlQueryModel *modal=new QSqlQueryModel();
        QSqlQuery* query = new QSqlQuery(mydb);

        query->prepare("SELECT name from tractors");
        query->exec();
        modal->setQuery(*query);
        ui->t_name_list->setModel(modal);
        connClose();
    }

    void loadWorkTypesToEditLists()
    {
        connOpen();

        QSqlQueryModel *modal=new QSqlQueryModel();
        QSqlQuery* query = new QSqlQuery(mydb);
        query->prepare("SELECT DISTINCT name from work_types");
        query->exec();
        modal->setQuery(*query);
        ui->wt_name_list->setModel(modal);
        connClose();
    }
    void loadFieldsToTaskTab()
    {
        connOpen();

        QSqlQueryModel *modal=new QSqlQueryModel();
        QSqlQuery* query = new QSqlQuery(mydb);

        query->prepare("SELECT name from fields");
        query->exec();

        modal->setQuery(*query);
        ui->f_name_Task_list->setModel(modal);

        connClose();

    }
    void loadWorkTypesToTaskTab()
    {
        connOpen();

        QSqlQueryModel *modal=new QSqlQueryModel();
        QSqlQuery* query = new QSqlQuery(mydb);
        query->prepare("SELECT DISTINCT name from work_types");
        query->exec();
        modal->setQuery(*query);
        ui->wt_name_Task_list->setModel(modal);
        connClose();
    }

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_add_tractor_button_clicked();

    void on_add_field_button_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_add_wt_button_clicked();

    void on_f_name_list_currentIndexChanged(const QString &name);

    void on_f_edit_delete_button_clicked();

    void on_f_edit_save_button_clicked();

    void on_t_name_list_currentIndexChanged(const QString &name);

    void on_t_edit_delete_button_clicked();

    void on_t_edit_save_button_clicked();

    void on_wt_name_list_currentIndexChanged(const QString &name);

    void on_wt_edit_t_list_currentIndexChanged(const QString &name);

    void on_add_task_button_clicked();

    void on_wt_name_Task_list_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
