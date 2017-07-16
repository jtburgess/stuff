#!/bin/bash
ip=mbtest-main.labs.acquiremedia.com
if [ "$1" = '1' ]
then
   ip=mbottest1.labs.acquiremedia.com
   shift
elif  [ "$1" = '2' ]
then
   ip=mbottest2.labs.acquiremedia.com
   shift
fi

if [ "$1" = 'n' ]
then
   setcol blue
   ssh nadmin@$ip
elif [ "$1" = 'r' ]
then
   setcol grey
   ssh root@$ip
else
   setcol aqua
   ssh $ip
fi
setcol 0
