# TaskSystem

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/std/the-standard)
[![CMake](https://img.shields.io/badge/CMake-3.12+-green.svg)](https://cmake.org/)

A lightweight, efficient task management system built with modern C++ featuring persistent storage, multi-threading support, and flexible command architecture.

## 🚀 Features

- **Persistent Task Storage**: Uses nlohmann/json for reliable task data persistence
- **Terminal-Based Interface**: Interactive command-line interface for task management
- **CRTP-Based Architecture**: Modern C++ design with Curiously Recurring Template Pattern
- **Multi-threaded Logging**: Concurrent logging system with multi-consumer support
- **Flexible Command System**: Extensible command architecture using type erasure
- **Cross-platform Support**: Compatible with Windows, Linux, and macOS

## 📋 Table of Contents

- [Installation](##installation)
- [Usage](##usage)
- [Commands](##commands)
- [Building from Source](##building-from-source)
- [Project Structure](##project-structure)
- [Contributing](##contributing)
- [License](##license)

## 🛠️ Installation

### Prerequisites

- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.12 or higher
- nlohmann/json library

### Quick Start

1. **Clone the repository**

   ```bash
   git clone https://github.com/which-W/TaskSystem.git
   cd TaskSystem
   ```

2. **Install dependencies**

   Make sure nlohmann/json is available in your system. You can install it via:

   **Ubuntu/Debian:**

   ```bash
   sudo apt-get install nlohmann-json3-dev
   ```

   **macOS (via Homebrew):**

   ```bash
   brew install nlohmann-json
   ```

   **Windows (via vcpkg):**

   ```bash
   vcpkg install nlohmann-json
   ```

3. **Build the project**

   ```bash
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```

4. **Run the application**

   ```bash
   ./TaskSystem        # Linux/macOS
   TaskSystem.exe      # Windows
   ```

## 📖 Usage

After launching TaskSystem, you'll see an interactive prompt where you can enter commands to manage your tasks.

```
欢迎使用任务管理系统！
可用命令: add, delete, list, update, exit, upgrate_index

> add Buy groceries,1,2025-05-24
Task added successfully!

> list
[1] Buy groceries (Priority: 1, Due: 2025-05-24)

> exit
退出任务管理系统。
```

## 🔧 Commands

### `add` - Add New Task

**Syntax:** `add <task_name>,<priority>,<due_date>`

**Example:**

```bash
> add Complete project documentation,2,2025-05-30
> add Buy milk,1,2025-05-24
```

### `delete` - Delete Task

**Syntax:** `delete <task_id>`

**Example:**

```bash
> delete 1
```

### `list` - List All Tasks

**Syntax:** `list`

**Example:**

```bash
> list
ID: 1, Description: task2, Priority: 2, Due Date: 2025-1-1
```

### `update` - Update Task

**Syntax:** `update <task_id>,<new_task_name>,<new_priority>,<new_due_date>`

**Example:**

```bash
> update 1,Complete final documentation,3,2025-06-01
```

### `upgrate_index` - Update Task Index

**Syntax:** `upgrate_index`

**Example:**

```bash
> upgrate_index 
```

### `exit` - Exit Application

**Syntax:** `exit`

Safely closes the application and saves all changes.

## 🏗️ Building from Source

### Using CMake (Recommended)

```bash
# Create build directory
mkdir build && cd build

# Configure the project
cmake ..

# Build the project
cmake --build .

# Optional: Install the project
cmake --install .
```

### Using CMake Presets (Windows)

For Windows users, the project includes CMake presets:

```bash
# Configure for x64 Debug
cmake --preset x64-debug

# Build
cmake --build out/build/x64-debug
```

Available presets:

- `x64-debug` - 64-bit Debug build
- `x64-release` - 64-bit Release build
- `x86-debug` - 32-bit Debug build
- `x86-release` - 32-bit Release build

## 📁 Project Structure

```
TaskSystem/
├── CMakeLists.txt          # Main CMake configuration
├── CMakePresets.json       # CMake presets for different platforms
├── LICENSE                 # Apache 2.0 License
├── README.md              # This file
├── .gitignore             # Git ignore rules
├── includes/              # External dependencies headers
│   └── nlohmann/          # JSON library headers
└── TaskSystem/            # Source code directory
    ├── CMakeLists.txt     # Source CMake configuration
    ├── TaskSystem.cpp     # Main application entry point
    ├── TaskSystem.h       # Main header file
    ├── TaskManager.h      # Task management logic
    ├── Command.h          # Command pattern implementation
    ├── CommandWrapper.h   # Type erasure wrapper for commands
    ├── Logger.h           # Logging system
    ├── LogQueue.h         # Thread-safe log queue
    └── global.h           # Global includes and definitions
```

## 🏛️ Architecture

### Design Patterns Used

- **CRTP (Curiously Recurring Template Pattern)**: For compile-time polymorphism in command handling
- **Command Pattern**: Encapsulates task operations as objects
- **Type Erasure**: `CommandWrapper` allows storing different command types in containers
- **Producer-Consumer**: Multi-threaded logging system with queue-based architecture

### Key Components

- **TaskManager**: Core task management functionality
- **Command System**: Flexible command processing with CRTP
- **Logger**: Thread-safe logging with multiple consumers
- **JSON Persistence**: Reliable task data storage

## 🤝 Contributing

We welcome contributions! Please follow these guidelines:

1. **Fork the repository**

2. **Create a feature branch**

   ```bash
   git checkout -b TaskSystem/test
   ```

3. **Make your changes**

4. **Add tests** (if applicable)

5. **Commit your changes**

   ```bash
   git commit -m "how do you to modify"
   ```

6. **Push to the branch**

   ```bash
   git push origin TaskSystem/test
   ```

7. **Open a Pull Request**

### Code Style

- Follow C++17 standards
- Use consistent indentation (4 spaces)
- Include appropriate comments for complex logic
- Ensure thread-safety where applicable

## 📝 License

This project is licensed under the Apache License 2.0 - see the [LICENSE](LICENSE) file for details.

## 🐛 Bug Reports & Feature Requests

Please use the [GitHub Issues](https://github.com/yourusername/TaskSystem/issues) page to report bugs or request features.

## 📧 Contact

- **Author**: WGT
- **Email**: [wengzu728.love@gmail.com]
- **Project Link**: [https://github.com/Which-W/TaskSystem](https://github.com/Which-W/TaskSystem)

## 🙏 Acknowledgments

- [nlohmann/json](https://github.com/nlohmann/json) - JSON library for modern C++
- CMake community for build system support
- C++ community for design pattern guidance

---

⭐ **Star this repository if you find it helpful!**
