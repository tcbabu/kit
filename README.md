
Note:
Kulina projects are X11 based and under Wayland it may have problems,
not really the problem of Kulina but Wayland. One may try to use
Xorg based sessions.

Also there is an attempt to add DEBIAN-12 based binary, it should
work on all latest distributions of Ubuntu, Fedora etc.

These Debian binaries may be available on in SourceForge, so one should
get it from Sourceforge, may not be Github.

-----------------------------------------------

Kit is graphical Text Editor of Linux. It is developed using Kulina Graphics Library
kglib. Hence to build from source you need to install kglib also.
25th Oct 2024
Tried kit on a version of Ubuntu and Slackware
Scrolling is very slow in Ubuntu(???) Not much problem
in Slackware

As on 19thOct 2024
There was some memory leak in the usage of IMAGEMAGIK,
hope there was better documentation or good examples.
Anyway tough to use the library, missing needed  explanations
or examples. It is always a problem to use external packake.
Ofcource GM was very useful. But mostly one need to use trail and
error to understand the usage, ecspecially 'DestroyImage'.
So not any change here, just a rebuild, so the tarball changes.
Of one need to use the updated 'kglib' package.

Again, get the updated 'kglib':

Updated Ver 2.0 as on 15th Oct 2024

I thought I won't do anything more in 'kit', but this
is Ver 2.0. I personally use 'kit' and observed that
few modifications are required in Copy/Paste and 'undo'
functionality. Also 'save' options is also changed.
I think, 'kit' is good now and I am relieved.

Update as on 13thSept 2024

Hope this is the final development.
If any bugs are observed those  may be fixed (encountering a bug is a chance).

I have been using vi since early 1980s. By the end of 1970s I got
my first chance to use an Editor, it came with Cyber 730 of CDC, that was
my first experience with an editor. Prior to that , it was card punching days.
Then UNIX machines started coming and vi appeared. Those were the days
of mostly text based terminals, and vi was great as it was available in
all types of Unix systems and even DOS machines.

Years had gone and now it is mostly graphics based systems and hence many
Graphical Editors are available, but vi still got relevance for system
admins and probably others also.

There are many editors available, probably there is no need for
one more. Still 'Kit' was initiated. It is not supposed to be feature rich,
the idea is something of a  simple editor which may not require a user
manual, with few trials one is expected get used to Kit.

Note: to build this Version one may require to download
the new version 'kglib tool kit', there are improvements 
to support some extra features and also to support 'freetype'
for rendering  fonts, earlier 'kglib' was using internal fonts.
