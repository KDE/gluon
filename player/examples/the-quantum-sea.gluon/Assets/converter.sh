#! /bin/bash
#
# Converts all MP4 files in the current directory to MP3s.
#
for f in *mp3; do
 newname=`echo $f | tr ' ' '_' `
 mv "$f" $newname
 f=$newname
 mplayer $f -ao pcm:file=tmp.wav
 oggenc tmp.wav -o ${f/.mp3/.ogg}
 rm -f tmp.wav
done
