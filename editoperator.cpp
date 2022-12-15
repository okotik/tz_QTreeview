#include <QPushButton>
#include "editoperator.h"
#include "ui_editoperator.h"
#include "basereader.h"

EditOperator::EditOperator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditOperator)
{
    ui->setupUi(this);
    connect(ui->nameLineEdit, &QLineEdit::textChanged, this,  &EditOperator::setSaveButtonEnablet);
    connect(ui->mccLineEdit, &QLineEdit::textChanged, this,  &EditOperator::setSaveButtonEnablet);
    connect(ui->mncLineEdit, &QLineEdit::textChanged, this,  &EditOperator::setSaveButtonEnablet);
}

EditOperator::~EditOperator()
{
    delete ui;
}

void EditOperator::setDataForm(const QString &name, const QString &mcc, const QString &mnc, QPixmap &pix, QPixmap &pixCountry, bool isEditable)
{
    ui->nameLineEdit->setText(name);
    ui->mccLineEdit->setText(mcc);
    ui->mccLineEdit->setEnabled(isEditable);
    ui->mncLineEdit->setText(mnc);
    ui->mncLineEdit->setEnabled(isEditable);
    ui->labelImage->setPixmap(pix);
    ui->labelImageCountry->setPixmap(pixCountry);

    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(isSaveButtonEnablet());
}

bool EditOperator::isSaveButtonEnablet()
{
    if(ui->nameLineEdit->text().isEmpty() || ui->mccLineEdit->text().isEmpty() || ui->mncLineEdit->text().isEmpty())
        return false;
    return true;
}

void EditOperator::setSaveButtonEnablet(const QString &)
{
    if(ui->mccLineEdit->isEnabled())
    {
        QPixmap pix;
        if(!pix.load(QString(":/icon/Operators/%1_%2.png").arg(ui->mccLineEdit->text()).arg(ui->mncLineEdit->text())))
            pix.load(":/icon/Operators/unnown.png");
        ui->labelImage->setPixmap(pix);

        if(ui->mccLineEdit->text().length() == 3)
        {
            if(!pix.load(QString(":/icon/Countries/%1.png").arg(BaseReader::getInstance().getCounryCodeByMcc(ui->mccLineEdit->text().toInt()))))
                pix.load(":/icon/Operators/unnown.png");
            ui->labelImageCountry->setPixmap(pix);
        }
        else
        {
            pix.load(":/icon/Operators/unnown.png");
            ui->labelImageCountry->setPixmap(pix);
        }
    }
    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(isSaveButtonEnablet());
}

void EditOperator::accept()
{
    this->close();
    emit saveNewData(ui->nameLineEdit->text(), ui->mccLineEdit->text(), ui->mncLineEdit->text(), ui->mccLineEdit->isEnabled());
}
