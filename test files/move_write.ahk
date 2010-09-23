;
; AutoHotkey Version: 1.x
; Language:       English
; Platform:       Win9x/NT
; Author:         A.N.Other <myemail@nowhere.com>
;
; Script Function:
;	Template script (you can customize this template by editing "ShellNew\Template.ahk" in your Windows folder)
;

#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.
;msgbox script starting

sleep, 3000
Run, C:\Program Files\TeraCopy\teracopy.exe Copy "I:\WRITE.TXT" "C:\Users\mdunne\Documents\My Dropbox\uav data logger\test files" /OverwriteAll

;WinWait  ahk_pid %Howdy%
;Winhide, ahk_pid %Howdy%
;msgbox %Howdy%