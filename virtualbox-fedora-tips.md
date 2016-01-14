VirtualBox
==========

[https://www.virtualbox.org/](https://www.virtualbox.org/)

1. You’ll want to install the VirtualBox guest additions into your VM.

Before doing this install kernel headers by running the following command:

sudo dnf install kernel-devel

Once you’re booted into your VM you can install the guest additions from the Devices menu. Tell it to “Insert Guest Additions CD image...”. It should autorun. You’ll need to re-install the guest additions every time you update your kernel.

2. Install the VirtualBox 5.0.x Oracle VM VirtualBox Extension Pack.

This will add a bunch of features including USB support.

Fedora
======

[https://getfedora.org/](https://getfedora.org/)

1. You’ll want to update your VM every week or so with the following command:

sudo dnf update
