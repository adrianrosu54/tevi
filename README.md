# Text Sight

A Terminal User Interface (TUI) application for displaying 
webcam image input directly in the terminal.

## Download 

See GitHub releases for prebuilt binaries.

### Building from source

Requirements:

- `vcpkg` for dependency management
- `Clang`, `Ninja`, `CMake`
- `libopencv4` on Linux
- `vc_redist.x64` installer on Windows

```bash
# install and build dependencies
vcpkg install
cmake --build --preset windows-release

# package for release
cmake --install build --prefix install
cpack --config build/CPackConfig.cmake
```

## License

This project is licensed under the GNU General Public License v3.0