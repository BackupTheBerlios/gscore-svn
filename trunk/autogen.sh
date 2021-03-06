#! /bin/sh

aclocal-1.9 \
&& libtoolize \
&& automake-1.9 --gnu --add-missing \
&& autoconf

if [ -e ./configure ]; then
echo
echo "You can now run ./configure"
echo
else
echo
echo "Failure building the configure script."
echo "You may miss required tool (aclocal 1.9, libtoolize, automake 1.9, autoconf 2.5x) to build gscore"
echo "Please install the appropriate software and re-run autogen.sh"
echo "This might also happen if you don't have the m4 provided as a subdirectory in this package in the directory"
echo "where aclocal will find them. Just copy ./m4/* in, usually, /usr/share/aclocal."
echo "Or, it can also come from a configure.ac mistake (then it's my business ;)). Please report your issue on the"
echo "gscore mailing list. See http://www.gscore.org for informations on how to subscribe."
echo
fi
