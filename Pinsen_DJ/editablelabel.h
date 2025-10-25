#ifndef EDITABLELABEL_H
#define EDITABLELABEL_H


#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QKeyEvent>

class EditableLabel : public QWidget
{
    Q_OBJECT

public:
    explicit EditableLabel(QWidget *parent = nullptr);
    explicit EditableLabel(const QString &prefix, const QString &text, QWidget *parent = nullptr);

    QString text() const;
    void setText(const QString &text);
    void setPlaceholderText(const QString &text);
    void setEditable(bool editable);
    bool isEditable() const;


    void setPrefix(const QString &prefix);//增加前缀
    QString prefix() const;

    // 添加字符长度限制方法
        void setMaxLength(int maxLength);
        int maxLength() const;

        // 添加对齐方法 :cite[4]:cite[10]
            Qt::Alignment alignment() const;
            void setAlignment(Qt::Alignment alignment);

public slots:
    void updateDisplayText();

signals:
    void textEdited(const QString &newText);
    void textChanged(const QString &newText);
    void editingStarted();
    void editingCanceled();
    void textExceedMaxLength(const QString &exceededText); // 新增信号：文本超出最大长度

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void handleEditingFinished();
    void handleTextChanged(const QString &text);

private:
    void init(const QString &prefix = "", const QString &text = "");
    void showLabel();
    void showEditor();
    void finishEditing();
    void cancelEditing();

    bool validateTextLength(const QString &text); // 新增方法：验证文本长度

    QLabel *m_label;
    QLineEdit *m_lineEdit;
    QString m_oldText;
    bool m_editable;
    QString m_prefix;
    QString m_text;
     int m_maxLength; // 新增成员：最大字符长度
      Qt::Alignment m_alignment; // 存储对齐方式
};
#endif // EDITABLELABEL_H
