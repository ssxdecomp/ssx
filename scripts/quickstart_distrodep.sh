#!/bin/bash

# Distro-dependent logic for the setup script.

# This is a bit stupid, but avoids the gaping security vulnerablity
# of trying to source the file.
DISTRO_ID=$(cat /etc/os-release|grep "^ID="|cut -d'=' -f2)

# Adding a setup_[distro id] function here will magically enable support for that
# distribution in the quickstart script, automatically removing the
# warning nag for distros that aren't supported.

setup_arch() {
	sudo pacman -S lib32-gcc-libs ninja python-pipenv
}

setup_debian() {
	sudo dpkg --add-architecture i386
	sudo apt update
	sudo apt install libc6:i386 libgcc-s1:i386 libstdc++6:i386 gcc-multilib g++-multilib libc6-dev-i386
}

setup_ubuntu() {
	setup_debian
}
