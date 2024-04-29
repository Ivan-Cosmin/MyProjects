# Twixt Project

## [Project presentation](https://www.youtube.com/watch?v=tIcxJhsYmOc)

## Project setup

### Download Qt
Install Qt 6.5.3 2019 MSVC x64 [here](https://www.qt.io/download-qt-installer-oss?hsCtaTracking=99d9dd4f-5681-48d2-b096-470725510d34%7C074ddad0-fdef-4e53-8aa8-5e8a876d6ab4)

![Capture](https://i.imgur.com/CtanKVi.png)

### Download Qt Visual Studio Tools

Once entered in Visual Studio, go to Extensions > Manage Extensions > Online and search for "Qt Visual Studio Tools".  
To install the extension, **you have to quit Visual Studio** and a downloader will pop up.  

Keep in mind: **if you don't see the extension**, you must **update** your Visual Studio to the last version!  

![Capture](https://i.imgur.com/L5qtpDr.png)

### Add Version 
Enter again in Visual Studio, then go to Extensions > Qt Vs Tools > Qt versions  

![Capture](https://i.imgur.com/5tcwdHO.png)

Click on **+ add new Qt Version** _(step 1)_, then click the folder icon on the path column _(step 2)_  

![Capture](https://i.imgur.com/ZgShPqu.png)

Go to Qt install folder and select: 6.5.3 > msvc2019_64 > bin > qmake.exe  

![Capture](https://i.imgur.com/AexygEN.png)  

Now you can run the Visual Studio project!

