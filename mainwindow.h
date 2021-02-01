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
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("/home/sebastian/Pulpit/DB/mydb.project");

        if (!mydb.open())
        {
            qDebug()<<("Nie połączono z bazą danych");
            return false;
        }
        else
        {
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
    void loadMainTab()
    {
        QDate DateNow;
        DateNow.currentDate();
        connOpen();
        QSqlQueryModel *modal=new QSqlQueryModel();
        QSqlQueryModel *modal2=new QSqlQueryModel();
        QSqlQuery* query = new QSqlQuery(mydb);
        QSqlQuery* query2 = new QSqlQuery(mydb);
        QSqlQuery* query3 = new QSqlQuery(mydb);
        QSqlQuery* query4 = new QSqlQuery(mydb);
        QSqlQuery* query5 = new QSqlQuery(mydb);
        QSqlQuery* query6 = new QSqlQuery(mydb);
        QSqlQuery* query7 = new QSqlQuery(mydb);
        query->prepare("SELECT type from tasks WHERE data > date('now') AND state ='0' OR data < date('now') AND state ='0'");
        query->exec();
        modal->setQuery(*query);
        ui->upcomingTaskList->setModel(modal);
        query2->prepare("SELECT type from tasks WHERE data <= date('now') AND state ='1' OR data >= date('now') AND state ='1'");
        query2->exec();
        modal2->setQuery(*query2);
        ui->oldTaskList->setModel(modal2);
        query3->prepare("SELECT sum(area) FROM fields");
        query3->exec();
        query3->first();
        ui->areaBox->setText(query3->value(0).toString()+" ha");
        query4->prepare("SELECT sum(fuel_use) FROM tasks WHERE state='1'");
        query4->exec();
        query4->first();
        ui->used_fuelBox->setText(query4->value(0).toString()+" l");
        query5->prepare("SELECT COUNT(DISTINCT name) FROM fields;");
        query5->exec();
        query5->first();
        ui->f_numberBox->setText(query5->value(0).toString());
        query6->prepare("SELECT COUNT(f_name) FROM tasks WHERE state='1';");
        query6->exec();
        query6->first();
        ui->DoneTasksCountBox->setText(query6->value(0).toString());
        query7->prepare("SELECT COUNT(f_name) FROM tasks WHERE state='0';");
        query7->exec();
        query7->first();
        ui->NotDoneTasksCountBox->setText(query7->value(0).toString());

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

    void on_upcomingTaskList_activated(const QModelIndex &index);

    void on_oldTaskList_activated(const QModelIndex &index);

    void on_wt_edit_delete_button_clicked();

    void on_wt_edit_save_button_clicked();

    void on_task_delete_button_clicked();

    void on_task_edit_button_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
