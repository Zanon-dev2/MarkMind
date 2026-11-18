# MarkMind

> An automated, AI-powered documentation generator written in C++ that scans your project repository, bundles your source code, and queries the Google Gemini API to generate a professional `README.md` file.

---

## 📋 Description

**MarkMind** is a developer tool designed to eliminate the friction of writing project documentation. By recursively walking through your codebase, it intelligently collects relevant source files and configuration scripts (while ignoring build artifacts and version control directories) and sends them to the **Gemini API**. The AI analyzes your codebase architecture and outputs a clean, comprehensive, and professional `README.md` directly into your project root.

---

## 🗂️ Folder Structure

```text
MarkMind/
│
├── markmind.cpp      # Main C++ source file containing file-walker, cURL logic, and CLI parser
├── Makefile          # Build configuration for compilation via Make
└── README.md         # Project documentation (auto-generated or manual)
```

---

## ⚙️ Dependencies

To successfully compile and run **MarkMind**, ensure you have the following installed on your system:

1. **C++17 Compiler** (e.g., `g++` via MinGW on Windows or GCC on Linux)
2. **libcurl** (Client URL library for HTTP requests)
3. **nlohmann/json** (Modern JSON parser for C++)
4. **workez.hpp** (Custom/utility header referenced in the source)
5. **Windows Sockets API (`-lws2_32`)** (Required if compiling on Windows for network operations)

---

## 🛠️ How to Compile

MarkMind comes with a `Makefile` configured for `g++`. Open your terminal in the project directory and run:

```bash
make build
```

This will compile `markmind.cpp` with C++17 standards, link `libcurl` and `ws2_32`, and output an executable named `Mark.exe`.

---

## 🚀 How to Use

Before running the application, you must set your Gemini API key as an environment variable.

### 1. Set the Environment Variable

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

Execute the program using the `api local` command to scan the current directory and generate the README:

```bash
./Mark.exe api local
```

Once executed successfully, a newly generated `README.md` file will appear in your project root directory.