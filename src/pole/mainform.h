#ifndef MAINFORM_H 
#define MAINFORM_H

#include <QMainWindow>


class QGraphicsScene;
class QGraphicsView;
class QPushButton;
class QStringList;
class QSignalMapper;
class QLabel;
class ImageButton;
class ImageLabel;
class TextEditList;
class TextEdit;
class IconList;
class QCursor;
class QAction;
class QSettings;

class MainForm : public QMainWindow
{
	Q_OBJECT
			
	public:
		MainForm(QWidget *parent = 0, Qt::WindowFlags fl = Qt::Window| Qt::FramelessWindowHint);
		
	private slots:
		virtual void mousePressEvent(QMouseEvent *pe);
		virtual void mouseReleaseEvent(QMouseEvent *pe);
		virtual void mouseMoveEvent(QMouseEvent *pe);
		
		
		void changeNews();
		void changeMap();
		void changeDataItem();
		void changeForces();
		void changePeople();
		void changeTech();
		void changeOutfit();
		
		void loadNewsPage();
		void loadMainPage();
		void loadNavigationPage();
		void loadDataPage();
		void loadJournalPage();
		
		void hideNewsPage();
		void hideMainPage();
		void hideNavigationPage();
		void hideDataPage();
		void hideJournalPage();
		
		void showNewsPage();
		void showMainPage();
		void showNavigationPage();
		void showDataPage();
		void showDataForces();
		void showDataPeople();
		void showDataTech();
		void showDataOutfit();
		void showJournalPage();
		
		void hidePage();
		void changePage();
		
		void arrowSlot();
		
		void playButtonSoundMove();
		void playButtonSoundPress();
		
		void showStatusText();
		void clearStatusText();
		
		void aboutSlot();
		void switchSound();
		
	private:
		QLabel *glassLabel;
		QLabel *panelsLabel;
		
		QSettings *settings;
		QString version;
		
		QAction *aboutAction;
		QAction *aboutQtAction;
		QAction *soundAction;
		
		TextEdit *statusTextEdit;
		QStringList statusList;
		bool sound;
		
		ImageButton *powerButton;
		ImageButton *dataButton;
		ImageButton *journalButton;
		ImageButton *navButton;
		ImageButton *leftButton;
		ImageButton *topleftButton;
		ImageButton *rightButton;
		ImageButton *toprightButton;
		
		ImageLabel *newsLabel;
		ImageLabel *newsHeaderLabel;
		TextEditList *newsText;
		TextEdit *newsHeader;
		QStringList nList;
 		int newsDepartSize;
 		int newsSubdepartSize;
 		int newsDepartIndex;
 		int newsSubdepartIndex;
		QStringList newsList;
		void loadNews();
		
		ImageLabel *mLabel;
		TextEditList *mTextList;
		
		ImageLabel *navLabel;
		ImageLabel *pLabel;
		ImageLabel *mapLabel;
		ImageButton *rnavButton;
		ImageButton *lnavButton;
		TextEdit *mapHeader;
		QStringList mapList;
		int mapIndex;
		void loadMaps();
		
		
		QStringList forcesList;
		QStringList fList;
		QString dataPage;
		int forcesDepartIndex;
		int forcesIndex;
		int forcesDepartSize;
		
		QStringList peopleList;
		QStringList pList;
		QString peopleTextLeft;
		QStringList peopleTr;
		int peopleDepartIndex;
		int peopleIndex;
		int peopleDepartSize;
		
		QStringList techList;
		QStringList tList;
		QString techTextLeft;
		int techDepartIndex;
		int techIndex;
		int techDepartSize;
		
		QVector<QStringList> outfitList;
		QString armorsTextLeft;
		QString grenadesTextLeft;
		QString ammunitionTextLeft;
		QString weaponsTextLeft;
		QString equipmentText;
		QStringList equipmentTextList;
		int outfitDepartIndex;
		int outfitIndex;
		
		ImageLabel *dataLabel;
		ImageButton *outfitButton;
		ImageButton *techButton;
		ImageButton *forcesButton;
		ImageButton *peopleButton;
		ImageLabel *dbLabel;
		ImageLabel *dbPeopleLabel;
		ImageLabel *dbTechLabel;
		ImageLabel *dbArmorLabel;
		ImageButton *rdButton;
		ImageButton *ldButton;
		ImageButton *rdtopButton;
		ImageButton *ldtopButton;
		TextEditList *dbTextEdit;
		TextEditList *charTextLeft;
		TextEditList *charTextRight;
		TextEdit *dbHeader;
		TextEdit *dbType;
		
		void loadDbForces();
		void loadDbPeople();
		void loadDbTech();
		void loadDbOutfit();
		void armorsShow();
		void grenadesShow();
		void ammunitionShow();
		void weaponsShow();
		void equipmentShow();
		
		QString page;
		
		QString path;
		QPoint mPosition;
		bool mLeftPressed;
		
		IconList *iconList;
		TextEdit *iconText;
		
		QPixmap cursorPixmap;
		QCursor myCursor;
};

#endif
