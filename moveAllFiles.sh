#!/bin/bash
source = "/mnt/hgfs/Shared/lab2/New\ Folder"
dest = "/usr/src/linux-2.4.18-14custom"

cp $source/todo_api.h $dest/todo_api.h

entry = arch/i386/kernel/entry.S
cp $source/$entry $dest/$entry

todo_headder = include/linux/sys_calls_todo.h
cp $source/$todo_headder $dest/$todo_headder

sched = include/linux/sched.h
cp $source/$sched $dest/$sched

cp $source/kernel/exit.c $dest/kernel/exit.c
cp $source/kernel/fork.c $dest/kernel/fork.c
cp $source/kernel/Makefile $dest/kernel/Makefile
cp $source/kernel/sys_calls_todo.c $dest/kernel/sys_calls_todo.c



