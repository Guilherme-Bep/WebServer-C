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

### 3. Acesse a pasta do projeto via WSL

```bash
exemplo: cd "/mnt/c/Users/usuario/Documents/WebServer"
```
### 4. Abrir o projeto no VS Code com o WSL
```bash
code .
```
### 5. Instalar o GCC (se for a primeira vez compilando em C no WSL)
```bash
sudo apt update
sudo apt install build-essential
```
### 6. Compile e rode o código
```bash
gcc wServer.c -o wServer
./servidor
```

Aparecerá  "Servidor ouvindo na porta 8080"

### 7. Abra o navegador e acesse:
```bash
http://localhost:8080
```

### 🤝 Contribuições
Sinta-se à vontade para abrir issues, sugerir melhorias ou enviar pull requests. Qualquer feedback é bem-vindo!

