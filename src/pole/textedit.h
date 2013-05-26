#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>

class TextEdit : public QTextEdit
{
	Q_OBJECT
	
	public:
		TextEdit( QWidget *parent = 0 );
		
	private slots:
		virtual void mouseMoveEvent(QMouseEvent *pe);
		virtual void mouseDoubleClickEvent ( QMouseEvent *pe );
		virtual void contextMenuEvent( QContextMenuEvent *e );
};

#endif
