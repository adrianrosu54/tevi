# TeVi

***TeVi*** (Text-View) is a CLI application for displaying webcam image input
directly in the terminal. It enables the user to print images to the screen
using **ANSI escape sequences**.

```ascii
#MMMMMMM%%%%M%%M%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%@%@%%%%%%%%%@@%%%%%%%%%%%%%%%%%
MMMMMMM%%%%%%%%%%%%%%%%%%%%%%%%%@@@@@%%%%@@@@@@@@%@@@%@@@@%%@@@@@@@%%@%%%%%%%%%%
#MMM#xMM%%%%%%%%%%%%%%%M%%%%%%%M%%%%@%%%%@%@@@@@@@%@@@@@@@@%%%@@@@@@%%@%%%%@%%%%
#MMMMkMM%%%%%%%%%%%%%%@@@@@@@MM#M%%M%%%%%%@@@@@@@@@@@@@@@@@@@@@@@%@@@%%%%%%%%%%%
M##M#k%M%%%%%%%%M%%@@%%@@@#M##M#M%##MM#M%%%%%@@@@@@@@@@@@@@@@@@@@%%%%%%%%%%%%%%M
##z##Mk#M%%%%MMM@@@%M##*xzkz=!=##%#M####M%%%%@@@@@@@@@@@@@@@%%@%%%%%%%%%%%%%%%MM
##x##z##MMM#M%@@@%M#zxx=!-+!+--|kM#MM%M%%%#MM%%@@@@@@@@@@%%%%%%%%%%%%%%%%%%%%%%M
##z#######M%%@@@@@++-+-!!--!--!!!|*kM##MMMMM%M%%@@@@@@@@@@@@%%%%%%%%%%%%%%%%%%%M
#M#######%@@%@@@@@#|+|!+!-+-!!--!+*%##M##%#%MMMM%@@@@@@@@@@@@%%@%%%%%%%%%%%%%%%%
**x*xz#%%%%%%#M@@@%%@%k*!!+!+!-+|#M%M##MMM%#kM%%%%%@@@@@@@@@@@@@@@@@@%%@%%%%%%%%
=*kM%%%%%#kMkkM%M%k##MMzkz||!-!+M@%@%%%M@%#M#MM%%%%@@@@@@@@@@@@@@@@@@@%%%%%%%%%%
%M##kz##**##Mkk##Mzk##x##M#kx|!|%@@@@%%%%%%M%%%%%%%@@@@@%%@@@@@@@@@@@@%%%%%%%%@%
M#kzkkk#*|!!xMkkkMx=*=!|=zz=!!-=%@%@@%%%%%%%%%%%@@@%@@%%%%%%%%%%@%%%%@@@%%%%@@%#
#zzk==x*z||+*kkzzk#M#z|+-+=+!!++#%%%%%%%%%%%%%%%%%@%%%%%%%%@%%%%%%%%%%%%M%@@@%Mz
#k*=#*=!+-++=z|=++=kx*+-+!*x|=!!=k%%%%%%%%%%%%%%%%%%%%%%%%%%%%MMMMMMMk##%@@%##*+
k###k#kx*|+++++++!+!+!|+|#@@@@%k++xk#######MM#####MMM#####kkkkzzzzx*|xM@@@%##x!!
k#zk#M#zzkzx=|++!++!++xM@@@@@@@@%*+=xzxxxxxxxxxxxxzxxxxxxxxx****==**M@%@%z*|!!!+
#z!==x!=zzzzk#kxxxx*x#@@@@@MM@@@@%#kxxx**====***zM@%k*********xkk#%@M##*|!!|*zM%
%M|!|!+!+=xzxxk=xk@@@@%%%#M##%%@%@@MM#%#x===*xx#z*kkk#k==xkzkMMM%M%z#xxxzkxxk%%%
%%%M#zzk#M%@%%%#M%@@%%#M####%M#M#zM%%MzMMkkz*|++|||==**xxkM#MM#**xzkM#kz*z#%MMkx
%%M##M%@@M#%@%%##M#%MMM#M@@%M#%*z**###k+*x=k=xM%%%%%%%%%MMMMM%%%#z**=|=kM#kx*=+!
%%%M##kkM#MM|kk#M##%%%@M##M##M@z+=*k*=k#z*+-+=+=k%%%#M%%M#kzzxx*||||zM%%%k**=|==
M%#x=zx=||x++xkk####Mk%M##kkk#M@x!!!*xxx*xzx==|+!!=xkx=|*===||==|*#%M#zx=+|*=|==
Mx!+==+!!++kzxx*=*#M###MMk++*=#kM#|--!|xzzzzzzk#kzxx*=*x=*|==xz#%%x*====|||+!---
M!!!+!|-+!-++!-!!!!#%MzxM%xz*+=+=M%Mx+--!|xk####M##kkkk###Mzzx=|+++!+=xxzk#M#kkz
z!!!!!-!!--!-!-!--!kx*=xk*zkkxx|-!=zzMMkzx*==||==xxz#M%%%%%#kzzzkk#MMMMMMMMM##M
```

## Features

* Capture webcam image and display it directly in the terminal
* `tevi stream`: visualise the source live in **TUI** mode
* `tevi print`: print image to the terminal screen
* **Cross-Platform**: supports Linux, Windows 11 and MacOS.

### CLI flags

* Image file viewer: `--file <file>`
  * supports JPEG and PNG images
* **ASCII** mode: `--ascii`
* greyscale display: `--gray`/`--grey`
* Fixed width and/or height `--width <cols>`, `--height <rows>`
  * aspect ratio maintained automatically

## Usage

Stream webcam input to the terminal

```bash
tevi stream
```

Stream as **ASCII** text with 80 character width

```bash
tevi stream --ascii --grey --width 80
```

Print a single webcam capture:

```bash
tevi print
```

Render photo `image.jpg` as colored **ASCII** text to screen:

```bash
tevi print --file image.jpg --ascii
```

## Building from source

Prerequisites:

* **vcpkg** installed with `VCPKG_ROOT` added to the `PATH` environment
variable
* **clang**, **ninja**, **cmake** installed

```bash
cmake --preset linux-release
cmake --build build
./build/tevi
```

## License

This project is licensed under the GNU General Public License v3.0
