# TaskSystem

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/std/the-standard)
[![CMake](https://img.shields.io/badge/CMake-3.12+-green.svg)](https://cmake.org/)

A lightweight, efficient task management system built with modern C++ featuring persistent storage, multi-threading support, flexible command architecture, and comprehensive task ownership management.

## 🚀 Features

- **Persistent Task Storage**: Uses nlohmann/json for reliable task data persistence
- **Terminal-Based Interface**: Interactive command-line interface with built-in help system
- **Task Ownership Management**: Assign and manage task owners with dedicated interfaces
- **CRTP-Based Architecture**: Modern C++ design with Curiously Recurring Template Pattern
- **Multi-threaded Logging**: Concurrent logging system with multi-consumer support
- **Flexible Command System**: Extensible command architecture using type erasure
- **Modular Command Registration**: Clean separation of command registration and execution logic
- **Interactive Help System**: Context-aware help for all available commands
- **Cross-platform Support**: Compatible with Windows, Linux, and macOS

## 📋 Table of Contents

- [Installation](#%EF%B8%8F-installation)
- [Usage](#-usage)
- [Commands](#-commands)
- [Building from Source](#%EF%B8%8F-building-from-source)
- [Project Structure](#-project-structure)
- [Contributing](#-contributing)
- [License](#-license)

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

After launching TaskSystem, you'll see an interactive prompt where you can enter commands to manage your tasks. Use the `help` command to display all available commands and their usage.

```
欢迎使用任务管理系统！
可用命令: add, delete, list, update, exit, upgrate_index, help, list_owner, get_owner, set_owner 

> help
"add <描述>,<所有者>,<优先级>,<截止日期> - 添加任务" 
"delete <ID> - 删除指定ID的任务" 
"list [sortOption] - 列出所有任务，sortOption可选：0-按ID, 1-按优先级, 2-按截止日期" 
"update <ID>,<描述>,<所有者>,<优先级>,<截止日期> - 更新指定ID的任务" 
"upgrate_index - 更新索引"
"list_owner <所有者> - 根据所有者筛选任务"
.....

> add Buy groceries,1,2025-05-24
添加任务成功！

> help add
"add <描述>,<所有者>,<优先级>,<截止日期> - 添加任务" 

> list
ID: 1, 描述: task, 所有者: wgt, 优先级: 2, 截止日期: 2025-1-1

> exit
退出任务管理系统。
```

## 🔧 Commands

### `add` - Add New Task

**Syntax:** `add <task_name>,<owner_name>,<priority>,<due_date>`

**Description:** Creates a new task with specified details. Priority should be a numeric value, and due date should be in YYYY-MM-DD format.

**Example:**

```bash
> add Complete project documentation,wgt,2,2025-05-30
> add Buy milk,zu,1,2025-05-24
```

### `delete` - Delete Task

**Syntax:** `delete <task_id>`

**Description:** Permanently removes a task from the system using its unique identifier.

**Example:**

```bash
> delete 1
```

### `list` - List All Tasks

**Syntax:** `list`

**Description:** Displays all tasks with their complete information including ID, description, priority, due date, and owner (if assigned).

**Example:**

```bash
> list
ID: 1, 描述: task, 所有者: wgt, 优先级: 2, 截止日期: 2025-1-1
```

### `update` - Update Task

**Syntax:** `update <task_id>,<new_task_name>,<new_owner_name>,<new_priority>,<new_due_date>`

**Description:** Modifies an existing task's details. All parameters are required, even if only changing one field.

**Example:**

```bash
> update 1,Complete final documentation,wgt2,3,2025-06-01
```

### `set_owner` - Assign Task Owner

**Syntax:** `set_owner <task_id>,<owner_name>`

**Description:** Assigns an owner to a specific task. The owner name can contain spaces and special characters.

**Example:**

```bash
> set_owner 1,Alice Smith
> set_owner 2,Bob Johnson
```

### `get_owner` - Get Task Owner

**Syntax:** `get_owner <task_id>`

**Description:** Retrieves and displays the current owner of a specified task. Shows "Not assigned" if no owner is set.

**Example:**

```bash
> get_owner 1
Owner of task 1: Alice Smith
```

### `upgrate_index` - Update Task Index

**Syntax:** `upgrate_index`

**Description:** Reorganizes and updates the internal task indexing system to maintain data consistency and optimize performance.

**Example:**

```bash
> upgrate_index 
目录已更新
```

### `help` - Display Help Information

**Syntax:** `help`

**Description:** Shows comprehensive usage information for all available commands, including syntax and brief descriptions.

**Example:**

```bash
> help
"add <描述>,<所有者>,<优先级>,<截止日期> - 添加任务" 
"delete <ID> - 删除指定ID的任务" 
"list [sortOption] - 列出所有任务，sortOption可选：0-按ID, 1-按优先级, 2-按截止日期" 
"update <ID>,<描述>,<所有者>,<优先级>,<截止日期> - 更新指定ID的任务" 
"upgrate_index - 更新索引"
"list_owner <所有者> - 根据所有者筛选任务"
....
>help add
"add <描述>,<所有者>,<优先级>,<截止日期> - 添加任务" 
```

### `exit` - Exit Application

**Syntax:** `exit`

**Description:** Safely closes the application, ensuring all data is properly saved to persistent storage before termination.

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
    ├── Register_Command.h # Command registration system
    ├── Run_command.h      # Command execution engine
    ├── Logger.h           # Logging system
    ├── LogQueue.h         # Thread-safe log queue
    └── global.h           # Global includes and definitions
```

## 🏛️ Architecture

### Design Patterns Used

- **CRTP (Curiously Recurring Template Pattern)**: For compile-time polymorphism in command handling
- **Command Pattern**: Encapsulates task operations as objects with extensible command registration
- **Type Erasure**: `CommandWrapper` allows storing different command types in containers
- **Registry Pattern**: `Register_Command` provides centralized command registration and management
- **Producer-Consumer**: Multi-threaded logging system with queue-based architecture
- **Separation of Concerns**: Clear separation between command registration, execution, and task management

### Key Components

- **TaskManager**: Core task management functionality with owner assignment capabilities
- **Command System**: Flexible command processing with CRTP and modular registration
- **CommandWrapper**: Type-erased command container for heterogeneous command storage
- **Register_Command**: Centralized command registration and initialization system
- **Run_command**: Interactive command execution loop with user input handling
- **Logger**: Thread-safe logging with multiple consumers
- **JSON Persistence**: Reliable task data storage with owner information

### Command Architecture

The system uses a sophisticated command architecture that supports:

- **Dynamic Command Registration**: Commands are registered at startup through the registration system
- **Type Safety**: Template-based command implementation ensures compile-time type checking
- **Extensibility**: New commands can be easily added without modifying existing code
- **Encapsulation**: Each command encapsulates its own logic and validation
- **Help Integration**: Automatic help generation for registered commands

## 🤝 Contributing

We welcome contributions! Please follow these guidelines:

1. **Fork the repository**

2. **Create a feature branch**

   ```bash
   git checkout -b TaskSystem/your_feature_name
   ```

3. **Make your changes**

   - Follow the existing code style and architecture patterns
   - Add appropriate comments for complex logic
   - Update documentation if adding new features
   - Ensure thread-safety where applicable

4. **Add tests** (if applicable)

5. **Commit your changes**

   ```bash
   git commit -m "Add: brief description of your changes"
   ```

6. **Push to the branch**

   ```bash
   git push origin TaskSystem/your-feature-name
   ```

7. **Open a Pull Request**

### Code Style Guidelines

- Follow C++17 standards and best practices
- Use consistent indentation (4 spaces, no tabs)
- Include appropriate comments for complex logic
- Maintain const-correctness where possible
- Use RAII principles for resource management
- Follow the existing naming conventions
- Ensure proper error handling and validation

### Adding New Commands

To add a new command to the system:

1. Implement the command class following the CRTP pattern in `Command.h`
2. Register the command in `Register_Command.h`
3. Update the help system with command documentation
4. Add appropriate error handling and validation
5. Update this README with the new command documentation

## 📝 License

This project is licensed under the Apache License 2.0 - see the [LICENSE](LICENSE) file for details.

## 🐛 Bug Reports & Feature Requests

Please use the [GitHub Issues](https://github.com/Which-W/TaskSystem/issues) page to report bugs or request features. When reporting issues, please include:

- Operating system and version
- Compiler version
- Steps to reproduce the issue
- Expected vs. actual behavior
- Relevant log output or error messages

## 📧 Contact

- **Author**: WGT
- **Email**: [wengzu728.love@gmail.com]
- **Project Link**: [https://github.com/Which-W/TaskSystem](https://github.com/Which-W/TaskSystem)

## 🙏 Acknowledgments

- [nlohmann/json](https://github.com/nlohmann/json) - JSON library for modern C++
- CMake community for build system support
- C++ community for design pattern guidance
- Contributors and users who provide feedback and improvements

---

⭐ **Star this repository if you find it helpful!**
