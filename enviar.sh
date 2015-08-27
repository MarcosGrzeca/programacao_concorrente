#!/bin/sh
git add *.c *.sh *.txt
git commit -m $1
git push origin master

