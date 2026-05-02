# OpenGL Triangle

A minimal colored triangle rendered with FreeGLUT and legacy OpenGL, demonstrating a
Windows C++17 project with CMake, vcpkg, GoogleTest, and GitHub Actions CI/CD.

[![CI](https://github.com/shoggy/cpp-opengl-demo/actions/workflows/ci.yml/badge.svg)](https://github.com/shoggy/cpp-opengl-demo/actions/workflows/ci.yml)

## Features

- Red/green/blue vertex triangle in a resizable 640×480 window
- Aspect-ratio-preserving reshape
- Press **ESC** to quit
- Unit-tested math helpers (headless, no OpenGL context required)

---

## Prerequisites

- **Windows 10/11**
- **Visual Studio 2022** (Community or higher) with the *Desktop development with C++* workload,
  **or** [winlibs MinGW-w64](https://winlibs.com/) (GCC 13+ recommended)
- **CMake 3.21+** — [cmake.org/download](https://cmake.org/download/) or
  `winget install Kitware.CMake`
- **Ninja** — `winget install Ninja-build.Ninja` or `choco install ninja`
- **Git** — [git-scm.com](https://git-scm.com/)

---

## Windows Setup

### 1. Clone and bootstrap vcpkg

```cmd
git clone https://github.com/microsoft/vcpkg.git C:\vcpkg
C:\vcpkg\bootstrap-vcpkg.bat -disableMetrics
```

### 2. Set VCPKG_ROOT permanently

Open **System Properties → Environment Variables** and add a new **User variable**:

| Variable    | Value      |
|-------------|------------|
| `VCPKG_ROOT` | `C:\vcpkg` |

Then open a **new** terminal so the variable is visible.

### 3. Update the vcpkg baseline

After cloning vcpkg, record its HEAD commit hash in `vcpkg.json`:

```cmd
git -C %VCPKG_ROOT% rev-parse HEAD
```

Copy the printed hash into the `"builtin-baseline"` field in `vcpkg.json`.

---

## Building

All commands run from the repository root in a **Developer Command Prompt** (MSVC) or a
MinGW terminal with GCC on `PATH`.

### Configure + Build (Debug)

```cmd
cmake --preset debug
cmake --build --preset debug
```

Output: `build\debug\src\opengl_app.exe` and `build\debug\tests\run_tests.exe`

### Configure + Build (Release)

```cmd
cmake --preset release
cmake --build --preset release
```

### Run tests

```cmd
ctest --preset debug --output-on-failure
```

### Run the application

```cmd
build\debug\src\opengl_app.exe
```

---

## Project Structure

```
.
├── .github/
│   └── workflows/
│       └── ci.yml          # GitHub Actions: lint → build/test → publish
├── src/
│   ├── CMakeLists.txt
│   └── main.cpp            # FreeGLUT + OpenGL immediate-mode triangle
├── tests/
│   ├── CMakeLists.txt
│   └── test_math.cpp       # Headless GoogleTest unit tests
├── CMakeLists.txt          # Root: find_package, enable_testing
├── CMakePresets.json       # debug / release presets (reads VCPKG_ROOT)
├── vcpkg.json              # Manifest: freeglut + gtest
├── .clang-format           # Google style, 4-space indent, 100-col limit
├── .gitignore
└── README.md
```

---

## Why tests don't use OpenGL

OpenGL requires a GPU context, which requires a running display server. GitHub Actions
Windows runners are headless. Rather than add a virtual display, the unit tests cover
pure C++ logic — `clamp`, `lerp`, `pointInTriangle` — which gives meaningful coverage
of the geometry math without any context setup. This is also correct architecture:
rendering state should not leak into unit-testable logic.

---

## CI Pipeline

| Job      | Trigger           | What it does                                            |
|----------|-------------------|---------------------------------------------------------|
| `lint`   | every push / PR   | `clang-format --dry-run` + `cppcheck` static analysis  |
| `build`  | after lint passes | CMake configure → build → `ctest` on `windows-latest`  |
| `publish`| tag `v*.*.*`      | Release build, bundle `freeglut.dll`, upload zip to GH Releases |

### Publishing a release

```cmd
git tag v1.0.0
git push origin v1.0.0
```

The `publish` job automatically creates a GitHub Release with generated release notes
and attaches `opengl-triangle-v1.0.0-windows.zip`.

---

## Updating vcpkg dependencies

```cmd
cd %VCPKG_ROOT%
git pull
bootstrap-vcpkg.bat -disableMetrics
```

Then update `"builtin-baseline"` in `vcpkg.json` with the new HEAD hash.

---

## License

MIT
