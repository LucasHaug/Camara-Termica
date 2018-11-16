# Câmara Térmica

Código para rodar na Nucleo-64 da ST. O código foi elaborado para funcionar com as Nucleo-64: STM32F303RET6 e STM32F072RBT6, sendo necessário alterar uma configuração no início do Makefile para escolher entre uma das duas.

## Requisitos

* [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html)
  > É necessário colocar o local de instalação na varíavel de ambiente `CUBE_PATH`

* make
  > Linux: `sudo apt install make`
  >
  > Windows: `msys2> pacman -S make`

* [GNU Arm Embedded Toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads)
  > É necessário que a pasta `bin` dessa instalação esteja no `PATH`
  > e numa variável de ambiente `ARM_GCC_PATH`

* clang-format
  > Linux: `sudo apt install clang-format`
  >
  > Windows: `msys2> pacman -S clang`

* [Visual Studio Code](https://code.visualstudio.com/)
  * [EditorConfig](https://marketplace.visualstudio.com/items?itemName=EditorConfig.EditorConfig)
  * [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)

* [ST-Link](https://github.com/texane/stlink) ou [J-Link](https://www.segger.com/downloads/jlink/)
  > É necessário que o executável também esteja no `PATH`

## Gerando arquivos

Com o arquivo do projeto na pasta correta, os seguintes comandos devem ser 
executados (necessário apenas após dar checkout no repositório ou mudar o cube):

```bash
$ make cube     # Gera os arquivos do cube
$ make prepare  # Apaga os arquivos do cube desnecessários
```

Se, após modificar os arquivos do cube, ocorrer algum erro nos comandos acima,
pode rodar `make clean_cube` para apagar os arquivos gerados e então tentar 
novamente para que eles sejam gerados do zero.


## Compilando

Para compilar os arquivos rode

```bash
$ make
```

Às vezes, é necessário limpar os arquivos já compilados, se algum erro estiver 
acontecendo, para isso faça:

```bash
make clean
```

Isso apaga todos os arquivos de compilação gerados, exceto aqueles gerados a 
partir  das bibliotecas da ST geradas pelo Cube, isso ocorre para agilizar um 
novo build, já que raramente será necessário recompilar esses arquivos, mas caso 
seja necessário, é possível limpar todos os arquivos de compilação com

```bash
make clean_all
```

## Gravando

Para gravar os arquivos na placa, rode

```bash
$ make flash
```

Ou, caso use um gravador com J-Link:

```bash
$ make jflash
```

## Formatando

Para garantir que o código está formatado, utilize o atalho `CTRL`+`S` para
salvar e formatar o arquivo em que se está mexendo ou, para formatar todos
os arquivos do repositório de uma vez, rode 

```bash
$ make format
```

---

Estrutura de pastas, Makefile e configurações baseadas em: https://github.com/ThundeRatz/STM32ProjectTemplate
