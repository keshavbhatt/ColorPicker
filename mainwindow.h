#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QTableWidgetItem>
#include <QStandardPaths>
#include <QDir>

#include "settings.h"
#include "colordialog.h"

#include "ui_pattern.h"

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



    void load_saved_colors();
    void save_color(const QColor color);
    void add_to_table(const QString colorStr, bool saving);
    void delete_color_from_saved_colors_file(const QString hexArgb);
    void on_actionSettingsAndAbout_triggered();

    void on_actionQuit_triggered();


    void on_copy_clicked();

    void on_code_textChanged(const QString &arg1);

    void switchAdvanceMode();
    void switchSimpleMode();
    void on_actionswitchMode_triggered();

    void on_pattern_generator_clicked();

    void on_pickBackground_clicked();

    void on_zoomin_clicked();

    void on_zoomout_clicked();

protected slots:
    void closeEvent(QCloseEvent *closeEv);
private:
    Ui::MainWindow *ui;
    Ui::pattern_widget _ui_pattern;

    ColorDialog *colorDialog = nullptr;
    QString setting_path;
    QSettings settings;
    Settings *settingsWidget = nullptr;
    QWidget *pattern_widget = nullptr;
    int _patter_factor = 4;
    QPushButton *screenPicker = nullptr;
    QColorDialog *cDialog = nullptr;
};

#endif // MAINWINDOW_H
