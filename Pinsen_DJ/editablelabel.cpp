#include "editablelabel.h"
#include <QDebug>

void EditableLabel::init(const QString &prefix, const QString &text)
{
    // 创建水平布局，去除边距和间距
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    // 初始化成员变量
    m_prefix = prefix;
    m_text = text;
    m_oldText = text;
    m_maxLength = 32767; // 默认设置为一个很大的值，相当于不限制


    // 创建标签和行编辑框
    m_label = new QLabel(text, this);
    m_lineEdit = new QLineEdit(text, this);

    QFont font("微软雅黑", 12);
    m_label->setFont(font);
    m_lineEdit->setFont(font);

    // 设置行编辑框的最大长度
    m_lineEdit->setMaxLength(m_maxLength);

    // 设置对齐方式
    m_label->setAlignment(m_alignment);
    m_lineEdit->setAlignment(m_alignment);

    // 更新显示文本
    updateDisplayText();

    // 设置行编辑框的文本（不包含前缀）
    m_lineEdit->setText(m_text);


    // 添加到布局
    layout->addWidget(m_label);
    layout->addWidget(m_lineEdit);

    // 初始状态：显示标签，隐藏编辑器
    m_label->show();
    m_lineEdit->hide();

    // 设置标签的样式，使其看起来可点击
    m_label->setStyleSheet("QLabel { padding: 2px; border: 1px solid transparent; }"
                           "QLabel:hover { border: 1px dotted gray; }");

    // 为行编辑框安装事件过滤器，用于处理ESC键
    m_lineEdit->installEventFilter(this);

    // 连接信号槽
    connect(m_lineEdit, &QLineEdit::editingFinished, this, &EditableLabel::handleEditingFinished);
    connect(m_lineEdit, &QLineEdit::textChanged, this, &EditableLabel::handleTextChanged);

    // 初始化其他成员变量
    m_oldText = text;
    m_editable = true;
}

// 更新显示文本（标签显示前缀+文本）
void EditableLabel::updateDisplayText()
{
    m_label->setText(m_prefix + m_text);
}

bool EditableLabel::validateTextLength(const QString &text)
{
    if (text.length() > m_maxLength) {
        // 发出文本超出最大长度的信号
        emit textExceedMaxLength(text);

        // 可选：显示警告消息
        // QMessageBox::warning(this, "长度限制",
        //                     QString("文本长度不能超过 %1 个字符").arg(m_maxLength));
        return false;
    }
    return true;
}

// 设置最大字符长度
void EditableLabel::setMaxLength(int maxLength)
{
    m_maxLength = maxLength;
    m_lineEdit->setMaxLength(maxLength);
}

// 获取最大字符长度
int EditableLabel::maxLength() const
{
    return m_maxLength;
}

void EditableLabel::handleTextChanged(const QString &text)
{
    // 实时验证文本长度
    if (!validateTextLength(text)) {
        // 如果文本超出限制，恢复到之前的有效文本
        m_lineEdit->blockSignals(true);
        m_lineEdit->setText(m_oldText);
        m_lineEdit->blockSignals(false);
    }
}

// 获取对齐方式
Qt::Alignment EditableLabel::alignment() const
{
    return m_alignment;
}

// 设置对齐方式 :cite[4]:cite[10]
void EditableLabel::setAlignment(Qt::Alignment alignment)
{
    m_alignment = alignment;
    m_label->setAlignment(alignment);
    m_lineEdit->setAlignment(alignment);
}

EditableLabel::EditableLabel(QWidget *parent) : QWidget(parent)
{
    init("",""); // 调用初始化函数，使用空字符串
}

EditableLabel::EditableLabel(const QString &prefix, const QString &text, QWidget *parent) : QWidget(parent)
{
    init(prefix, text); // 调用初始化函数，使用提供的前缀和文本
}

QString EditableLabel::text() const
{
    return m_label->text();
}

void EditableLabel::setText(const QString &text)
{
    m_text = text;
    m_lineEdit->setText(text);
    updateDisplayText();
}

void EditableLabel::setPrefix(const QString &prefix)
{
    m_prefix = prefix;
    updateDisplayText();
}

QString EditableLabel::prefix() const
{
    return m_prefix;
}

void EditableLabel::setPlaceholderText(const QString &text)
{
    m_lineEdit->setPlaceholderText(text);
}

void EditableLabel::setEditable(bool editable)
{
    m_editable = editable;
    // 根据可编辑状态更新标签样式
    if (editable) {
        m_label->setStyleSheet("QLabel { padding: 2px; border: 1px solid transparent; }"
                               "QLabel:hover { border: 1px dotted gray; }");
    } else {
        m_label->setStyleSheet("QLabel { padding: 2px; border: none; }");
    }
}

bool EditableLabel::isEditable() const
{
    return m_editable;
}

void EditableLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_editable) {
        showEditor();
        event->accept();
    } else {
        QWidget::mouseDoubleClickEvent(event);
    }
}

bool EditableLabel::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == m_lineEdit && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        // 处理ESC键 - 取消编辑
        if (keyEvent->key() == Qt::Key_Escape) {
            cancelEditing();
            return true;
        }

        // 处理回车键 - 完成编辑
        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
            finishEditing();
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}

void EditableLabel::handleEditingFinished()
{
    finishEditing();
}

void EditableLabel::showLabel()
{
    m_lineEdit->hide();
    m_label->show();
    setFocusProxy(m_label);
}

void EditableLabel::showEditor()
{
    if (!m_editable) return;

    m_oldText = m_label->text();
    m_lineEdit->setText(m_oldText);
    m_label->hide();
    m_lineEdit->show();
    m_lineEdit->setFocus();
    m_lineEdit->selectAll();
    setFocusProxy(m_lineEdit);

    emit editingStarted();
}

void EditableLabel::finishEditing()
{
    QString newText = m_lineEdit->text();
    // 验证文本长度
    if (validateTextLength(newText)) {
        m_text = newText;
        updateDisplayText();
        showLabel();

        if (newText != m_oldText) {
            emit textEdited(newText);
        }
    } else {
        // 如果文本超出限制，恢复到之前的文本
        m_lineEdit->setText(m_oldText);
        showLabel();
    }
}

void EditableLabel::cancelEditing()
{
    m_lineEdit->setText(m_oldText);
    showLabel();
    emit editingCanceled();
}
