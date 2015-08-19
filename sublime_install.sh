#!/bin/sh
# Sublime Text 3 install with Package Control (last update: 12 July 2015)
#
# No need to download this script, just run it on your terminal:
#
# $ curl -L git.io/sublimetext | sh
#
# When you need to update Sublime Text, run this script again.
# Detect the architecture
if [ "$(uname -m)" = "x86_64" ]; then
ARCHITECTURE="x64"
else
ARCHITECTURE="x32"
fi
# Fetch the latest build version number (thanks daveol)
BUILD=$(echo $(curl http://www.sublimetext.com/3) | sed -rn "s#.*The latest build is ([0-9]+)..*#\1#p")
URL="http://c758482.r82.cf2.rackcdn.com/sublime_text_3_build_{$BUILD}_{$ARCHITECTURE}.tar.bz2"
INSTALLATION_DIR="/opt/sublime_text"
# Download the tarball, unpack and install
curl -o $HOME/st3.tar.bz2 $URL
if tar -xf $HOME/st3.tar.bz2 --directory=$HOME; then
# Remove the installation folder and the symlink, they might already exist
sudo rm -rf $INSTALLATION_DIR /bin/subl
sudo mv $HOME/sublime_text_3 $INSTALLATION_DIR
sudo ln -s $INSTALLATION_DIR/sublime_text /bin/subl
fi
rm $HOME/st3.tar.bz2
# Package Control - The Sublime Text Package Manager: https://sublime.wbond.net
curl -o $HOME/Package\ Control.sublime-package https://sublime.wbond.net/Package%20Control.sublime-package
sudo mv $HOME/Package\ Control.sublime-package "$INSTALLATION_DIR/Packages/"
# Add to applications list (thanks 4ndrej)
sudo ln -s $INSTALLATION_DIR/sublime_text.desktop /usr/share/applications/sublime_text.desktop
# Set the icon (thanks gcaracuel)
sudo sed -i.bak 's/Icon=sublime-text/Icon=\/opt\/sublime_text\/Icon\/128x128\/sublime-text.png/g' /usr/share/applications/sublime_text.desktop
echo ""
echo "Sublime Text 3 installed successfully!"
echo "Run with: subl"
@mariosant
mariosant commented on 4 Feb 2014

Hmmm... I would appreciate if it would show at the applications list of gnome 3.10. I tried copying the desktop entry into the /usr/share/applications but it didn't work.
@simonewebdesign
Owner
simonewebdesign commented on 22 Feb 2014

Yeah, that would be really great. If anyone knows how to do that, please contribute.

EDIT: nevermind, I did it myself.

Anyway you are right; looks like just moving the desktop file into /usr/share/applications or ~/.local/share/applications doesn't work for some reason, so in the script I just added a new desktop entry manually.
@Soufien
Soufien commented on 6 Mar 2014

Thx a lot Simon ;) it was very useful !! ;)
@diek
diek commented on 11 Mar 2014

