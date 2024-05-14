# Requisitos para rodar o código

- MingGW
- GNU Make

# Funcionalidades do programa

- Busca em Profundidade.
- Busca em Largura.
- Componentes conectados.
- Vértices de Articulação.
- Ler um arquivo e gerar um arquivo de saída.
- Entre outras inclusas no programa.

# Como rodar o código:

Para compilar e executar o código em C, siga os passos abaixo:

1. Certifique-se de ter o MingGW e o GNU Make instalados em seu sistema.
2. Abra o terminal e navegue até o diretório onde o arquivo de código-fonte está localizado.
3. Execute o seguinte comando para compilar o código:
    ```
    make ep1_lista
    ou
    make CFLAGS+="-DMATRIZ" ep1_matriz
    ```
4. Após a compilação bem-sucedida, execute o seguinte comando para executar o programa:
    ```
    ./ep1_lista.exe arquivo-de-entrada arquivo-de-saida
    ou
    ./ep1_matriz.exe arquivo-de-entrada arquivo-de-saida
    ```
5. O programa será executado com as funcoes implementadas no `main`. Caso queira adicionar ou remover alguma funcionalidade, consulte os `grafo_matrizadj.h` ou `grafo_listaadj.h` para ver quais funcoes estao disponiveis envolvendo grafos ou entao consulte `ep1_xxx.c` para funcoes mais complexas e sinta-se a vontade para modificar e testar.

6. Caso queira excluir os arquivos gerados, execute o seguinte programa para remover os arquivos:
    ```
    make cleanWIN
    ou
    make cleanLINUX
    ```