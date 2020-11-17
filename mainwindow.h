#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QFileInfo>
#include "connection.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_add_fields_box_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase mydb;
};

#endif // MAINWINDOW_H
