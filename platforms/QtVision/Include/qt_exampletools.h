#pragma once
#include <functional>

#include <QFormLayout>
#include <QCommandLinkButton>
#include <QBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QToolButton>
#include <QColorDialog>
#include <QStyleOption>
#include <QPainter>
#include <QComboBox>
#include <QStackedLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QFile>
#include <QDir>

#include "vsn_color.h"
#include "qt_openglwidget.h"
#include "qt_exampleview.h"

class QtColorButton : public QPushButton
{
    Q_OBJECT
public:
    QtColorButton(VSN::Color color, QWidget * parent = nullptr)
        : QPushButton(parent)
        , m_value(color)
    {
        connect(this, SIGNAL(released()), this, SLOT(evPressButton()));
    }

    VSN::Color value() const { return m_value; }
    void  setValue(VSN::Color color) { m_value = color; }

signals:
    void chooseColor(VSN::Color);

private slots:
    void evPressButton()
    {
        QColor color(m_value.GetRed(), m_value.GetGreen(), m_value.GetBlue());
        QColor newCol = QColorDialog::getColor(color, this);
        VSN::Color value(newCol.red(), newCol.green(), newCol.blue());
        if (newCol.isValid() /*&& value != m_value*/)
        {
            m_value = value;
            emit chooseColor(m_value);
        }
    }

    virtual void paintEvent(QPaintEvent * ev) override
    {
        QPainter p(this);
        QStyleOptionButton option;
        option.init(this);
        option.rect = rect();
        style()->drawControl(QStyle::CE_PushButton, &option, &p, this);
        p.fillRect(option.rect.adjusted(8, 8, -8, -8), QColor(m_value.GetRed(), m_value.GetGreen(), m_value.GetBlue()));
        p.drawRect(option.rect.adjusted(8, 8, -8, -8));
    }

private:
    VSN::Color m_value;
};

class ExampleWidget : public QWidget
{
public:
    ExampleWidget(QString name, QtExampleView * viewWidget)
    {
        QStackedLayout * pStackOfWidgets = new QStackedLayout(this);

        if (auto license = licenseWidget(this, viewWidget))
            pStackOfWidgets->addWidget(license);

        QWidget * pRoot = new QWidget;

        pStackOfWidgets->addWidget(pRoot);


        QHBoxLayout* left = new QHBoxLayout(pRoot);
        m_rightPanel = new QVBoxLayout();
        m_rightPanel->setAlignment(Qt::AlignTop);
        m_rightPanel->setMargin(8);

        //pStackOfWidgets->setMinimumSize({ 640,480 });

        left->addWidget(viewWidget, 1);
        left->addLayout(m_rightPanel);
        left->setMargin(0);


        QCommandLinkButton* info = new QCommandLinkButton();
        info->setText(name);
        info->setIconSize(QSize(0, 0));
        m_rightPanel->addWidget(info);

        move(QPoint(200, 200));
        QRect geom = QApplication::desktop()->availableGeometry();
        resize(2 * geom.width() / 3, 2 * geom.height() / 3);
    }

    QPushButton * button(const QString& label)
    {
        QPushButton * pButton = new QPushButton(label);

        if (getLayout())
            getLayout()->addWidget(pButton);

        return pButton;
    }

    // ---
    QLabel* label(const QString& str)
    {
        QLabel* labelKey = new QLabel(str);

        if (getLayout())
            getLayout()->addWidget(labelKey);

        return labelKey;
    }

    QDoubleSpinBox* spinbox(const QString& str, double value)
    {
        QDoubleSpinBox* lineEdit = new QDoubleSpinBox();

        if (getLayout())
            getLayout()->addLayout(labelBox(str, lineEdit, m_strMaxWidth));

        lineEdit->setValue(value);

        return lineEdit;
    }

    QDoubleSpinBox* spinbox(const QString& str, double value, double minRange, double maxRange, double step)
    {
        auto box = spinbox(str, value);

        box->setRange(minRange, maxRange);
        box->setSingleStep(step);

        return box;
    }

    QtColorButton * colorButton(const QString& str, VSN::Color value)
    {
        QtColorButton * button = new QtColorButton(value);

        if (getLayout())
            getLayout()->addLayout(labelBox(str, button, m_strMaxWidth));

        return button;
    }

    QComboBox * comboBox(const QString& str, const QStringList & list)
    {
        QComboBox * box = new QComboBox(this);
        box->addItems(list);

        if (getLayout())
            getLayout()->addLayout(labelBox(str, box, m_strMaxWidth));

        return box;
    }

    QToolButton * toolButton(const QString& str, const QIcon& icon, bool checkable = false)
    {
        QToolButton* button = new QToolButton(this);
        button->setCheckable(checkable);
        button->setIconSize(QSize(18, 18));
        button->setIcon(icon);
        button->setToolTip(str);

        if (getLayout())
            getLayout()->addLayout(labelBox(str, button, m_strMaxWidth));

        return button;
    }


