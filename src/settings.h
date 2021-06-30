#ifndef SETTINGS_H
#define SETTINGS_H

#include <QKeyEvent>
#include <QSettings>
#include <QWidget>

namespace Ui
{
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

  public:
    explicit Settings(QWidget *parent = nullptr, const QString &setting_path = QString());

    virtual ~Settings();

  public slots:
    void setTheme(const QString &themeName);

    void setAdvanceMode();

    void setSimpleMode();

    void showAbout();

  signals:
    void empty_saved_table();

    void themeChanged(const QString &themeName);

    void switchAdvanceMode(bool checked);

    void switchSimpleMode(bool checked);

  protected:
    void keyPressEvent(QKeyEvent *e) override;

  private slots:
    void on_clearColorsPushButton_clicked();

    void on_donatePushButton_clicked();

    void on_girhubPushButton_clicked();

#ifdef COLORPICKER_SNAPCRAFT_BUILD
    void on_ratePushButton_clicked();

#endif
    void on_themeComboBox_currentIndexChanged(const QString &arg1);

    void on_advance_toggled(bool checked);

    void on_simple_toggled(bool checked);
    
    void on_message_linkActivated(const QString &link);

  private:
    Ui::Settings *ui;
    QString setting_path;
};

#endif // SETTINGS_H
