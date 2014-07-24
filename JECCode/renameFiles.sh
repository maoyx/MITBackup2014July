#! /bin/sh -f
echo "Renaming txt files........... :)"

ls  | awk '/.txt/{of=$1} {if(substr($1,8,1)=="P"){{nf1= substr($1,1,4)} {nf2=substr($1,11)} {print "cp " $1 " renamedTXTfiles/"nf1 nf2}}}' | sh
ls  | awk '/.txt/{of=$1} {if(substr($1,8,1)=="C"){{nf1= substr($1,1,4)} {nf2=substr($1,13)} {print "cp " $1 " renamedTXTfiles/"nf1 nf2}}}' | sh



