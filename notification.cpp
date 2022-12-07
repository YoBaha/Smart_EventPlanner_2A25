#include "notification.h"
notification::notification()
{

}

void notification::notification_ajout()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion espace ","nouveauelle espace a  ete ajoutée ",QSystemTrayIcon::Information,15000);

}

void notification::notification_modifier()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion espace ","espace a  ete modifier ",QSystemTrayIcon::Information,15000);

}


void notification::notification_supprimer()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion espace ","espace a  ete supprimer ",QSystemTrayIcon::Information,15000);

}

