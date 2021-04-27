#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QSettings>
#include <QKeyEvent>

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr, QString setting_path = "");
    ~Settings();
public slots:
    void setTheme(QString themeName);
    void setAdvanceMode();
    void setSimpleMode();
    void showAbout();
signals:
    void empty_saved_table();
    void themeChnaged(QString themeName);
    void switchAdvanceMode(bool checked);
    void switchSimpleMode(bool checked);

protected slots:
    void keyPressEvent(QKeyEvent *e);
private slots:
    void on_clearColorsPushButton_clicked();

    void on_donatePushButton_clicked();

    void on_girhubPushButton_clicked();

    void on_ratePushButton_clicked();

    void on_themeComboBox_currentIndexChanged(const QString &arg1);

    void on_advance_toggled(bool checked);

    void on_simple_toggled(bool checked);


    void on_message_linkActivated(const QString &link);

private:
    Ui::Settings *ui;
    QString setting_path;
};

#endif // SETTINGS_H
