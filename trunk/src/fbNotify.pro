#     fbNotify: A Facebook notification system.
#     Copyright (C) 2006 fbNotify Team.
#
#     This program is free software; you can redistribute it and/or modify
#     it under the terms of the GNU General Public License as published by
#     the Free Software Foundation; either version 2 of the License, or
#     (at your option) any later version.
#
#     This program is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#     GNU General Public License for more details.
#
#     You should have received a copy of the GNU General Public License along
#     with this program; if not, write to the Free Software Foundation, Inc.,
#     51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.


#QT configuration 
TEMPLATE = app
DEPENDPATH += . core kernel ui
INCLUDEPATH += .
TARGET = fbNotify
QT +=  xml \
       network


#Resources
RESOURCES += fbNotify.qrc

#Primary source code
HEADERS +=  fbNotify.h \
            FBNApplication.h
SOURCES +=  fbNotify.cpp \
            FBNApplication.cpp \
            FBNApplication_mac.cpp \
            FBNApplication_win32.cpp

#Core source code
HEADERS +=  core/FBNCore_includes.h \
            core/FBNCore.h \
            core/FBNLocalization.h \
            core/FBNLogger.h \
            core/FBNServices.h \
            core/FBNSettings.h \
            core/md5.h
SOURCES +=  core/FBNCore.cpp \
            core/FBNLocalization.cpp \
            core/FBNLogger.cpp \
            core/FBNServices.cpp \
            core/FBNSettings.cpp \
            core/md5.c

#Kernel/Facebook API abstraction source code
HEADERS +=  kernel/FBNKernelEnums.h \
            kernel/FBNKernelStructs.h \
            kernel/facebook.h \
            kernel/facebook.auth.h \
            kernel/facebook.error.h \
            kernel/facebook.events.h \
            kernel/facebook.friends.h \
            kernel/facebook.messages.h \
            kernel/facebook.photos.h \
            kernel/facebook.pokes.h \
            kernel/facebook.users.h \
            kernel/facebook.wall.h

SOURCES +=  kernel/FBNKernelEnums.cpp \
            kernel/FBNKernelStructs.cpp \
            kernel/facebook.auth.cpp \
            kernel/facebook.error.cpp \
            kernel/facebook.events.cpp \ 
            kernel/facebook.friends.cpp \
            kernel/facebook.messages.cpp \
            kernel/facebook.photos.cpp \
            kernel/facebook.pokes.cpp \
            kernel/facebook.users.cpp \
            kernel/facebook.wall.cpp

#Kernel source code
HEADERS +=  kernel/FBNKernel_includes.h \
            kernel/FBNKernel.h \
            kernel/FBNHttp.h \
            kernel/FBNUrlBuilder.h
SOURCES +=  kernel/FBNKernel.cpp \
            kernel/FBNHttp.cpp \
            kernel/FBNUrlBuilder.cpp

#UI source code
HEADERS +=  ui/FBNNotificationManager.h \
            ui/FBNNotificationWindow.h \
            ui/FBCaptionButton.h \
            ui/FBLoginNotification.h \
            ui/FBMessageNotification.h \
            ui/FBNAboutPanel.h \
            ui/FBNLinkButton.h \
            ui/FBNLoginButton.h \
            ui/FBNAnimation.h \
            ui/FBNFadeInAnimation.h \
            ui/FBNFadeOutAnimation.h \
            ui/FBNConfigurationPanel.h \
            ui/FBNConfigurationPanelMaster.h \
            ui/FBNConfigurationWindow.h \
            ui/FBNLoginPanel.h \
            ui/FBNNotificationsPanel.h \
            ui/FBNotification.h \
            ui/FBNotificationCaptionBar.h \
            ui/FBNotificationCloseButton.h \
            ui/FBNotificationManager.h \
            ui/FBNotificationsDialog.h \
            ui/FBNotificationThread.h \
            ui/FBNPanelTab.h \
            ui/FBNResourceManager.h \
            ui/FBNSectionHeading.h \
            ui/FBNTrayIcon.h \
            ui/FBNUI_includes.h \
            ui/FBNWarningBox.h \
            ui/FBPokeNotification.h \
            ui/FBTimer.h \
            ui/FBWallNotification.h \
            ui/FBWindow.h \
            ui/FBNCloseButton.h \
            ui/FBNEffects.h \
            ui/FBNNotificationSettingsList.h \
            ui/FBNLoginNotification.h
SOURCES +=  ui/FBNNotificationManager.cpp \
            ui/FBNNotificationWindow.cpp \
            ui/FBCaptionButton.cpp \
            ui/FBLoginNotification.cpp \
            ui/FBMessageNotification.cpp \
            ui/FBNAboutPanel.cpp \
            ui/FBNLoginPanel.cpp \
            ui/FBNLinkButton.cpp \
            ui/FBNLoginButton.cpp \
            ui/FBNAnimation.cpp \
            ui/FBNFadeInAnimation.cpp \
            ui/FBNFadeOutAnimation.cpp \
            ui/FBNConfigurationPanel.cpp \
            ui/FBNConfigurationPanelMaster.cpp \
            ui/FBNConfigurationWindow.cpp \
            ui/FBNNotificationsPanel.cpp \
            ui/FBNotification.cpp \
            ui/FBNotificationCaptionBar.cpp \
            ui/FBNotificationCloseButton.cpp \
            ui/FBNotificationManager.cpp \
            ui/FBNotificationsDialog.cpp \
            ui/FBNotificationThread.cpp \
            ui/FBNPanelTab.cpp \
            ui/FBNResourceManager.cpp \
            ui/FBNSectionHeading.cpp \
            ui/FBNTrayIcon.cpp \
            ui/FBNWarningBox.cpp \
            ui/FBPokeNotification.cpp \
            ui/FBTimer.cpp \
            ui/FBWallNotification.cpp \
            ui/FBWindow.cpp \
            ui/FBNCloseButton.cpp \
            ui/FBNEffects_win32.cpp \
            ui/FBNNotificationSettingsList.cpp \
            ui/FBNLoginNotification.cpp

#Platform specific options
win32 {
LIBS     +=  "c:/MinGW/lib/libcurl.dll.a"
DESTDIR   =  "../etc/install/win32/bin/"
RC_FILE   =  "fbNotify.rc"
}
macx {
CONFIG  +=  x86 ppc
LIBS    +=  "/usr/lib/libcurl.dylib"
}