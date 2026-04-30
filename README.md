# TeVi

TeVi is a Terminal User Interface (TUI) application for displaying webcam image
input directly in the terminal.

## Building from source

Prerequisites:

* **vcpkg** installed with `VCPKG_ROOT` added to the `PATH` environment
variable
* **clang**, **ninja**, **cmake** installed

```bash
cmake --preset default
cmake --build build
./build/tevi
```

## License

This project is licensed under the GNU General Public License v3.0
