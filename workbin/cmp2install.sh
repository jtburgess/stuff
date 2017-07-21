#!/bin/bash
# intended to be run as a Makefile Target script
# e.g.
#Compare:
#	cmp2install.sh $(TARG_DIR) $(TARG_LIST)

# $Id$
SVNREV='$Revision$'
SVNURL='$URL$'
SVNDATE='$Date$'
bin=${bin-/nwsys/release/bin}
PATH=$bin:$PATH

. ga_options.sh

function Usage()
{
	echo Usage: `basename $0` install-directory list-of-files-to-compare
	exit 1
}

targ_dir=$1
shift

if [ ! -d $targ_dir ]
then
	echo ERROR: cant find target directory: $targ_dir
	Usage
fi

if [ $# -lt 1 ]
then
	echo ERROR: Missing target file list
	Usage
fi

for f in $*
do
	echo '###' $f : $targ_dir
	diff -w $f $targ_dir/$f
	if [ $? = 0 ]
	then echo No Change
	elif ${autoInstall-false}
	then nwinstall -c -s -q $targ_dir $f
	fi
	echo
done