    std::vector<QToolButton*> toolButtons(const QString & str, std::vector<const QIcon*> icons)
    {
        std::vector<QToolButton*> buttons;

        QHBoxLayout* groupButtons = new QHBoxLayout();
        groupButtons->setMargin(0);
        QWidget * widget = new QWidget(this);

        for (auto el : icons)
        {
            QToolButton* button = new QToolButton(widget);
            groupButtons->addWidget(button);
            button->setIconSize(QSize(18, 18));
            button->setIcon(*el);
            buttons.push_back(button);
        }

        groupButtons->setAlignment(Qt::AlignRight);

        widget->setLayout(groupButtons);

        if (getLayout())
            getLayout()->addLayout(labelBox(str, widget, m_strMaxWidth));

        return buttons;
    }

    QGroupBox* group(const QString& str, std::function<void(ExampleWidget*)> func)
    {
        if (func && getLayout())
        {
            QGroupBox* group = new QGroupBox(this);
            group->setTitle(str);

            m_layouts.push_back(new QVBoxLayout(group));
            func(this);
            m_layouts.pop_back();

            getLayout()->addWidget(group);

            return group;
        }

        return nullptr;
    }

private:
    QWidget * licenseWidget(QWidget * owner, QtExampleView * view)
    {
        std::string signature, key;
        if (loadkey(signature, key) && QtVision::ActivateLicense(signature, key))
        {
            view->activateKey();
            return nullptr;
        }

        QWidget * pWidget = new QWidget(owner);

        QBoxLayout * pLayout = new QVBoxLayout();
        pWidget->setLayout(pLayout);
        pLayout->setAlignment(Qt::AlignVCenter);

        auto warningLabel = new QLabel("The current license key is missing or wrong. Please enter your license key to activate.");
        warningLabel->setAlignment(Qt::AlignCenter);
        QFont font = warningLabel->font();
        font.setPointSize(16);
        warningLabel->setFont(font);
        pLayout->addWidget(warningLabel);
        pLayout->addSpacing(20);

        auto pSignature = new QLineEdit();
        auto pKey = new QLineEdit();

        pSignature->setMaximumWidth(500); pKey->setMaximumWidth(500);

        auto pSigLayout = labelBox("Signature:", pSignature, 100);
        pSigLayout->setAlignment(Qt::AlignHCenter);
        pLayout->addLayout(pSigLayout);
        auto pKeyLayout = labelBox("Key:", pKey, 100);
        pKeyLayout->setAlignment(Qt::AlignHCenter);
        pLayout->addLayout(pKeyLayout);

        auto pActivate = new QPushButton("Activate");
        auto pSaveKey = new QCheckBox("Save this license key");

        pActivate->setMaximumWidth(100);

        QHBoxLayout* hlayout = new QHBoxLayout();
        hlayout->setAlignment(Qt::AlignCenter);
        hlayout->addWidget(pSaveKey);
        hlayout->addWidget(pActivate);
        pLayout->addLayout(hlayout);

#if  defined(C3D_LICENSE_SIG) && defined(C3D_LICENSE_KEY)
        pSignature->setText(C3D_LICENSE_SIG);
        pKey->setText(C3D_LICENSE_KEY);
#endif

        QObject::connect(pActivate, &QPushButton::clicked, [this, pWidget, pSignature, pKey, pSaveKey, view]() {
            auto signature = pSignature->text().toStdString();
            auto key = pKey->text().toStdString();

            if (QtVision::ActivateLicense(signature, key))
            {
                view->activateKey();
                if (pSaveKey->isChecked())
                    savekey(signature, key);
                pWidget->deleteLater();
            }
        });

        return pWidget;
    }

    QHBoxLayout * labelBox(const QString& str, QWidget * widget, int strMaxWidth = -1)
    {
        QLabel* labelKey = new QLabel(str);
        labelKey->setBuddy(widget);

        if (strMaxWidth > -1)
            labelKey->setMaximumWidth(strMaxWidth > 0 ? strMaxWidth : labelKey->width());

        QHBoxLayout* hGroupLayout = new QHBoxLayout();
        hGroupLayout->addWidget(labelKey);
        hGroupLayout->addWidget(widget);

        return hGroupLayout;
    }

    QVBoxLayout * getLayout()
    {
        if (m_layouts.empty())
            return m_rightPanel;

        return m_layouts.back();
    }

    /// load the key from user directory
    bool loadkey(std::string & signature, std::string & key)
    {
        auto dir = QDir::homePath().toStdString() + "/.c3dkey";
        QFile file(dir.c_str());
        if (file.open(QFile::ReadOnly))
        {
            signature = file.readLine().toStdString();
            signature.erase(--signature.end()); // remove last symbol
            key = file.readLine().toStdString();
            file.close();

            return true;
        }

        return false;
    }

    /// save the key to user directory
    void savekey(const std::string & signature, const std::string & key)
    {
        auto dir = QDir::homePath().toStdString() + "/.c3dkey";
        QFile file(dir.c_str());
        file.open(QFile::WriteOnly);
        file.write(signature.data(), signature.size());
        file.write("\n");
        file.write(key.data(), key.size());
        file.close();
    }

    int           m_strMaxWidth = -1;
    QVBoxLayout * m_rightPanel = nullptr;
    std::list<QVBoxLayout*> m_layouts;
};
