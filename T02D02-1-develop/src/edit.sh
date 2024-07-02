#!/bin/bash

if [[ $# -ne 3 ]]; then
echo "error. no such arguments"
exit 1
fi

Rway="../""$1"
if [[ ! -f $Rway ]]; then
echo "error. no such file"
fi

sed -i ' ' -e "s/$2/$3/g" $Rway 
Fsize=$(stat -f%z "$Rway")
Fday=$(stat -f %Sm -t %Y-%m-%d' '%H:%M "$Rway")
Fsha=$(shasum -a 256 "$Rway"|cut -d' ' -f1)
Lout=""$1" - "$Fsize" - "$Fday" - "$Fsha" - sha256"


echo $Lout >> files.log

exit 0
