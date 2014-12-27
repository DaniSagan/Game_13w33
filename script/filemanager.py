#! /usr/bin/python
# -*- coding=utf-8 -*-

import wx
import sys

def main():
    app = wx.App()

    if sys.argv[1] == 'o':
        openFileDialog = wx.FileDialog(None, "Open file", "", "",
                                       "Image file (*.jpg, *.png;)|*.jpg;*.png",
                                       wx.FD_OPEN | wx.FD_FILE_MUST_EXIST)
        if openFileDialog.ShowModal() == wx.ID_CANCEL:
            return 0
        sys.stdout.write(openFileDialog.GetPath().encode('utf-8'))
    elif sys.argv[1] == 's':
        saveFileDialog = wx.FileDialog(None, "Guardar archivo", "", "",
                                       "archivo PDF (*.pdf)|*.pdf",
                                       wx.FD_SAVE | wx.FD_OVERWRITE_PROMPT)
        if saveFileDialog.ShowModal() == wx.ID_CANCEL:
            return 0
        sys.stdout.write(saveFileDialog.GetPath().encode('utf-8'))
    elif sys.argv[1] == 'f':
        openFolderDialog = wx.DirDialog(parent=None, 
                                        message="Open city", 
                                        defaultPath="maps/")
        if openFolderDialog.ShowModal() == wx.ID_CANCEL:
            return 0
        sys.stdout.write(openFolderDialog.GetPath().encode('utf-8'))                             
    return 0

if __name__ == '__main__':
    main()
