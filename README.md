# MySH - Simple Unix Shell in C

A lightweight Unix shell built in C that supports command execution, built-in commands, input/output redirection, and background process execution.

## 🚀 Features

- Execute Linux commands using `execvp()`
- Built-in commands:
  - `cd`
  - `pwd`
  - `exit`
- Input redirection using `<`
- Output redirection using `>`
- Background process execution using `&`
- Process creation using `fork()`
- Parent-child synchronization using `wait()`

---

## 🛠️ Technologies Used

- C Programming
- Linux System Calls
- Process Management
- File Descriptors
- Unix/Linux Environment

---

## 📂 Project Structure

```bash
main.c
README.md
```

---

## ⚙️ How It Works

### 1. Command Input

The shell continuously accepts commands from the user through a prompt.

```bash
mysh>
```

---

### 2. Command Parsing

Input commands are tokenized using `strtok()` into arguments.

Example:

```bash
ls -l
```

gets parsed as:

```c
args[0] = "ls";
args[1] = "-l";
```

---

### 3. Built-in Commands

#### Change Directory

```bash
cd folder_name
```

#### Go to Home Directory

```bash
cd ~
```

#### Print Current Working Directory

```bash
pwd
```

#### Exit Shell

```bash
exit
```

---

### 4. Background Process Execution

Commands ending with `&` run in the background.

Example:

```bash
sleep 10 &
```

Output:

```bash
[Background PID : 1234]
```

---

### 5. Input Redirection

```bash
sort < input.txt
```

Redirects file contents to standard input using `dup2()`.

---

### 6. Output Redirection

```bash
ls > output.txt
```

Redirects command output to a file.

---

## 🔧 Compilation

Compile the program using GCC:

```bash
gcc mysh.c -o mysh
```

---

## ▶️ Running the Shell

```bash
./mysh
```

---

## 💻 Example Usage

### Basic Commands

```bash
mysh> ls
mysh> pwd
mysh> date
```

### Directory Navigation

```bash
mysh> cd Documents
mysh> pwd
```

### Output Redirection

```bash
mysh> ls > files.txt
```

### Input Redirection

```bash
mysh> sort < data.txt
```

### Background Execution

```bash
mysh> sleep 20 &
```

---

## 🧠 System Calls Used

| System Call | Purpose |
|-------------|----------|
| `fork()` | Create child process |
| `execvp()` | Execute command |
| `wait()` | Wait for child process |
| `chdir()` | Change directory |
| `getcwd()` | Get current working directory |
| `open()` | Open files |
| `dup2()` | Redirect input/output |
| `close()` | Close file descriptor |

---

## 📚 Concepts Demonstrated

- Process Creation
- Parent-Child Processes
- Linux Shell Internals
- File Descriptor Manipulation
- Command Parsing
- Background Jobs
- I/O Redirection

---

## ⚠️ Limitations

- No piping support (`|`)
- No command history
- No tab completion
- No signal handling (`Ctrl+C`)
- Supports only simple space-separated parsing

---

## 🚀 Future Improvements

- Add pipe support
- Add command history
- Implement signal handling
- Add auto-completion
- Support multiple commands
- Add environment variable expansion

---

## 🎯 Learning Outcomes

This project helps in understanding:

- How Unix shells work internally
- Linux process management
- System programming concepts
- File descriptor operations
- Interaction between parent and child processes

---

## 👨‍💻 Author

Built as a systems programming project to learn Linux internals and shell implementation in C.

```
