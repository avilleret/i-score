#!/bin/bash

## USAGE : 
## ./computeFolder.sh UBUNTU32
##         OR
## ./computeFolder.sh UBUNTU64
##         OR
## ./computeFolder.sh MACOS32
##         OR
## ./computeFolder.sh MACOS64

OS=$1

INSTALL_PATH="/home/luc/Documents/workspace/acousmoscribe/installation/"

if [ "$OS" = "UBUNTU32" ]
then
    INSTALL_UBUNTU_PATH="/home/luc/Documents/workspace/acousmoscribe/installation/acousmoscribe_ubuntu_32"
elif [ "$OS" = "UBUNTU64" ]
then
    INSTALL_UBUNTU_PATH="/home/luc/Documents/workspace/acousmoscribe/installation/acousmoscribe_ubuntu_64"
fi

LOCAL_BIN_PATH="/home/luc/Documents/workspace/acousmoscribe/acousmoscribe"
LOCAL_SHARE_DOCS_PATH=$INSTALL_PATH"ubuntuDocs/shareDocs/"
LOCAL_DEBIAN_PATH=$INSTALL_PATH"ubuntuDocs/DEBIAN/"

ROOT_USR_PATH="/usr/"
ROOT_LIB_PATH="/usr/bin/"
ROOT_LIB_PATH="/usr/local/lib/"
ROOT_INCLUDE_PATH="/usr/local/include/"
ROOT_SHARE_PATH="/usr/local/share/"

INSTALL_USR_PATH=$INSTALL_UBUNTU_PATH$ROOT_USR_PATH
INSTALL_LIB_PATH=$INSTALL_UBUNTU_PATH$ROOT_LIB_PATH
INSTALL_INCLUDE_PATH=$INSTALL_UBUNTU_PATH$ROOT_INCLUDE_PATH
INSTALL_BIN_PATH=$INSTALL_UBUNTU_PATH$ROOT_BIN_PATH
INSTALL_SHARE_PATH=$INSTALL_UBUNTU_PATH$ROOT_SHARE_PATH
INSTALL_DEBIAN_PATH=$INSTALL_UBUNTU_PATH"/DEBIAN/"

# UBUNTU 64

echo "CREATING INSTALLATION REPOSITORY"

sudo mkdir -p $INSTALL_USR_PATH
sudo mkdir -p $INSTALL_LIB_PATH
sudo mkdir -p $INSTALL_INCLUDE_PATH
sudo mkdir -p $INSTALL_BIN_PATH

if [ "$OS" = "UBUNTU32" ] || [ "$OS" = "UBUNTU64" ]
then 
{
    sudo mkdir -p $INSTALL_SHARE_PATH
    sudo mkdir -p $INSTALL_DEBIAN_PATH
}
elif [ "$OS" = "MACOS32" ] || [ "$OS" = "MACOS64" ]
then
{
    echo "MACOS : TODO"
}
else
{
    echo "Unhandled OS"
}
fi

echo "COPYING BINARY"

sudo cp -r $LOCAL_BIN_PATH $INSTALL_BIN_PATH

echo "COPYING INCLUDES"

if [ "$OS" = "UBUNTU32" ] || [ "$OS" = "UBUNTU64" ]
then
    for i in "DeviceManager/" "gecode/" "IScore/" "libxml2/" 
    do
	sudo rm -r $INSTALL_INCLUDE_PATH$i
	sudo cp -r $ROOT_INCLUDE_PATH$i $INSTALL_INCLUDE_PATH
    done
elif [ "$OS" = "MACOS32" ] || [ "$OS" = "MACOS64" ]
then
    echo "MACOS : TODO"
else
    echo "Unhandled OS"
fi

echo "COPYING LIBRARIES"

if [ "$OS" = "UBUNTU32" ] || [ "$OS" = "UBUNTU64" ]
then
    sudo rm -r $INSTALL_LIB_PATH"/IScore"
    
    for i in "IScore/" "libDeviceManager.a" "libIscore.a" "libgecode*.a" "libxml*.a" "libxml*.so*"
    do
	if [ $i = "IScore/" ]
	then
	    sudo cp -r $ROOT_LIB_PATH$i $INSTALL_LIB_PATH$i
	else
	    sudo cp -r $ROOT_LIB_PATH$i $INSTALL_LIB_PATH
	fi
    done
elif [ "$OS" = "MACOS32" ] || [ "$OS" = "MACOS64" ]
then
    echo "MACOS : TODO"
else
    echo "Unhandled OS"
fi

if [ "$OS" = "UBUNTU32" ] || [ "$OS" = "UBUNTU64" ]
then
    echo "COPYING SHARE DOCS"
    
    sudo rm -r $INSTALL_SHARE_PATH
    sudo cp -r $LOCAL_SHARE_DOCS_PATH $INSTALL_SHARE_PATH
    
    echo "COPYING DEBIAN FILES"
    
    sudo rm -r $INSTALL_DEBIAN_PATH
    sudo cp -r $LOCAL_DEBIAN_PATH $INSTALL_DEBIAN_PATH
    
    sudo chown root -R $INSTALL_USR_PATH
    sudo chmod u+x $INSTALL_DEBIAN_PATH"post"*
    sudo chmod u+x $INSTALL_DEBIAN_PATH"post"*
    
    if [ "$OS" = "UBUNTU32" ]
    then
	sudo mv $INSTALL_DEBIAN_PATH"control_32" $INSTALL_DEBIAN_PATH"control"
	sudo rm $INSTALL_DEBIAN_PATH"control_64"
    elif [ "$OS" = "UBUNTU64" ]
    then
	sudo mv $INSTALL_DEBIAN_PATH"control_64" $INSTALL_DEBIAN_PATH"control"
	sudo rm $INSTALL_DEBIAN_PATH"control_32"
    fi
elif [ "$OS" = "MACOS32" ] || [ "$OS" = "MACOS64" ]
then
    echo "MACOS : TODO"
else
    echo "Unhandled OS"
fi