// Importa 'Express', framework para criação de servidores web em Node.js.
const express = require("express");
// Importa 'fs' (File System), módulo nativo do Node.js para interagir com o sistema de arquivos.
const fs = require("fs");
// Importa 'path', para lidar com caminhos de arquivos
const path = require("path");

// Cria uma instância do aplicativo Express.
const app = express();
// Define a porta em que o servidor irá rodar.
const PORT = 3000;
// Cria o caminho completo para o arquivo de texto, que funcionará como um "banco de dados" simples.
const FILE_PATH = path.join(__dirname, "contador.txt");

// Verifica se o arquivo do contador NÃO existe.
if (!fs.existsSync(FILE_PATH)) {
  // Se não existir, cria o arquivo e o inicializa com o valor "0".
  fs.writeFileSync(FILE_PATH, "0");
}

// Rota para o ESP32 incrementar o contador. Acessada via método POST
app.post("/incrementar", (req, res) => {
  console.log("Recebido um POST do ESP32 para /incrementar");
  // Lê o valor atual do arquivo
  let valor = fs.readFileSync(FILE_PATH, "utf8");
  // Converte o valor de texto para número inteiro.
  let valorNumerico = parseInt(valor);
  // Incrementa (soma 1) ao valor.
  valorNumerico++;
  // Converte o novo valor de volta para texto e o salva no arquivo.
  fs.writeFileSync(FILE_PATH, valorNumerico.toString());
  // Envia uma resposta "OK" para o ESP32.
  res.status(200).send("Contador incrementado com sucesso!");
});

// Rota para a página web (index.html) buscar o valor atual do contador. Acessada via GET.
app.get("/contador", (req, res) => {
  console.log("Recebido um GET da página web para /contador");
  // Lê o valor atual do arquivo.
  const valor = fs.readFileSync(FILE_PATH, "utf8");
  // Envia o valor como resposta para a página web.
  res.send(valor);
});

// Configura o Express para servir os arquivos da pasta atual (onde o server.js está).
app.use(express.static(__dirname));

// "Liga" o servidor, fazendo com que ele comece a "escutar" por requisições na porta definida.
app.listen(PORT, () => {
  console.log(`Servidor rodando em http://localhost:${PORT}`);
  console.log(`Página de visualização disponível em http://localhost:${PORT}/index.html`);
});