I am getting the following error:
./install_sublime_text3.sh: line 38: warning: here-document at line 24 delimited by end-of-file (wanted `EOF')
@simonewebdesign
Owner
simonewebdesign commented on 16 Mar 2014

@diek: that's weird. Try to run it again with:

curl https://gist.githubusercontent.com/simonewebdesign/8507139/raw/e1e7f6a302d44902dc0805eaf85344f1c4e84425/install_sublime_text.sh | sh

@alexcreasy
alexcreasy commented on 9 Apr 2014

Works like a charm, thanks!
@heichblatt
heichblatt commented on 26 Apr 2014

Just wanted to mention a script I built based on this.
@whitel
whitel commented on 25 Jul 2014

@simonewebdesign and @qboss, you need to restart gnome to pick up new desktop files. For example, hit Alt-F2, type "r" (without the quotes) and click enter.
@dee1337
dee1337 commented on 27 Jul 2014

my vm with fedora 19 32bit ran into an error using this version
bash: /usr/bin/subl: cannot execute binary file
...so i added 32bit support:
https://gist.github.com/dee1337/80b24a66c5e6a0cd97d9
@allanlewis
allanlewis commented on 29 Aug 2014

Sublime Text just released build 3065...
@DanMoto
DanMoto commented on 29 Aug 2014

Love it! Works like a charm! Thank you!
@simonewebdesign
Owner
simonewebdesign commented on 1 Sep 2014

FYI: I'm working on a new version of the script that will install the latest build (3065) and will detect the correct OS architecture (i386 or x64).
@bhalothia
bhalothia commented on 17 Sep 2014

Thanks a ton! :)
@4ndrej
4ndrej commented on 22 Oct 2014

there is desktop file already (at least in latest sublime text 3 v3.065), so the extraction should go to sublime_text (not the sublime_text_3) and the last part of installer could be changed to
ln -s /opt/sublime_text/sublime_text.desktop /usr/share/applications/sublime_text.desktop
@dimitrismistriotis
dimitrismistriotis commented on 12 Dec 2014

Maybe because of the curl command we should guard against some exited OS/X users, maybe on line 11:

if [ `uname` = 'Darwin' ]; then echo 'Not for OS/X, use brew cask'; exit -1; fi

@simonewebdesign
Owner
simonewebdesign commented on 16 Dec 2014

Thanks for your input Dimitri, however I believe there's no need to alert OS X users as they already have a .dmg file at their disposal from the official site, so they probably won't search for an installation script anyway
@pachecovit
pachecovit commented on 8 Jan

How add a 'official' icon on shortcut? I have OCD :'(
@dimitrismistriotis
dimitrismistriotis commented on 8 Jan

For elementaryOS
After installing, based on http://elementaryos.org/answers/create-shortcut-of-terminal-commands-in-dock-panel:

subl ~/.local/share/applications/sublime.desktop

[Desktop Entry]
Type=Application
Name=Sublime Text
GenericName=Sublime Text
Exec=subl
Terminal=false
Icon=/opt/sublime_text/Icon/128x128/sublime-text.png

Maybe in another version do a check and append it on bottom?
@askmatey
askmatey commented on 16 Feb
Clean GNOME Desktop Entry

Tested with Fedora 21 x86_64:

$ vim /usr/share/applications/sublime-desktop

[Desktop Entry]
Encoding=UTF-8
Name=Sublime Text
GenericName=Sublime Text
Comment=Sublime Text is a sophisticated text editor for code, markup and prose.
Exec=subl
Terminal=false
Icon=/usr/share/sublime-text/Icon/256x256/sublime-text.png
Type=Application
MimeType=text/plain;
Categories=Application;Development;Editor;Utility;TextEditor;

However, the Fedora guideline for package naming recommends to use dashes instead of underscores (for packages and folders):

    ...

    When naming packages for Fedora, the maintainer must use the dash '-' as the delimiter for name parts.

RTFM and stop using underscore_case.
@ahockersten
ahockersten commented on 20 Mar

I started fixing som annoyances I had with this script, and basically ended up rewriting the whole thing, see:
https://gist.github.com/ahockersten/9781d1233e2bb125b458

Changes:

    Now has an uninstaller (since I have changed a bunch of paths, this won't work if you previously installed with another version of the script)
    Icons are installed correctly
    No sudo inside script, it should be run as root or using sudo instead
    Better (but not perfect) error handling
    Better install directories (uses /usr/local for the subl script)
    Installing Package Control is now optional (use -p)
    Previously, if you ran "subl" from the command line and used the desktop shortcut, you would get two icons in Gnome's taskbar. I've fixed so that this no longer happens.

@SystemDisc
SystemDisc commented on 30 Mar

For anyone who wants an RPM for Sublime Text 3 with everything included: https://mega.co.nz/#!eAAkARQR!dvMZGO49xxxPt_tuRrhYip7IIfhp9dhQzhEmT5i9S14

[systemdisc@localhost ~]$ rpm -qp sublime-3-1.x86_64.rpm -l
/opt/sublime_text/Icon/128x128/sublime-text.png
/opt/sublime_text/Icon/16x16/sublime-text.png
/opt/sublime_text/Icon/256x256/sublime-text.png
/opt/sublime_text/Icon/32x32/sublime-text.png
/opt/sublime_text/Icon/48x48/sublime-text.png
/opt/sublime_text/Packages/ASP.sublime-package
/opt/sublime_text/Packages/ActionScript.sublime-package
/opt/sublime_text/Packages/AppleScript.sublime-package
/opt/sublime_text/Packages/Batch File.sublime-package
/opt/sublime_text/Packages/C#.sublime-package
/opt/sublime_text/Packages/C++.sublime-package
/opt/sublime_text/Packages/CSS.sublime-package
/opt/sublime_text/Packages/Clojure.sublime-package
/opt/sublime_text/Packages/Color Scheme - Default.sublime-package
/opt/sublime_text/Packages/D.sublime-package
/opt/sublime_text/Packages/Default.sublime-package
/opt/sublime_text/Packages/Diff.sublime-package
/opt/sublime_text/Packages/Erlang.sublime-package
/opt/sublime_text/Packages/Go.sublime-package
/opt/sublime_text/Packages/Graphviz.sublime-package
/opt/sublime_text/Packages/Groovy.sublime-package
/opt/sublime_text/Packages/HTML.sublime-package
/opt/sublime_text/Packages/Haskell.sublime-package
/opt/sublime_text/Packages/Java.sublime-package
/opt/sublime_text/Packages/JavaScript.sublime-package
/opt/sublime_text/Packages/LaTeX.sublime-package
/opt/sublime_text/Packages/Language - English.sublime-package
/opt/sublime_text/Packages/Lisp.sublime-package
/opt/sublime_text/Packages/Lua.sublime-package
/opt/sublime_text/Packages/Makefile.sublime-package
/opt/sublime_text/Packages/Markdown.sublime-package
/opt/sublime_text/Packages/Matlab.sublime-package
/opt/sublime_text/Packages/OCaml.sublime-package
/opt/sublime_text/Packages/Objective-C.sublime-package
/opt/sublime_text/Packages/PHP.sublime-package
/opt/sublime_text/Packages/Pascal.sublime-package
/opt/sublime_text/Packages/Perl.sublime-package
/opt/sublime_text/Packages/Python.sublime-package
/opt/sublime_text/Packages/R.sublime-package
/opt/sublime_text/Packages/Rails.sublime-package
/opt/sublime_text/Packages/Regular Expressions.sublime-package
/opt/sublime_text/Packages/RestructuredText.sublime-package
/opt/sublime_text/Packages/Ruby.sublime-package
/opt/sublime_text/Packages/SQL.sublime-package
/opt/sublime_text/Packages/Scala.sublime-package
/opt/sublime_text/Packages/ShellScript.sublime-package
/opt/sublime_text/Packages/TCL.sublime-package
/opt/sublime_text/Packages/Text.sublime-package
/opt/sublime_text/Packages/Textile.sublime-package
/opt/sublime_text/Packages/Theme - Default.sublime-package
/opt/sublime_text/Packages/Vintage.sublime-package
/opt/sublime_text/Packages/XML.sublime-package
/opt/sublime_text/Packages/YAML.sublime-package
/opt/sublime_text/changelog.txt
/opt/sublime_text/crash_reporter
/opt/sublime_text/plugin_host
/opt/sublime_text/python3.3.zip
/opt/sublime_text/sublime.py
/opt/sublime_text/sublime_plugin.py
/opt/sublime_text/sublime_text
/usr/local/bin/sublime_text
/usr/share/applications/sublime_text.desktop

@taotie12010
taotie12010 commented on 5 Apr

thx,it is very helpful.
@jzgdev
jzgdev commented on 5 Jun

Thanks for this, worked perfectly on Fedora 22
@dud3
dud3 commented on 20 Jun

This just doesn't work on Fedora 22: /usr/local/bin/subl: line 2: [: ==: unary operator expected
@simonewebdesign
Owner
simonewebdesign commented on 23 Jun

@dud3: some other people reported the same problem many times, but I haven't been able to reproduce it since then. Could you provide some more details (e.g. OS architecture, shell)?

Have you tried running the script again?
@FlorianMiesenberger
FlorianMiesenberger commented on 2 Jul

@dud3: I have got the same error on Fedora 22 ... :-1:
@kane-thornwyrd
kane-thornwyrd commented on 7 Jul

@dud3 and the others, just add a check for the args count...

#!/bin/sh
if [ $# -gt 0 ] && [ ${1} == "--help" ]; then
/usr/local/sublime-text_3/sublime_text --help
else
/usr/local/sublime-text_3/sublime_text $@ > /dev/null 2>&1 &
fi

@simonewebdesign
Owner
simonewebdesign commented on 12 Jul

@all: Works on Fedora 22 Workstation (64-Bit).
I haven't tested other platforms though, so please let me know if you have any issues at all.
@tiny-software
Markdown supported
Edit in fullscreen
Write Preview

Attach images by dragging & dropping or selecting them.

