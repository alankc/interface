#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <controllermainwindow.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
}

MainWindow::~MainWindow()
{

}

void MainWindow::on_pushButtonEnviar_clicked()
{
    QMessageBox a;
    a.setText("Enviado ao Robô!");
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
    QMessageBox::information(this, "teste", "Adicionar Tarefa");
}

void MainWindow::on_actionRemover_triggered()
{
    QMessageBox::information(this, "teste", "RemoverTarefa");
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
