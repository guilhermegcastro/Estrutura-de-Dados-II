# 📚 Estrutura de Dados II

![C Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![OS](https://img.shields.io/badge/OS-Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![Status](https://img.shields.io/badge/Status-Completed-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)

> "C is quirky, flawed, and an enormous success." - Dennis Ritchie

---

## 🚀 Sobre o Projeto

Boas-vindas ao meu repositório de **Estrutura de Dados II**.

Este repositório serve como o meu portfólio acadêmico e "segundo cérebro", documentando a minha evolução na disciplina. Aqui você encontrará desde recursividade até a implementação de estruturas encadeadas e genéricas, com headers organizados separadamente das implementações, baseado nos exercícios propostos pelo professor Adriano Prates.

<p align="center">
  <img src="https://github.com/guilhermegcastro/Estrutura-de-Dados-II/raw/main/images/when-the-coding-when-the.gif" width="400px" />
</p>

---

## 📂 Organização dos Diretórios

A estrutura separa **interfaces** (`include/`) de **implementações** (`src/`):

### `include/` — Headers

| Diretório / Arquivo | Descrição |
| :--- | :--- |
| **`Queue and Stack`** | Definições de fila e pilha (interfaces `.h`). |
| **`Generic List`** | Definições de lista genérica (interfaces `.h`). |

### `src/` — Implementações

| Diretório / Arquivo | Descrição |
| :--- | :--- |
| **`#01 - Recursividade`** | Algoritmos recursivos e resolução de problemas por recursão. |
| **`#02 - Lista Encadeada`** | Implementação de listas ligadas (inserção, remoção, busca). |
| **`#03 - Lista Genérica`** | Estruturas genéricas via `void*`, aplicáveis a múltiplos tipos de dado. |

---

## 🧠 Destaques de Aprendizagem

Alguns dos conceitos-chave explorados e consolidados neste repositório:

- [x] **Recursividade:** Resolução de problemas por decomposição recursiva.
- [x] **Listas Encadeadas:** Manipulação de nós, ponteiros e alocação dinâmica.
- [x] **Estruturas Genéricas:** Uso de `void*` para estruturas reutilizáveis entre tipos.
- [x] **Filas e Pilhas:** Implementação de TADs (Tipos Abstratos de Dados) com interface separada da implementação.

---

## 🛠 Tecnologias e Ferramentas

* **Linguagem:** C (Padrão C99/C11) ©️
* **Compilador:** GCC (GNU Compiler Collection) 🐂
* **Editor/IDE:** Geany / VS Code 🫖
* **Sistema Operativo:** Linux (Manjaro) 🐧

---

## 💻 Como Compilar e Executar

Para rodar qualquer código deste repositório, siga os passos no terminal:

1. **Clone o repositório:**
   ```bash
   git clone https://github.com/guilhermegcastro/Estrutura-de-Dados-II.git
   ```
2. Navegue até a pasta desejada (exemplo):
   ```bash
   cd Estrutura-de-Dados-II/src/"#02 - Lista Encadeada"
   ```
3. Compile o arquivo, incluindo os diretórios de headers:
   ```bash
   gcc -Iinclude/"Queue and Stack" -Iinclude/"Generic List" nome_do_arquivo.c -o programa
   ```
4. Execute:
   ```bash
   ./programa
   ```
