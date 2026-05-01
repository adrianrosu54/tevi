# TeVi

TeVi is a CLI application for displaying webcam image input directly in the
terminal. It enables the user to print images to the screen using **ANSI escape
sequences**.

## Usage

Print capture from webcam input:

```bash
tevi print
```

Print photo `image.jpg` as greyscale **ASCII** text to screen:

```bash
tevi print --file image.jpg --ascii --grey
```

## Building from source

Prerequisites:

* **vcpkg** installed with `VCPKG_ROOT` added to the `PATH` environment
variable
* **clang**, **ninja**, **cmake** installed

```bash
cmake --preset release
cmake --build build
./build/tevi
```

## License

This project is licensed under the GNU General Public License v3.0
