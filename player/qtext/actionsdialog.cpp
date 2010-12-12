#include "mainwindow.h"
#include "actionsdialog.h"

ActionsDialog::ActionsDialog( QList<QAction*> actions,
                              QWidget* parent )
    : QDialog( parent )
    , settings( new QSettings )
    , m_actions( actions )
{
    setupUi();
}

ActionsDialog::~ActionsDialog()
{
}

void ActionsDialog::changeEvent( QEvent* e )
{
    QDialog::changeEvent( e );
    switch( e->type() )
    {
        case QEvent::LanguageChange:
            retranslateUi();
            break;
        default:
            break;
    }
}

void ActionsDialog::recordAction( int curr_row, int curr_col,
                                  int prev_row, int prev_col )
{
    Q_UNUSED( prev_row );
    Q_UNUSED( prev_col );
    oldAccelText = TableWidgetActions->item( curr_row, curr_col )->text();
}

void ActionsDialog::validateAction( int row, int column )
{
    QTableWidgetItem* item;
    item = TableWidgetActions->item( row, column );
    QString accelText = QString( QKeySequence( item->text() ) );

    if( accelText.isEmpty() && item->text().isEmpty() )
        ; //  item->setText(oldAccelText);
    else
        item->setText( accelText );
}

void ActionsDialog::accept()
{
    for( qint32 row = 0; row < actionsList.size(); ++row )
        actionsList.at( row )->setShortcut( QKeySequence( TableWidgetActions
                                            ->item( row, 1 )->text() ) );
    mSaveShortcuts();
    QDialog::accept();
}

void ActionsDialog::mSaveShortcuts()
{
    settings->beginGroup( "Action" );
    foreach( const QAction * action, actionsList )
    settings->setValue( action->text(), QString( action->shortcut() ) );

    settings->endGroup();
}

void ActionsDialog::setupUi()
{
    if( objectName().isEmpty() )
        setObjectName( QString::fromUtf8( "ActionsDialog" ) );

    gridLayout = new QGridLayout( this );
    gridLayout->setObjectName( QString::fromUtf8( "gridLayout" ) );
    TableWidgetActions = new QTableWidget( this );
    TableWidgetActions->setObjectName( QString::fromUtf8( "TableWidgetActions" ) );
    TableWidgetActions->setShowGrid( true );

    gridLayout->addWidget( TableWidgetActions, 0, 0, 1, 1 );

    buttonBox = new QDialogButtonBox( this );
    buttonBox->setObjectName( QString::fromUtf8( "buttonBox" ) );
    buttonBox->setOrientation( Qt::Horizontal );
    buttonBox->setStandardButtons( QDialogButtonBox::Cancel
                                   | QDialogButtonBox::Ok
                                   | QDialogButtonBox::Apply );

    gridLayout->addWidget( buttonBox, 1, 0, 1, 1 );
    TableWidgetActions->setRowCount( m_actions.count() );
    TableWidgetActions->setColumnCount( 2 );
    QStringList TableWidgetHorizontalHeaderLabels;
    TableWidgetHorizontalHeaderLabels << tr( "Description" ) << tr( "Shortcut" );
    TableWidgetActions->setHorizontalHeaderLabels( TableWidgetHorizontalHeaderLabels );
    TableWidgetActions->verticalHeader()->hide();

    int row = 0;

    foreach( QAction * action, m_actions )
    {
        QTableWidgetItem* TableWidgetItemDesc = new QTableWidgetItem;
        TableWidgetItemDesc->setText( action->text() );
        TableWidgetActions->setItem( row, 0, TableWidgetItemDesc );

        QTableWidgetItem* TableWidgetItemShortcut = new QTableWidgetItem;
        TableWidgetItemShortcut->setText( QString( action->shortcut() ) );
        TableWidgetActions->setItem( row, 1, TableWidgetItemShortcut );
        actionsList.append( action );
        ++row;
    }

    retranslateUi();

    connect( TableWidgetActions, SIGNAL( currentCellChanged( int, int, int, int ) )
             , SLOT( recordAction( int, int, int, int ) ) );
    connect( TableWidgetActions, SIGNAL( cellChanged( int, int ) )
             , SLOT( validateAction( int, int ) ) );

    connect( buttonBox, SIGNAL( accepted() ), SLOT( accept() ) );
    connect( buttonBox, SIGNAL( rejected() ), SLOT( reject() ) );
    connect( buttonBox, SIGNAL( clicked( QAbstractButton* ) )
             , SLOT( buttonBoxClicked( QAbstractButton* ) ) );
}

void ActionsDialog::retranslateUi()
{
    setWindowTitle( QApplication::translate( "ActionsDialog", "Dialog", 0,
                    QApplication::UnicodeUTF8 ) );
}

void ActionsDialog::setFallbacksEnabled( bool enabled )
{
    if( settings )
        settings->setFallbacksEnabled( enabled );
}

void ActionsDialog::buttonBoxClicked( QAbstractButton* optionsDialogPushButton )
{
    if(( optionsDialogPushButton == buttonBox->button( QDialogButtonBox::Apply ) )
            | ( optionsDialogPushButton == buttonBox->button( QDialogButtonBox::Ok ) ) )
        mSaveShortcuts();

}

#include "actionsdialog.moc"
