#!/bin/sh
git add *.c
git add *.sh
git commit -m $1
git push origin master

