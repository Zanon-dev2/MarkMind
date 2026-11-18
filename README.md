# MarkMind

> An intelligent, automated CLI tool that scans your source code and leverages the Gemini AI API to generate professional, comprehensive `README.md` documentation instantly.

---

## Description

MarkMind is a C++ command-line utility designed to streamline the documentation process for developers. By analyzing either an entire directory tree (recursively filtering out build folders and noise) or a specific source file, MarkMind packages your code structure and contents into a payload, communicates securely with the Gemini API via `libcurl`, and automatically outputs a polished, ready-to-use `README.md`.

---

## Folder Structure

```text
.
├── Makefile
└── markmind.cpp
```

---

## Dependencies

To successfully compile and run MarkMind, ensure you have the following libraries and tools installed on your system:

* **C++17 Compatible Compiler** (e.g., `g++` via MinGW or GCC)
* **libcurl** (Client URL request library)
* **nlohmann/json** (JSON for Modern C++ header-only library)
* **workez.hpp** (Custom header utilized in source context)
* **Windows Sockets (`-lws2_32`)** (Required for network operations on Windows platforms)

---

## How to Compile

A `Makefile` is provided to simplify the build process using `g++`. Open your terminal in the project root and run the following command:

```bash
make build
```

This will compile `markmind.cpp` with C++17 standards, link the necessary cURL and Windows socket libraries, and output an executable named `Mark.exe`.

---

## How to Use

MarkMind requires a valid Gemini API key set in your environment variables before execution.

### 1. Set your Environment Variable
* **Windows (Command Prompt):**
  ```cmd
  set GEMINI_API_KEY=your_actual_api_key_here
  ```
* **Windows (PowerShell):**
  ```powershell
  $env:GEMINI_API_KEY="your_actual_api_key_here"
  ```
* **Linux / macOS:**
  ```bash
  export GEMINI_API_KEY="your_actual_api_key_here"
  ```

### 2. Run the Executable

* **Generate a README for an entire local directory:**
  Scans all relevant source files in the current directory (ignoring standard build directories, `.git`, `node_modules`, etc.) and generates a `README.md`.
  ```bash
  Mark.exe api local
  ```

* **Generate a README for a specific file:**
  Target an individual file for analysis and documentation generation.
  ```bash
  Mark.exe api file path/to/your/file.cpp
  ```