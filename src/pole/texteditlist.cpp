#include "texteditlist.h"

#include <QCursor>
#include <QMouseEvent>

TextEditList::TextEditList( QWidget *parent, int type ) : QTextEdit(parent)
{
	if(type == 0)
 		setGeometry(160, 290, 397, 130);
	
	QPalette palette = this->palette();
	palette.setColor(QPalette::Active, QPalette::Text, QColor(0, 165, 200));
	palette.setColor(QPalette::Active, QPalette::Base, QColor(0, 0, 0));
	setPalette(palette);
	
  	setOwnStyle();
}

void TextEditList::contextMenuEvent( QContextMenuEvent *e )
{
}

void TextEditList::mouseDoubleClickEvent ( QMouseEvent *pe )
{
}

void TextEditList::mouseMoveEvent(QMouseEvent *pe)
{
}

void TextEditList::mouseReleaseEvent(QMouseEvent *pe)
{
	
}

void TextEditList::mousePressEvent(QMouseEvent *pe)
{
	
}

void TextEditList::setOwnStyle()
{
     	setFrameStyle(QFrame::NoFrame);
	setReadOnly(true);
	
#ifdef Q_OS_UNIX
	setCurrentFont( QFont("Sans Serif", 7) );
#endif
	
#ifdef Q_OS_WIN
 	setCurrentFont( QFont("Sans Serif", 9) );
#endif
	
	setAlignment( Qt::AlignCenter );
}


