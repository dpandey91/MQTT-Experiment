#!/bin/bash

while read compareFile1 <&3 && read compareFile2 <&4; do     
    
   #echo "Comparing file - $compareFile"

#if diff "$compareFile1" "$compareFile2" >/dev/null ; then
 
#   echo Same
 #else
      echo $compareFile1  $compareFile2 >> output.txt
#echo $compareFile2

 #fi 
done 3<cOutTime.txt 4<pOutTime.txt
