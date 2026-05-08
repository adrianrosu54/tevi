# TeVi

***TeVi*** (Text-View) is a CLI application for displaying webcam image input
directly in the terminal. It enables the user to print images to the screen
using **ANSI escape sequences**.

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
