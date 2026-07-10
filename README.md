# World Cup Manager

Sistema de gerenciamento de times e jogadores de futebol em C, com simulação de partidas e disputa de Copa do Mundo. Desenvolvido para rodar no terminal do Windows.

## Como compilar e rodar

> ⚠️ Este projeto foi desenvolvido para **Windows** (usa comandos como `cls` e `chcp`).

No terminal (Prompt de Comando, PowerShell ou Git Bash), dentro da pasta do projeto:

```bash
gcc main.c -o world-cup-manager
```

Depois, execute:

```bash
./world-cup-manager
```

## Funcionalidades

### Sistema de usuários
- Cadastro e login de usuários
- Sessão salva (não precisa logar toda vez)
- Perfil de **Administrador** e perfil de **Treinador (Coach)**

### Administrador
- Criar, listar, editar e excluir times
- Criar, editar e excluir jogadores
- Salvar alterações no sistema

### Treinador (Coach)
- Escolher um time para gerenciar
- Montar elenco: convocar e dispensar jogadores (limite de 15 por time)
- Definir titulares
- Ver estatísticas do time
- Simular partidas
- Disputar a Copa do Mundo (fase de grupos + mata-mata)
- Acompanhar artilharia e assistências dos jogadores

### Partidas
- Simulação de resultados com base na força dos times (`overallStrength`)
- Sorteio de artilheiros e assistências
- Tabelas de classificação por grupo

## Estrutura do projeto

| Arquivo | Descrição |
|---|---|
| `main.c` | Menu principal e loop do jogo |
| `manager.c` / `manager.h` | Gerenciamento de usuários, times e jogadores |
| `matches.c` / `matches.h` | Simulação de partidas e Copa do Mundo |
| `inicializate.c` | Inicialização de dados padrão do sistema |

## Autor

Nicolas Venceslau
