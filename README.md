# MarkMind 🚀

> An intelligent, automated documentation generator that scans your codebase, analyzes your files, and leverages the Google Gemini AI to craft professional `README.md` files instantly.

---

## 📖 Description

**MarkMind** is a lightweight C++ utility designed to streamline project documentation. By recursively walking through your project directory, it collects source code and configuration files, packages them securely into a structured API payload, and queries the **Google Gemini 3.5 Flash-Lite** model. 

Within seconds, MarkMind writes a comprehensive, beautiful, and structured Markdown README directly into your project root—saving you hours of manual writing.

---

## 🗂️ Folder Structure

```text
MarkMind/
│
├── markmind.cpp      # Core C++ application logic & cURL/Gemini API integration
├── Makefile          # Build instructions for GNU Make / MinGW
└── README.md         # Project documentation (Auto-generated or manual)
```

---

## 📦 Dependencies

To compile and run MarkMind, ensure you have the following libraries and tools installed on your system:

1. **C++26 Compatible Compiler** (e.g., `g++` from GCC 14+ or Clang)
2. **libcurl** (Client URL transfer library)
3. **nlohmann/json** (JSON for Modern C++)
4. **workez.hpp** (Custom/Helper utility header used in the codebase)
5. **Windows Sockets (`-lws2_32`)** (Required if compiling on Windows)

---

## 🛠️ How to Compile

MarkMind comes with a built-in `Makefile` configured for Windows environments using `g++` and linking against `libcurl` and `ws2_32`.

To compile the project, open your terminal in the root directory and run:

```bash
make build
```

This will output an executable named `Mark.exe`.

---

## 🚀 How to Use

Before running MarkMind, you must set your Google Gemini API key as an environment variable.

### 1. Set your API Key

* **Windows (Command Prompt):**
  ```cmd
  set GEMINI_API_KEY=your_api_key_here
  ```

* **Windows (PowerShell):**
  ```powershell
  $env:GEMINI_API_KEY="your_api_key_here"
  ```

* **Linux / macOS (Bash/Zsh):**
  ```bash
  export GEMINI_API_KEY="your_api_key_here"
  ```

### 2. Run the Generator

Execute the binary using the `api local` command to scan the current directory and generate your README:

```bash
Mark.exe api local
```

Once executed successfully, a brand new `README.md` file will appear in your project folder!