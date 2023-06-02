#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}


void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file = QFile(filename);

    currentFile = filename;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file" + file.errorString());
    }
    setWindowTitle(filename);
    QTextStream input_stream  = QTextStream(&file);

    QString text = input_stream.readAll();
    ui->textEdit->setText(text);
    file.close();
}


void MainWindow::on_actionSave_As_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Save As");
    QFile file = QFile(file_name);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file" + file.errorString());
        return;
    }
    currentFile = file_name;
    setWindowTitle(file_name);
    QTextStream output_stream (&file);
    QString text = ui->textEdit->toPlainText();
    output_stream << text;
    file.close();
}


void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("Printer");

    QPrintDialog printer_dialog = QPrintDialog(&printer, this);
    if (printer_dialog.exec() == QDialog::Rejected) {
        QMessageBox::warning(this, "Warning", "Cannot access printer");
        return;
    }

    ui->textEdit->print(&printer);
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionVersion_triggered()
{

}

