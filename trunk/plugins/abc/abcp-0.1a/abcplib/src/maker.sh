
if [ -f $1.re ] ; then 
  echo "Creating $1.c from $1.re"

  re2c -s $1.re >$1.c

  echo "$1.c created"
  echo

else
  echo "File \"$1.re\" not found"
fi
