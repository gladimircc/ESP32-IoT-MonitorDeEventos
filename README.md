# ESP32-IoT-MonitorDeEventos
Projeto didático de IoT - Internet das Coisas que utiliza um ESP32 para capturar cliques de um botão, envia os dados para um servidor Node.js (Express) e exibe a contagem em uma página web que se atualiza em tempo real.

## 🎯 Objetivo do Projeto
[cite_start]Este projeto demonstra um sistema de Internet das Coisas (IoT) completo e simples para monitorar um evento físico (o clique de um botão) e exibir a contagem total em tempo real através de uma página web. 

[cite_start]A arquitetura utilizada (Dispositivo → Servidor → Interface) serve como um modelo fundamental para inúmeros outros projetos de IoT. 

---

## 🛠️ Componentes Utilizados

### Hardware
* [cite_start]🧠 **ESP32-C3:** Microcontrolador responsável por ler o estado do botão, conecta-se ao Wi-Fi e se comunica com nosso servidor. 
* [cite_start]👆 **Botão (Push-button):** Atua como o gatilho para o evento físico que será contado. 
* [cite_start]💡 **LED:** Fornece um feedback visual ao usuário, confirmando que o clique foi registrado e enviado. 

### Software
* ⚙️ **Backend (Servidor):** Um servidor simples criado com **Node.js** e a biblioteca **Express**. [cite_start]Suas responsabilidades são receber os sinais do ESP32, guardar a contagem em um arquivo (`contador.txt`) e fornecer os dados para a interface web. 
* [cite_start]🖥️ **Frontend (Página Web):** Uma página **HTML** com **JavaScript** que busca os dados do servidor periodicamente e atualiza a contagem na tela do usuário em tempo real, sem a necessidade de recarregar a página. 

---

## 🚀 Como Executar o Projeto

### Pré-requisitos
* Node.js instalado na máquina que rodará o servidor.
* IDE do Arduino ou PlatformIO para gravar o código no ESP32.
* Um microcontrolador ESP32, um botão, um LED e uma protoboard.

### 1. Configuração do Backend (Servidor)
1.  Clone este repositório para a sua máquina.
2.  Navegue até a pasta do projeto pelo terminal.
3.  Instale as dependências necessárias (a biblioteca Express):
    ```bash
    npm install express
    ```
4.  Execute o servidor:
    ```bash
    node server.js
    ```
    O servidor estará rodando na porta 3000. Anote o endereço de IP local da sua máquina.

### 2. Configuração do Hardware (ESP32)
1.  Monte o circuito conectando o botão e o LED ao ESP32 conforme definido nos pinos do arquivo `.ino`.
2.  Abra o arquivo `.ino` (ex: `Gatilho_IoT.ino`) na sua IDE.
3.  Altere as seguintes linhas com as suas informações:
    ```cpp
    const char* ssid = "NOME_DA_SUA_REDE_WIFI";
    const char* password = "SENHA_DA_SUA_REDE_WIFI";
    const char* urlContador = "http://SEU_IP_LOCAL:3000/incrementar"; 
    ```
4.  Grave o código no seu ESP32. Abra o Monitor Serial para acompanhar o status da conexão e dos cliques.

### 3. Visualização
1.  Com o servidor rodando e o ESP32 conectado ao Wi-Fi, abra um navegador de internet.
2.  Acesse `http://SEU_IP_LOCAL:3000`.
3.  A página web exibirá a contagem. Cada vez que o botão for pressionado, o número na página será atualizado automaticamente.

---

## 💡 Possíveis Melhorias e Expansões
Este projeto é um ponto de partida. Algumas ideias para expandi-lo:
* [cite_start]**Trocar o Gatilho:** Use sensores de presença (PIR), magnéticos ou de umidade para contar outros tipos de eventos. 
* [cite_start]**Melhorar a Persistência:** Substitua o arquivo `contador.txt` por um banco de dados real como o Firebase ou MySQL para gerar gráficos e históricos. 
* [cite_start]**Adicionar Notificações:** Faça o servidor enviar um e-mail, uma mensagem no Telegram ou uma notificação push quando um evento ocorrer.
