#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "modelmainwindow.h"

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

private slots:
    void on_pushButtonEnviar_clicked();

    void on_actionCarregar_triggered();
    void on_actionSalvar_Locais_triggered();

    void on_actionAdicionar_triggered();
    void on_actionRemover_triggered();

    void on_actionComum_triggered();
    void on_actionEspecial_triggered();
    void on_actionRemover_Local_triggered();
    void on_actionCarregar_Locais_triggered();
    void on_listWidgetPlaces_doubleClicked(const QModelIndex &index);
    void on_listWidgetTarefas_doubleClicked(const QModelIndex &index);
};

#endif // MAINWINDOW_H
