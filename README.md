# 💈 Problema do Barbeiro Dorminhoco

## 📝 Descrição do Problema

O problema do **Barbeiro Dorminhoco** descreve uma barbearia com:

- 👨‍🔧 Um barbeiro  
- 💺 Uma cadeira de barbeiro  
- 🪑 `N` cadeiras de espera para clientes  

### Regras:

- 😴 Se **não há clientes**, o barbeiro dorme.
- 🚶‍♂️ Quando um cliente chega:
  - 🛎️ Se o barbeiro estiver **dormindo**, ele o acorda.
  - ⏳ Se o barbeiro estiver **ocupado** e houver **cadeiras disponíveis**, o cliente **senta e espera**.
  - ❌ Se **todas as cadeiras estiverem ocupadas**, o cliente **vai embora**.

---

## 🔐 Seção Crítica e Pontos de Sincronização

### 🔸 Seção Crítica:
- Acessar e modificar o número de clientes esperando e as cadeiras disponíveis.

### 🔸 Sincronização Necessária:

- 🔒 `mutex`: protege o contador de clientes para evitar acessos simultâneos.
- 🚻 `semaforo_cliente`: conta os clientes que aguardam atendimento.
- ✂️ `semaforo_barbeiro`: sinaliza quando o barbeiro está pronto para cortar cabelo.

---

## ⚙️ Tratamento com Semáforos

| 🔧 Recurso        | 🧩 Função                                                                 |
|------------------|--------------------------------------------------------------------------|
| `cliente` 👥      | Semáforo que contabiliza os clientes aguardando atendimento.            |
| `barbeiro` 💇     | Semáforo que sinaliza que o barbeiro está pronto para cortar cabelo.    |
| `mutex` 🔐        | Garante exclusão mútua ao acessar a variável de controle de clientes.   |

✅ Esse modelo de sincronização garante que:

- 🛠️ O barbeiro **trabalhe apenas se houver clientes**.  
- 📋 Os **clientes aguardem de forma organizada** ou saiam caso não haja lugar.  
- 🔄 **A integridade dos dados compartilhados** seja mantida.
