#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDesktopWidget>
#include <controllermainwindow.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    QDesktopWidget* d = QApplication::desktop();
    QSize size = this->size();

    int ws = d->width();   // returns screen width
    int h = d->height();  // returns screen height
    int mw = size.width();
    int mh = size.height();
    int cw = (ws/2) - (mw/2);
    int ch = (h/2) - (mh/2);
    this->move(cw,ch);
}

MainWindow::~MainWindow()
{

}

void MainWindow::on_pushButtonEnviar_clicked()
{
    QMessageBox a;
    a.setText("Enviado ao Sistema!");
    a.exec();
}
/*Maps*/
void MainWindow::on_actionCarregar_triggered()
{
    ControllerMainWindow::LoadMap();
}

/*Tasks*/
void MainWindow::on_actionAdicionar_triggered()
{
    ControllerMainWindow::SetToAddTask();
}

void MainWindow::on_actionRemover_triggered()
{
    ControllerMainWindow::SetToRemoveTask();
}

/*Places*/
void MainWindow::on_actionComum_triggered()
{
    ControllerMainWindow::SetToAddCommonPlace();
}

void MainWindow::on_actionEspecial_triggered()
{
    ControllerMainWindow::SetToAddSpecialPlace();
}

void MainWindow::on_actionSalvar_Locais_triggered()
{
    ControllerMainWindow::SaveMap();
}

void MainWindow::on_actionRemover_Local_triggered()
{
    ControllerMainWindow::SetToRemovePlace();
}

void MainWindow::on_actionCarregar_Locais_triggered()
{
    ControllerMainWindow::LoadPlaces();
}

void MainWindow::on_listWidgetPlaces_doubleClicked(const QModelIndex &index)
{
    if (ControllerMainWindow::IsToRemovePlace())
        ControllerMainWindow::RemovePlace(index.row());
    else if (ControllerMainWindow::IsToAddTask())
        ControllerMainWindow::AddTask(index.row());
}

void MainWindow::on_listWidgetTarefas_doubleClicked(const QModelIndex &index)
{
    if (ControllerMainWindow::IsToRemoveTask())
        ControllerMainWindow::RemoveTask(index.row());
}
