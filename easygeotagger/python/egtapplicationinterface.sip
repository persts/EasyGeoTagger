
class EgtApplicationInterface : QObject
{

%TypeHeaderCode
#include <egtapplicationinterface.h>
%End

  public:
    /*! \brief Constructor */
    EgtApplicationInterface( );

    /*! \brief Wrapper for the EgtDataProviderManager::avilableProviders( ) */
    QStringList availableProviders( );

    /*! \brief Wrapper for the EgtDataProviderManager::dataProvider( ) */
    EgtDataProvider* dataProvider( QString );

    QMainWindow* gui( );

    /*! \brief get the position of the first visible widget */
    QPoint positionOfFirstVisibleWidget( );

    /*! \brief Find a particular widget */
    QPoint positionOfWidget( QString );

    /*! \brief Set a pointer to the main window */
    //void setGui( EgtMainWindow* theMainWindow );

    /*! \brief Set the data provider manager */
    //void setDataProviderManager( EgtDataProviderManager* theManager );

    /*! \brief Set the application plugin manager */
    //void setPluginManager( EgtPluginManager* thePluginManager );

  public slots:
    /*! \brief Accepts a key and data data pair for re broadcasting */
    void acceptKeyValuePair( QString, QString );

    /*! \brief Slot to accept item selections */
    void acceptModelIndexSelections( const QModelIndex& theIndex );

    /*! \brief Slot to accept requests to load a single plugin for a directory of plugins */
    void loadPlugins( QString );

    /*! \brief Slot to accept requests to fresh the file browser */
    void refreshFileBrowser( );

  signals:
    /* \brief Signal to broadcast a mouse click event in the file browser */
    void indexSelected( const QModelIndex& );

    /*! \brief Rebroadcasts key and tag data pair */
    void keyValuePair( QString, QString );

    /*! \brief Broadcast a load plugin request intended for the plugin manager */
    void loadPluginRequest( QString );
};
