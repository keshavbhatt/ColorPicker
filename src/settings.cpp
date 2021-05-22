#include "settings.h"
#include "ui_settings.h"

#include <QDesktopServices>
#include <QFile>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QUrl>

Settings::Settings(QWidget *parent, const QString &setting_path) : QWidget(parent), ui(new Ui::Settings)
{
    ui->setupUi(this);
    this->setting_path = setting_path;
}

void Settings::keyPressEvent(QKeyEvent *e)
{
    // esc key to close settings widget
    if (e->key() == Qt::Key_Escape)
        this->close();
}

void Settings::setAdvanceMode()
{
    ui->advance->blockSignals(true);
    ui->simple->blockSignals(true);
    ui->advance->setChecked(true);
    ui->simple->setChecked(false);
    ui->advance->blockSignals(false);
    ui->simple->blockSignals(false);
}

void Settings::setSimpleMode()
{
    ui->advance->blockSignals(true);
    ui->simple->blockSignals(true);
    ui->advance->setChecked(false);
    ui->simple->setChecked(true);
    ui->advance->blockSignals(false);
    ui->simple->blockSignals(false);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::setTheme(const QString &themeName)
{
    if (themeName.contains("Dark"))
    {
        ui->themeComboBox->setCurrentIndex(2);
    }
    else if (themeName.contains("Flat"))
    {
        ui->themeComboBox->setCurrentIndex(1);
    }
    else if (themeName.contains("System"))
    {
        ui->themeComboBox->setCurrentIndex(0);
    }
}

void Settings::on_clearColorsPushButton_clicked()
{
    QFile file(setting_path + "/saved.colors");
    file.remove();
    emit empty_saved_table();
}

void Settings::on_donatePushButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://paypal.me/keshavnrj/2"));
}

void Settings::on_girhubPushButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/keshavbhatt/ColorPicker"));
}

void Settings::on_ratePushButton_clicked()
{
    QDesktopServices::openUrl(QUrl("snap://color-picker"));
}

void Settings::on_themeComboBox_currentIndexChanged(const QString &arg1)
{
    emit themeChanged(arg1);
}

void Settings::on_advance_toggled(bool checked)
{
    emit switchAdvanceMode(checked);
}

void Settings::on_simple_toggled(bool checked)
{
    emit switchSimpleMode(checked);
}

void Settings::showAbout()
{
    QString mes = "<p align='center' style='-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; "
                  "margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;'><br /></p>"
                  "<p align='center' style=' margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; "
                  "-qt-block-indent:0; text-indent:0px;'><img src=':/icons/64/color-picker.png' /></p>"
                  "<p align='center' style='-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; "
                  "margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;'><br /></p>"
                  "<p align='center' style=' margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; "
                  "-qt-block-indent:0; text-indent:0px;'>Designed and Developed</p>"
                  "<p align='center' style=' margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; "
                  "-qt-block-indent:0; text-indent:0px;'>by <span style=' font-weight:600;'>Keshav Bhatt</span> "
                  "&lt;keshavnrj@gmail.com&gt;</p>"
                  "<p align='center' style=' margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; "
                  "-qt-block-indent:0; text-indent:0px;'>Website: https://ktechpit.com</p>"
                  "<p align='center' style=' margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; "
                  "-qt-block-indent:0; text-indent:0px;'>Runtime: Qt 5.5.1</p>"
                  "<p align='center' style=' margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; "
                  "-qt-block-indent:0; text-indent:0px;'>Version: " +
                  QApplication::applicationVersion() +
                  "</p>"
                  "<p align='center' style='-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; "
                  "margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;'><br /></p>"
                  "<p align='center' style=' margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; "
                  "-qt-block-indent:0; text-indent:0px;'><a style='color:#4392d0;' "
                  "href='https://snapcraft.io/search?q=keshavnrj'>More Apps</p>";

    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    ui->message->setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff, "opacity");
    a->setDuration(1000);
    a->setStartValue(0);
    a->setEndValue(1);
    a->setEasingCurve(QEasingCurve::InCurve);
    a->start(QPropertyAnimation::DeleteWhenStopped);
    ui->message->setText(mes);
    ui->message->show();
}

void Settings::on_message_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl(link));
}
