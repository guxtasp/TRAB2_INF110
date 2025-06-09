# Manipulador de Imagens PNM - INF110

Este projeto é um trabalho prático da disciplina **INF110**, desenvolvido com o objetivo de manipular imagens no formato **PNM (Portable Any Map)**, suportando os formatos **P2 (tons de cinza)** e **P3 (colorido RGB)**. O programa permite a aplicação de  filtros desenvolvidos e transformações sobre as imagens, como escurecimento, clareamento, negativação, espelhamento, entre outros.

## 📂 Formatos Suportados

- **P2**: Imagens em tons de cinza (ASCII)
- **P3**: Imagens coloridas (RGB, ASCII)
- **500x500**: Tamanho máximo da imagem suportado

> ⚠️ Os formatos **P1**, **P4**, **P5** e **P6** não são suportados.

## 🔧 Funcionalidades

- Escurecer imagem
- Clarear imagem
- Negativar imagem
- Espelhar imagem verticalmente
- Aplicar filtro de Prewitt (detecção de bordas)
- Desfocar imagem (Gaussiano)
- Converter para tons de cinza
- Pixelizar imagem

## 🚀 Como Compilar e Executar

1. **Clone o repositório**:
   ```bash
   git clone https://github.com/guxt4sp/TRAB2_INF110.git
   cd TRAB2_INF110
   ```

2. **Compile com g++**:
   ```bash
   g++ manipulador_imagem.cpp
   ```

3. **Execute o programa**:
   ```bash
   ./a.out
   ```

## 💡 Exemplo de Uso

Ao rodar o programa, você será solicitado a informar o nome do arquivo `.pnm`:

```bash
Digite o nome do arquivo (Nao se esqueca da extensao .pnm): exemplo.pnm
```

Em seguida, poderá escolher uma das opções de processamento:

```
1 - Escurecer
2 - Clarear
3 - Negativar
4 - Espelhar
5 - Filtro de Prewitt
6 - Desfocar
7 - Tons de cinza
8 - Pixelizar
```

## 📁 Organização do Código

- `imagem.cpp`: Código-fonte principal contendo a lógica de leitura, manipulação e gravação das imagens.
- `README.md`: Este arquivo de documentação.
- `exemplos/`: Pasta opcional para imagens de exemplo de entrada/saída.

## 🧑‍💻 Autores

- André Gustavo dos Santos  (Autor do código-base)
  - Criado em: 16/06/2014  
  - Última modificação: 15/07/2024  
- Gustavo Santos Pinto

## 💡 Dica

Para gerar uma variedade de imagens de teste, recomendamos o uso do [GIMP](https://www.gimp.org/), um editor de imagens gratuito e de código aberto. Com ele, você pode:

- Criar imagens personalizadas e exportá-las diretamente no formato **PNM** (`.pnm`, `.ppm`, `.pgm`)
- Exportar imagens em **JPEG** e depois convertê-las para PNM com ferramentas de conversão

Isso facilita a geração de imagens compatíveis com o manipulador, permitindo testar os diversos filtros e funcionalidades implementadas.

INF110 (Programação I) – Universidade Federal de Viçosa (Trabalho Prático 2)
