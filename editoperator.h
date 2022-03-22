#ifndef EDITOPERATOR_H
#define EDITOPERATOR_H

#include <QDialog>

namespace Ui {
class EditOperator;
}

class EditOperator : public QDialog
{
    Q_OBJECT

public:
    explicit EditOperator(QWidget *parent = nullptr);
    ~EditOperator() override;

public:
    void setDataForm(const QString &name, const QString &mcc, const QString &mnc, QPixmap &pix, QPixmap &pixCountry, bool isEditable = false);
    bool isSaveButtonEnablet();
signals:
    void saveNewData(const QString &name, const QString &mcc, const QString &mnc, const bool isNewItem);
public slots:
    void accept() override;
    void setSaveButtonEnablet(const QString &);

private:
    Ui::EditOperator *ui;
};

#endif // EDITOPERATOR_H
