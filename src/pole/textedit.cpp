#include "textedit.h"

TextEdit::TextEdit( QWidget *parent ) : QTextEdit(parent)
{
	setGeometry(498,80,100,21);
	
	QPalette palette = this->palette();
	palette.setColor(QPalette::Active, QPalette::Text, QColor(0, 165, 200));
	palette.setColor(QPalette::Active, QPalette::Base, Qt::transparent);
	setPalette(palette);
	
   	setFrameStyle(QFrame::NoFrame);
	setReadOnly(true);
	
#ifdef Q_OS_UNIX
 	setCurrentFont( QFont("Sans Serif", 7) );
#endif
	
#ifdef Q_OS_WIN
	setCurrentFont( QFont("Sans Serif", 9) );
#endif	
	
	setCursorWidth(0);
	setAlignment( Qt::AlignCenter );
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void TextEdit::contextMenuEvent( QContextMenuEvent *e )
{
}

void TextEdit::mouseMoveEvent(QMouseEvent *pe)
{
}

void TextEdit::mouseDoubleClickEvent ( QMouseEvent *pe )
{
}

