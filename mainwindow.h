#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QTableWidgetItem>
#include <QStandardPaths>
#include <QDir>

#include "colordialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_save_clicked();

    void on_saved_cellClicked(int row, int column);

    QString getHSV(const QColor color);
    QString getRGB(const QColor color);
    void invalidColor();
    QString getCMYK(const QColor color);

    void setStyle(QString fname);

    void on_actionSettings_triggered();

private:
    Ui::MainWindow *ui;
    ColorDialog *colorDialog = nullptr;
    QString setting_path;
    QSettings settings;
};

#endif // MAINWINDOW_H
