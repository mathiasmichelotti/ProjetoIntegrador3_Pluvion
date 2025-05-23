==============================
README - PROJETO LORA + ESP32 ENVIANDO DADOS PARA UBIDOTS
==============================

**DESCRIÇÃO DO PROJETO:**
Este projeto utiliza um módulo ESP32 para simular dados de sensores (exemplo: temperatura) 
e enviar esses dados para a plataforma de IoT Ubidots via conexão Wi-Fi. A ideia é 
integrar a comunicação LoRa para captura local dos dados, mas inicialmente o foco está 
no envio para a nuvem para monitoramento remoto.

**FUNCIONALIDADES:**
- Conexão do ESP32 a uma rede Wi-Fi
- Simulação de dados de sensores (temperatura fictícia)
- Envio dos dados para o Ubidots usando requisições HTTP POST
- Visualização dos dados na nuvem via dashboard Ubidots

**REQUISITOS:**
- Placa ESP32
- Ambiente Arduino IDE configurado para ESP32
- Conta no Ubidots com token de acesso
- Rede Wi-Fi com acesso à internet

**ESTRUTURA DO PROJETO:**
LoRa_Ubidots_Project/
│
├── LoRa_Ubidots.ino      - Código fonte para o ESP32
├── README.txt            - Este arquivo de instruções
├── LICENSE               - Licença do projeto (ex: MIT)
├── docs/                 - Documentação e esquemas (opcional)
├── data/                 - Dados simulados ou logs (opcional)
└── lib/                  - Bibliotecas adicionais (opcional)

**COMO USAR:**
1. Instale a placa ESP32 no Arduino IDE (instruções no site oficial do ESP32).
2. Copie o código do arquivo LoRa_Ubidots.ino para o Arduino IDE.
3. Altere as variáveis ssid e password com os dados da sua rede Wi-Fi.
4. Atualize a variável 'token' com seu token do Ubidots.
5. Conecte seu ESP32 ao computador e selecione a placa e porta correta no Arduino IDE.
6. Faça upload do código para o ESP32.
7. Abra o Monitor Serial para acompanhar a conexão e o envio dos dados.
8. Acesse seu painel Ubidots para visualizar os dados recebidos.

**OBSERVAÇÕES:**
- Após o upload, o ESP32 pode ser desconectado do computador e alimentado por fonte externa.
- A comunicação LoRa será implementada em etapas futuras para integração dos sensores.
- Este projeto é ideal para iniciantes que desejam aprender IoT e comunicação com a nuvem.

**CONTATO:**
Para dúvidas ou contribuições, entre em contato com Mathias.
