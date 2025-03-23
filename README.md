SMARTCHEESE: CONTROLE DE MATURAÇÃO E QUALIDADE DE QUEIJOS ARTESANAIS COM IOT
O projeto SmartCheese visa modernizar e padronizar a produção de queijos artesanais, especialmente no que diz respeito ao controle da maturação, utilizando tecnologias de Internet das Coisas (IoT). Através da coleta e análise de dados como temperatura e umidade do ar, o sistema oferece aos produtores ferramentas para otimizar processos como a viragem e a lavagem dos queijos, garantindo maior qualidade e reduzindo perdas causadas por condições ambientais inadequadas. O processamento de dados, leitura de sensores e controle de água serão realizados pelo microcontrolador presente na placa BitDogLab, enquanto um aplicativo móvel exibe as informações e orienta o produtor em tempo real.
OBJETIVOS DO PROJETO
1. Monitoramento Ambiental: Coletar dados de temperatura e umidade em tempo real durante o processo de maturação dos queijos.  
2. Controle de Qualidade: Garantir que as condições ideais para a maturação sejam mantidas, evitando variações que possam comprometer a qualidade do produto final.  
3. Otimização de Processos: Definir o tempo ideal de viragem e lavagem dos queijos com base nas condições ambientais.  
4. Redução de Perdas: Minimizar perdas causadas por umidade ou temperatura inadequadas, reduzindo custos para os produtores.  
5. Padronização: Oferecer uma solução que permita a padronização da produção, mesmo em pequena escala, elevando a qualidade dos queijos artesanais.  
DESCRIÇÃO DO FUNCIONAMENTO
O projeto é composto por sensores, atuadores, placa de desenvolvimento e aplicativo. Os sensores captam os dados de temperatura e umidade do ambiente de maturação, de acordo com a leitura dos sensores é emitido uma notificação no aplicativo indicando que as condições estão divergentes das ideais, além disso, o microcontrolador ao identificar essa situação libera o fluxo de água para lavar os queijos e compensar a baixa umidade. Entretanto, devido a limitação dos componentes que são integrados a placa (a BitLogLab não possui sensor de umidade), não será utilizado um sensor de umidade externo e a liberação de água será representada através do display OLED exibindo mensagens descritivas de cada etapa do programa. Abaixo é apresentada uma breve descrição da função de cada componente no projeto.
1. Sensores IoT: Dispositivos instalados no ambiente de maturação que coletam dados de temperatura e umidade em tempo real.  
2. Placa BitDogLab: A placa BitDogLab é responsável pelo processamento dos dados, leitura dos sensores e controle de sistemas de água para ajuste de umidade quando necessário.  
3. Plataforma de Análise: Os dados são processados localmente pelo microcontrolador e enviados para um aplicativo móvel.  
4. Aplicativo Móvel: Uma interface simples e intuitiva exibe as informações coletadas (temperatura, umidade, status de viragem e lavagem) e indica ao produtor o que está acontecendo no processo de maturação. O aplicativo também emite alertas e recomendações, como:  
1.	Momento ideal para viragem dos queijos.  
2.	Necessidade de lavagem ou ajuste de umidade.  
3.	Ações corretivas em caso de desvios das condições ideais.  

JUSTIFICATIVA
A produção de queijos artesanais é uma atividade tradicional que enfrenta desafios relacionados à padronização e controle de qualidade, especialmente em relação ao processo de maturação. Fatores como temperatura e umidade são críticos para o sucesso do produto final, mas muitos produtores não possuem ferramentas adequadas para monitorar e controlar essas variáveis.  

ORIGINALIDADE
Em pesquisas realizadas buscando artigos da área ou temas correlatos não foram encontrados projetos semelhantes ou com o mesmo objetivo.
O PROJETO SMARTCHEESE SE JUSTIFICA POR:  
1. Melhoria da Qualidade: Ao garantir condições ideais de maturação, o sistema eleva a qualidade dos queijos, agregando valor ao produto.  
2. Redução de Custos: A prevenção de perdas devido a condições ambientais inadequadas reduz custos para os produtores.  
3. Tecnologia Acessível: Levar tecnologia de ponta a pequenos produtores, democratizando o acesso a ferramentas que antes eram restritas a grandes indústrias.  
4. Preservação da Tradição: Ajudar a preservar a tradição dos queijos artesanais, garantindo que ela se mantenha viável e competitiva em um mercado cada vez mais exigente.  
5. Sustentabilidade: Reduzir o desperdício de recursos e insumos, contribuindo para uma produção mais sustentável.  
6. Automação e Simplicidade: Utilizar a placa BitDogLab para processamento local e controle de sistemas de água, aliado a um aplicativo móvel de fácil uso, torna a solução acessível mesmo para produtores com pouca familiaridade com tecnologia.  
REFERÊNCIAS
SAVAGE, Steven. Vacas conectadas: IA e IoT para produzir mais e melhor leite. Forbes Brasil, 28 jun. 2022. Disponível em: https://forbes.com.br/forbesagro/2022/06/vacas-conectadas-ia-e-iot-para-produzir-mais-e-melhor-leite/. Acesso em: 9 fev. 2025.
TETRA PAK. Como o foco em digitalização e sustentabilidade podem contribuir para o crescimento da Indústria queijeira. 2023. Disponível em: https://www.tetrapak.com/pt-br/insights/caixas-de-ideias/visao-do-especialista/Como-o-foco-em-digitalizacao-e-sustentabilidade-podem-contribuir-para-o-crescimento-da-industria-queijeira. Acesso em: 9 fev. 2025.
PIANA, V. J.; PELISSER, C.; SCHLEICHER SILVEIRA, M.; ENDRES, C. M.; GONÇALVES, A. L. PADRONIZAÇÃO DO PROCESSO DE FABRICAÇÃO DE ALIMENTOS POR MEIO DE IOT. Anais do Congresso Internacional de Conhecimento e Inovação – ciki, [S. l.], v. 1, n. 1, 2024. Disponível em: https://proceeding.ciki.ufsc.br/index.php/ciki/article/view/1554. Acesso em: 9 fev. 2025.
