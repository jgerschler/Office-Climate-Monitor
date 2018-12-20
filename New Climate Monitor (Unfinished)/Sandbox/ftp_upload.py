#!/usr/bin/python
import ftplib

session = ftplib.FTP('ftpsite.com','username','password')
file = open('image.png','rb')
session.storbinary('STOR '+'image.png', file)

file.close()                                    
session.quit()
