# 🌐 WebServer em C

Este projeto é um exemplo de servidor web simples escrito em **linguagem C**, que responde com uma página HTML básica. O servidor foi desenvolvido para ser executado em sistemas Unix-like. No entanto, você pode rodá-lo no **Windows** com facilidade utilizando o **WSL (Windows Subsystem for Linux)** e o **Visual Studio Code**.

---

## ⚙️ Requisitos

- Windows 10 ou superior
- [WSL (Windows Subsystem for Linux)](https://learn.microsoft.com/pt-br/windows/wsl/install)
- Distribuição Linux (recomendada: Ubuntu)
- [Visual Studio Code](https://code.visualstudio.com/)
- Extensão **Remote - WSL** no VS Code
- Compilador GCC (disponível no Linux/Ubuntu via `build-essential`)

---

## 🚀 Como rodar o projeto no Windows com WSL e VS Code

### 1. Instale o WSL (caso ainda não tenha)

No terminal do Windows (PowerShell ou CMD), digite:

```bash
wsl --install
```

### 2. Instalar a extensão Remote - WSL no VS Code

Abra o Visual Studio Code

Vá até a aba de Extensões (Ctrl + Shift + X)

Busque por Remote - WSL e clique em Instalar

### Acesse a pasta do projeto via WSL

```bash
exemplo: cd "/mnt/c/Users/usuario/Documents/WebServer"
```

