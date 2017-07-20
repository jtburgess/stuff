#!/bin/sh
cd ~
rsync --recursive --links --times --compress --update --log-file=Desktop/rsync-bkup.log --prune-empty-dirs \
	--exclude='Downloads' \
	--exclude='*/*[Cc]ache*' \
	--exclude='[Tt]emp*' \
	--exclude='*.log' \
	--exclude='.Trash' \
	--exclude='Documents/RECYCLER' \
	--exclude='Movies' \
	--exclude='Music' \
	--exclude='*.hdd' \
	--exclude='Documents/Parallels/*/Snapshots' \
	--exclude='Documents/Parallels/*/Windows Applications/*' \
	--exclude='Documents/Parallels/*/Applications Menu.localized/*' \
	--exclude='Pictures' \
	--exclude='SVN' \
	.  $* /Volumes/backup/jburgess > Desktop/sync-backup.out
#  --dry-run

