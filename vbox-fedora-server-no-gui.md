Extension Pack
--------------

You'll want to install the VirtualBox 5.0.x Oracle VM VirtualBox Extension Pack. This will add a bunch of features including USB support, and it should improve performance.

Fedora Server Installer
-----------------------

https://getfedora.org/en/server/download/

Installation
--------------------

For "Software Selection" select "Minimal Install". Do everything else normally.

Updates
-------

You’ll want to update your VM as soon as you're done rebooting after installing, and every week or so after that with the following command:

    sudo dnf update

Install Basic Development Software
----------------------------------

    sudo dnf install git gcc kernel-devel vim tar bzip2 zip bc openssl-devel

Install VirtualBox Guest Additions
----------------------------------

Boot with VirtualBox guest additions in CD drive.

    sudo mkdir /media/cdrom
    sudo mount /dev/cdrom /media/cdrom
    cd /media/cdrom
    sudo ./VBoxLinuxAdditions.run
    sudo shutdown -h now

Boot up again and you should be all set.

Helpful Commands
----------------

* `man [command]`: Show manual page for a command.
* `sudo [command]`: Run the following command as root user.
* `ls`: List files in current directory.
* `cd [directory]`: Change current directory.
* `pwd`: Print out current directory.
* `mount [device] [directory]`: Mount a device to a directory.
* `clear`: Clears the text from your terminal.
* `df -h`: Disk usage information in a human-readable format.
* `nano`: Basic text editor.
* `vim`: More advanced text editor.
* `exit`: Exit current session to login screen.
* `shutdown -h now`: Shut down.
