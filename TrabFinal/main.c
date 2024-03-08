#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Data
{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct Endereco
{
    char rua[100];
    int numero;
    char cidade[100];
    char estado[50];
} Endereco;

typedef struct Cliente
{
    char cpf[12];
    char nome[100];
    char telefone[15];
    Endereco endereco;
    Data dataNascimento;
    struct Cliente* proximo;
    struct Cliente* anterior;
} Cliente;

typedef struct Produto
{
    int codigo;
    char descricao[100];
    int quantidadeEstoque;
    float precoUnitario;
    struct Produto* proximo;
    struct Produto* anterior;
} Produto;

typedef struct Venda
{
    int codigoVenda;
    char cpfCliente[12];
    int codigoProduto;
    int quantidadeComprada;
    struct Venda* proximo;
    struct Venda* anterior;
} Venda;

void incluirCliente(Cliente** lista, Cliente* novoCliente){  // ** pega a posicaoao do ponteiro no endereco
    if (*lista == NULL)                     //lista vazia
    {
        *lista = novoCliente;
        novoCliente->proximo = NULL;
        novoCliente->anterior = NULL;       //Proximo e anterior é nulo, pos é o unico da lista
    }
    else
    {
        Cliente* aux = *lista;
        while (aux->proximo != NULL)           // cria a aux para percerrer a lista ate encontrar o ultimo da lista
        {
            aux = aux->proximo;
        }
        aux->proximo = novoCliente;
        novoCliente->proximo = NULL;            //Insere o novo cliente e mostra q ele é o ultimo com o proximo nulo e coloca o aux(ultimo da lista no while) como anterior
        novoCliente->anterior = aux;
    }
}

int verificarCPFExistente(Cliente* lista, const char* cpf){
    Cliente* aux = lista;                         // aux é o pónteiro do primeiro da lista para percorrer a lista
    while (aux != NULL)
    {
        if (strcmp(aux->cpf, cpf) == 0)             //A função strcmp é utilizada para comparar as duas strings
        {
            return 1;                           // CPF encontrado
        }
        aux = aux->proximo;
    }
    return 0;                                    // CPF não encontrado
}

void incluirNovoCliente(Cliente** lista){
    Cliente* novoCliente = (Cliente*)malloc(sizeof(Cliente));   // aloca na memoria o novoCliente (malloc), do tamanho determinado por (sizeof)

    printf("CPF do cliente: ");
    scanf("%s", novoCliente->cpf);

    if (verificarCPFExistente(*lista, novoCliente->cpf))        // Verificar se o CPF já está cadastrado
    {
        printf("CPF já cadastrado.\n");
        free(novoCliente);                                      // libera a memoria alocada para esse novo cliente, pois ele n vai ser mais incluido(ja existe)
        return;
    }

    printf("Nome do cliente: ");
    scanf(" %[^\n]s", novoCliente->nome);                         // %[^\n]s para ler string com espaço em branco, ex: "joao vitor"

    printf("Telefone do cliente: ");
    scanf(" %[^\n]s", novoCliente->telefone);

    printf("Endereco do cliente - \n");
    printf("Rua: ");
    scanf(" %[^\n]s", novoCliente->endereco.rua);

    printf("Numero: ");
    scanf("%d", &novoCliente->endereco.numero);

    printf("Cidade: ");
    scanf(" %[^\n]s", novoCliente->endereco.cidade);

    printf("Estado: ");
    scanf("%s", novoCliente->endereco.estado);

    printf("Data de nascimento do cliente (DD MM AAAA): ");
    scanf("%d %d %d", &novoCliente->dataNascimento.dia, &novoCliente->dataNascimento.mes, &novoCliente->dataNascimento.ano);

    incluirCliente(lista, novoCliente);                     // chama a função para incluir

    printf("Cliente cadastrado com sucesso!\n");
}

void alterarCliente(Cliente* lista, const char* cpf){               // recebe como parametro o primeiro cliente da lista.   const pq o cpf nao muda e constante
    Cliente* aux = lista;

    while (aux != NULL)
    {
        if (strcmp(aux->cpf, cpf) == 0)                             // busca o cliente pelo cpf(Primary key)
        {
            printf("Novo nome do cliente: ");
            scanf(" %[^\n]s", aux->nome);

            printf("Novo telefone do cliente: ");
            scanf(" %[^\n]s", aux->telefone);

            printf("Novo endereco do cliente - \n");
            printf("Nova rua: ");
            scanf(" %[^\n]s", aux->endereco.rua);

            printf("Novo numero: ");                                                       // onde esta alterando?? salva as informaçoes, ok, mas onde esta sendo salvo???????????????????????????????????
            scanf("%d", &aux->endereco.numero);

            printf("Nova cidade: ");
            scanf(" %[^\n]s", aux->endereco.cidade);

            printf("Novo estado: ");
            scanf("%s", aux->endereco.estado);

            printf("Nova data de nascimento do cliente (DD MM AAAA): ");
            scanf("%d %d %d", &aux->dataNascimento.dia, &aux->dataNascimento.mes, &aux->dataNascimento.ano);

            printf("Cliente alterado com sucesso!\n");
            return;
        }
        aux = aux->proximo;
    }
                                                                    // se não encontra o cpf sai do while e printa o erro
    printf("Cliente não encontrado.\n");
}

void excluirCliente(Cliente** lista, const char* cpf,Venda* listaVendas ){   // const?????????????????????????????????????????????????????????????????????????
    Cliente* aux = *lista;                                          // aux = primeiro da lista

    while (aux != NULL)
    {
        if (strcmp(aux->cpf, cpf) == 0)                             // compara duas strings
        {
            Venda* test = NULL;
            Venda* auxV = listaVendas;                              // atribui ponteiro a lista de vendas para verificação
            while (auxV != NULL)
            {
                if (strcmp(auxV->cpfCliente, cpf) == 0)
                {
                    test = auxV;
                }
                auxV = auxV->proximo;
            }

            if (test != NULL)                                        // Verificar se o cliente está cadastrado em alguma venda
            {
                printf("O cliente está cadastrado em uma venda e não pode ser excluído.\n");
                return;
            }

            if (aux->anterior != NULL)
            {
                aux->anterior->proximo = aux->proximo;              // verifica se o cliente é o primeiro da lista
            }
            else
            {
                *lista = aux->proximo;                                  // é o primeiro da lista
            }

            if (aux->proximo != NULL)
            {
                aux->proximo->anterior = aux->anterior;                    // verifica se é o ultimo da lista
                                                                        // caso contrario ele é o ultimo da lisat ent n precisa atualizar a lista
            }

            free(aux);                                                  // libera o espaço da memoria (exclui o cliente)
            printf("Cliente excluído com sucesso!\n");
            return;
        }
        aux = aux->proximo;
    }

    printf("Cliente não encontrado.\n");
}

void consultarCliente(Cliente* lista, const char* cpf){
    Cliente* aux = lista;

    while (aux != NULL)
    {
        if (strcmp(aux->cpf, cpf) == 0)
        {
            printf("CPF: %s\n", aux->cpf);
            printf("Nome: %s\n", aux->nome);
            printf("Telefone: %s\n", aux->telefone);
            printf("Endereço: %s, %d, %s, %s\n", aux->endereco.rua, aux->endereco.numero, aux->endereco.cidade, aux->endereco.estado);
            printf("Data de Nascimento: %d/%d/%d\n", aux->dataNascimento.dia, aux->dataNascimento.mes, aux->dataNascimento.ano);
            return;
        }
        aux = aux->proximo;
    }

    printf("Cliente não encontrado.\n");
}

void incluirProduto(Produto** lista, Produto* novoProduto){
    if (*lista == NULL)
    {
        *lista = novoProduto;
        novoProduto->proximo = NULL;
        novoProduto->anterior = NULL;
    }
    else
    {
        Produto* aux = *lista;
        while (aux->proximo != NULL)
        {
            aux = aux->proximo;
        }
        aux->proximo = novoProduto;
        novoProduto->proximo = NULL;
        novoProduto->anterior = aux;
    }
}

int verificarCodigoExistente(Produto* lista, int codigo){
    Produto* aux = lista;
    while (aux != NULL)
    {
        if (aux->codigo == codigo)
        {
            return 1; // Código encontrado
        }
        aux = aux->proximo;
    }
    return 0; // Código não encontrado
}

Produto* obterProduto(Produto* lista, int codigo){
    Produto* aux = lista;
    while (aux != NULL){
        if (aux->codigo == codigo){
            return aux;
        }
        aux = aux->proximo;
    }
    return NULL;
}

void incluirNovoProduto(Produto** lista){
    Produto* novoProduto = (Produto*)malloc(sizeof(Produto));

    printf("Código do produto: ");
    scanf("%d", &novoProduto->codigo);

    // Verificar se o código já está cadastrado
    if (verificarCodigoExistente(*lista, novoProduto->codigo))
    {
        printf("Código já cadastrado.\n");
        free(novoProduto);
        return;
    }

    printf("Descrição do produto: ");
    scanf(" %[^\n]s", novoProduto->descricao);

    printf("Quantidade em estoque: ");
    scanf("%d", &novoProduto->quantidadeEstoque);

    printf("Preço unitário: ");
    scanf("%f", &novoProduto->precoUnitario);

    incluirProduto(lista, novoProduto);

    printf("Produto cadastrado com sucesso!\n");
}

void alterarProduto(Produto* lista, int codigo){
    Produto* aux = lista;

    while (aux != NULL)
    {
        if (aux->codigo == codigo)
        {
            printf("Nova descrição do produto: ");
            scanf(" %[^\n]s", aux->descricao);

            printf("Nova quantidade em estoque: ");
            scanf("%d", &aux->quantidadeEstoque);

            printf("Novo preço unitário: ");
            scanf("%f", &aux->precoUnitario);

            printf("Produto alterado com sucesso!\n");
            return;
        }
        aux = aux->proximo;
    }

    printf("Produto não encontrado.\n");
}

void excluirProduto(Produto** lista, int codigo, Venda* listaVendas){
    Produto* aux = *lista;

    while (aux != NULL)
    {
        if (aux->codigo == codigo)
        {
            Venda* test = NULL;
            Venda* auxV = listaVendas;
            while (auxV != NULL)
            {
                if (auxV->codigoProduto == codigo)
                {
                    test = auxV;
                }
                auxV = auxV->proximo;
            }

            // Verificar se o produto está cadastrado em alguma venda
            if (test != NULL)
            {
                printf("O produto está cadastrado em uma venda e não pode ser excluído.\n");
                return;
            }

            free(aux);
            printf("Produto excluído com sucesso!\n");
            return;
        }
        aux = aux->proximo;
    }

    printf("Produto não encontrado.\n");
}

void consultarProduto(Produto* lista, int codigo){
    Produto* aux = lista;

    while (aux != NULL)
    {
        if (aux->codigo == codigo)
        {
            printf("Código: %d\n", aux->codigo);
            printf("Descrição: %s\n", aux->descricao);
            printf("Quantidade em estoque: %d\n", aux->quantidadeEstoque);
            printf("Preço unitário: %.2f\n", aux->precoUnitario);
            return;
        }
        aux = aux->proximo;
    }

    printf("Produto não encontrado.\n");
}

int verificarClienteCadastrado(Cliente* lista, const char* cpf){
    Cliente* aux = lista;
    while (aux != NULL)
    {
        if (strcmp(aux->cpf, cpf) == 0)
        {
            return 1; // Cliente cadastrado
        }
        aux = aux->proximo;
    }
    return 0; // Cliente não cadastrado
}

void incluirNovaVenda(Venda** lista, Cliente* listaClientes, Produto* listaProdutos){
    Venda* novaVenda = (Venda*)malloc(sizeof(Venda));

    printf("Digite o código da venda: ");
    scanf("%d", &novaVenda->codigoVenda);

    printf("Digite o CPF do cliente: ");
    scanf("%s", novaVenda->cpfCliente);

    printf("Digite o código do produto: ");
    scanf("%d", &novaVenda->codigoProduto);

    printf("Digite a quantidade comprada: ");
    scanf("%d", &novaVenda->quantidadeComprada);

    novaVenda->proximo = NULL;
    novaVenda->anterior = NULL;

    // Verificar se o cliente existe
    Cliente* cliente = NULL;
    Cliente* auxCliente = listaClientes;
    while (auxCliente != NULL){
        if (strcmp(auxCliente->cpf, novaVenda->cpfCliente) == 0){
            cliente = auxCliente;
            break;
        }
        auxCliente = auxCliente->proximo;
    }

    if (cliente == NULL){
        printf("Cliente não encontrado. A venda não pode ser efetuada.\n");
        free(novaVenda);
        return;
    }

    // Verificar se o produto existe
    Produto* produto = obterProduto(listaProdutos, novaVenda->codigoProduto);
    if (produto == NULL){
        printf("Produto não encontrado. A venda não pode ser efetuada.\n");
        free(novaVenda);
        return;
    }

    // Verificar se a quantidade em estoque é suficiente
    if (novaVenda->quantidadeComprada > produto->quantidadeEstoque){
        printf("Quantidade em estoque insuficiente. A venda não pode ser efetuada.\n");
        free(novaVenda);
        return;
    }

    // Atualizar a quantidade em estoque do produto
    produto->quantidadeEstoque -= novaVenda->quantidadeComprada;

    // Adicionar a venda à lista de vendas
    if (*lista == NULL){
        *lista = novaVenda;
    } else {
        Venda* aux = *lista;
        while (aux->proximo != NULL){
            aux = aux->proximo;
        }
        aux->proximo = novaVenda;
        novaVenda->anterior = aux;
    }

    printf("Venda registrada com sucesso.\n");
}

void alterarVenda(Venda** lista, Cliente* listaClientes, Produto* listaProdutos) {
    int codigoVenda;

    printf("Digite o código da venda a ser alterada: ");
    scanf("%d", &codigoVenda);

    // Procurar a venda na lista
    Venda* venda = *lista;
    while (venda != NULL) {
        if (venda->codigoVenda == codigoVenda) {
            break;
        }
        venda = venda->proximo;
    }

    if (venda == NULL) {
        printf("Venda não encontrada.\n");
        return;
    }

    int quantidadeCompradaAnterior = venda->quantidadeComprada;

    printf("Digite a nova quantidade comprada: ");
    scanf("%d", &venda->quantidadeComprada);

    // Verificar se o produto existe
    Produto* produto = obterProduto(listaProdutos, venda->codigoProduto);
    if (produto == NULL){
        printf("Produto não encontrado. A venda não pode ser alterada.\n");
        return;
    }

    // Verificar se a nova quantidade em estoque é suficiente
    if (venda->quantidadeComprada > produto->quantidadeEstoque + quantidadeCompradaAnterior) {
        printf("Quantidade em estoque insuficiente. A venda não pode ser alterada.\n");
        return;
    }

    // Atualizar a quantidade em estoque do produto
    produto->quantidadeEstoque += quantidadeCompradaAnterior - venda->quantidadeComprada;

    printf("Venda alterada com sucesso.\n");
}

void excluirVenda(Venda** lista, Produto* listaProdutos) {
    int codigoVenda;

    printf("Digite o código da venda a ser excluída: ");
    scanf("%d", &codigoVenda);

    // Procurar a venda na lista
    Venda* venda = *lista;
    while (venda != NULL) {
        if (venda->codigoVenda == codigoVenda) {
            break;
        }
        venda = venda->proximo;
    }

    if (venda == NULL) {
        printf("Venda não encontrada.\n");
        return;
    }

    // Atualizar a quantidade em estoque do produto
    Produto* produto = obterProduto(listaProdutos, venda->codigoProduto);
    produto->quantidadeEstoque += venda->quantidadeComprada;

    // Remover a venda da lista
    if (venda->anterior != NULL) {
        venda->anterior->proximo = venda->proximo;
    } else {
        *lista = venda->proximo;
    }

    if (venda->proximo != NULL) {
        venda->proximo->anterior = venda->anterior;
    }

    free(venda);
    printf("Venda excluída com sucesso.\n");
}

void exibirVenda(Venda* lista) {
    int codigoVenda;

    printf("Digite o código da venda: ");
    scanf("%d", &codigoVenda);

    Venda* venda = lista;
    while (venda != NULL) {
        if (venda->codigoVenda == codigoVenda) {
            printf("Código da venda: %d\n", venda->codigoVenda);
            printf("CPF do cliente: %s\n", venda->cpfCliente);
            printf("Código do produto: %d\n", venda->codigoProduto);
            printf("Quantidade comprada: %d\n", venda->quantidadeComprada);
            return;
        }
        venda = venda->proximo;
    }

    printf("Venda não encontrada.\n");
}

void listarClientes(Cliente* listaClientes) {
    Cliente* cliente = listaClientes;

    if (cliente == NULL) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    printf("Clientes cadastrados:\n");
    while (cliente != NULL) {
        printf("CPF: %s\n", cliente->cpf);
        printf("Nome: %s\n", cliente->nome);
        printf("Telefone: %s\n", cliente->telefone);
        printf("Endereço: %s, %d - %s, %s\n", cliente->endereco.rua, cliente->endereco.numero, cliente->endereco.cidade, cliente->endereco.estado);
        printf("Data de Nascimento: %d/%d/%d\n", cliente->dataNascimento.dia, cliente->dataNascimento.mes, cliente->dataNascimento.ano);
        printf("--------------------\n");

        cliente = cliente->proximo;
    }
}

void listarProdutos(Produto* listaProdutos) {
    Produto* produto = listaProdutos;

    if (produto == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("Produtos cadastrados:\n");
    while (produto != NULL) {
        printf("Código: %d\n", produto->codigo);
        printf("Descrição: %s\n", produto->descricao);
        printf("Quantidade em estoque: %d\n", produto->quantidadeEstoque);
        printf("Preço unitário: %.2f\n", produto->precoUnitario);
        printf("--------------------\n");

        produto = produto->proximo;
    }
}

void listarVendas(Venda* listaVendas) {
    Venda* venda = listaVendas;

    if (venda == NULL) {
        printf("Nenhuma venda efetivada.\n");
        return;
    }

    printf("Vendas efetivadas:\n");
    while (venda != NULL) {
        printf("Código da venda: %d\n", venda->codigoVenda);
        printf("CPF do cliente: %s\n", venda->cpfCliente);
        printf("Código do produto: %d\n", venda->codigoProduto);
        printf("Quantidade comprada: %d\n", venda->quantidadeComprada);
        printf("--------------------\n");

        venda = venda->proximo;
    }
}

void listarClientesAcimaValor(Cliente* listaClientes, Venda* listaVendas, Produto* listaProdutos, float valor) {
    Cliente* cliente = listaClientes;
    while (cliente != NULL) {
        int totalCompras = 0;
        Venda* venda = listaVendas;
        Produto* produto = obterProduto(listaProdutos, venda->codigoProduto);
        while (venda != NULL) {
            if (strcmp(venda->cpfCliente, cliente->cpf) == 0 && ((venda->quantidadeComprada) * (produto->precoUnitario)) > valor) {
                totalCompras++;
            }
            venda = venda->proximo;
        }
        if (totalCompras > 0) {
            printf("\nCliente: %s\n", cliente->nome);
            printf("Quantidade de compras acima de %.2f: %d\n\n", valor, totalCompras);
            printf("--------------------\n");
        }
        cliente = cliente->proximo;
    }
}

void listarProdutosAbaixoEstoque(Produto* listaProdutos, int valor) {
    Produto* produto = listaProdutos;
    while (produto != NULL) {
        if (produto->quantidadeEstoque < valor) {
            printf("\nProduto: %s\n", produto->descricao);
            printf("Quantidade em estoque: %d\n\n", produto->quantidadeEstoque);
            printf("--------------------\n");
        }
        produto = produto->proximo;
    }
}

// Função para adicionar um cliente no final da lista
void adicionarCliente(Cliente** listaClientes, Cliente* novoCliente) {
    if (*listaClientes == NULL) {
        *listaClientes = novoCliente;
    } else {
        Cliente* ultimo = *listaClientes;
        while (ultimo->proximo != NULL) {
            ultimo = ultimo->proximo;
        }
        ultimo->proximo = novoCliente;
        novoCliente->anterior = ultimo;
    }
}

// Função para adicionar um produto no final da lista
void adicionarProduto(Produto** listaProdutos, Produto* novoProduto) {
    if (*listaProdutos == NULL) {
        *listaProdutos = novoProduto;
    } else {
        Produto* ultimo = *listaProdutos;
        while (ultimo->proximo != NULL) {
            ultimo = ultimo->proximo;
        }
        ultimo->proximo = novoProduto;
        novoProduto->anterior = ultimo;
    }
}

// Função para adicionar uma venda no final da lista
void adicionarVenda(Venda** listaVendas, Venda* novaVenda) {
    if (*listaVendas == NULL) {
        *listaVendas = novaVenda;
    } else {
        Venda* ultimo = *listaVendas;
        while (ultimo->proximo != NULL) {
            ultimo = ultimo->proximo;
        }
        ultimo->proximo = novaVenda;
        novaVenda->anterior = ultimo;
    }
}

// Função para criar um novo cliente
Cliente* criarCliente() {
    Cliente* novoCliente = (Cliente*)malloc(sizeof(Cliente));
    if (novoCliente != NULL) {
        novoCliente->proximo = NULL;
        novoCliente->anterior = NULL;
    }
    return novoCliente;
}

// Função para criar um novo produto
Produto* criarProduto() {
    Produto* novoProduto = (Produto*)malloc(sizeof(Produto));
    if (novoProduto != NULL) {
        novoProduto->proximo = NULL;
        novoProduto->anterior = NULL;
    }
    return novoProduto;
}

// Função para criar uma nova venda
Venda* criarVenda() {
    Venda* novaVenda = (Venda*)malloc(sizeof(Venda));
    if (novaVenda != NULL) {
        novaVenda->proximo = NULL;
        novaVenda->anterior = NULL;
    }
    return novaVenda;
}

void salvarDadosArquivo(Cliente* listaClientes, Produto* listaProdutos, Venda* listaVendas) {
    // Abrir o arquivo para escrita
    FILE* arquivo = fopen("dados.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Salvar os clientes no arquivo
    Cliente* cliente = listaClientes;
    while (cliente != NULL) {
        fprintf(arquivo, "Cliente|%s|%s|%s|%s|%d|%s|%s|%d|%d|%d\n",
            cliente->cpf, cliente->nome, cliente->telefone,
            cliente->endereco.rua, cliente->endereco.numero,
            cliente->endereco.cidade, cliente->endereco.estado,
            cliente->dataNascimento.dia, cliente->dataNascimento.mes,
            cliente->dataNascimento.ano);
        cliente = cliente->proximo;
    }

    // Salvar os produtos no arquivo
    Produto* produto = listaProdutos;
    while (produto != NULL) {
        fprintf(arquivo, "Produto|%d|%s|%d|%.2f\n",
            produto->codigo, produto->descricao,
            produto->quantidadeEstoque, produto->precoUnitario);
        produto = produto->proximo;
    }

    // Salvar as vendas no arquivo
    Venda* venda = listaVendas;
    while (venda != NULL) {
        fprintf(arquivo, "Venda|%d|%s|%d|%d\n",
            venda->codigoVenda, venda->cpfCliente,
            venda->codigoProduto, venda->quantidadeComprada);
        venda = venda->proximo;
    }

    // Fechar o arquivo
    fclose(arquivo);

    printf("Dados salvos com sucesso.\n");
}

void lerDadosArquivo(Cliente** listaClientes, Produto** listaProdutos, Venda** listaVendas) {
    // Abrir o arquivo para leitura
    FILE* arquivo = fopen("dados.txt", "r");
    if (arquivo == NULL) {
        printf("Arquivo de dados não encontrado.\n");
        return;
    }


    // Variáveis temporárias para ler os dados do arquivo
    char linha[200];

    // Ler os dados do arquivo e preencher as listas
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char tipo[10];
        sscanf(linha, "%[^|]", tipo);
        if (strcmp(tipo, "Cliente") == 0) {
            Cliente* cliente = criarCliente();
            sscanf(linha, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%d|%d|%d", tipo,
                &cliente->cpf, &cliente->nome, &cliente->telefone,
                &cliente->endereco.rua, &cliente->endereco.numero,
                &cliente->endereco.cidade, &cliente->endereco.estado,
                &cliente->dataNascimento.dia, &cliente->dataNascimento.mes,
                &cliente->dataNascimento.ano);
            adicionarCliente(listaClientes, cliente);
        } else if (strcmp(tipo, "Produto") == 0) {
            Produto* produto = criarProduto();
            sscanf(linha, "%[^|]|%d|%[^|]|%d|%f", tipo,
                &produto->codigo, &produto->descricao,
                &produto->quantidadeEstoque, &produto->precoUnitario);
            adicionarProduto(listaProdutos, produto);
        } else if (strcmp(tipo, "Venda") == 0) {
            Venda* venda = criarVenda();
            sscanf(linha, "%[^|]|%d|%[^|]|%d|%d", tipo,
                &venda->codigoVenda, venda->cpfCliente,
                &venda->codigoProduto, &venda->quantidadeComprada);
            adicionarVenda(listaVendas, venda);
        }
    }

    // Fechar o arquivo
    fclose(arquivo);

    printf("Dados carregados com sucesso.\n");
}


void exibirMenu(){
    printf("========================\n");
    printf("MENU\n");
    printf("========================\n");
    printf("1. Incluir cliente\n");
    printf("2. Alterar cliente\n");
    printf("3. Excluir cliente\n");
    printf("4. Consultar cliente\n");
    printf("5. Incluir produto\n");
    printf("6. Alterar produto\n");
    printf("7. Excluir produto\n");
    printf("8. Consultar produtos\n");
    printf("9. Incluir venda\n");
    printf("10. Alterar venda\n");
    printf("11. Excluir venda\n");
    printf("12. Exibir vendas\n");
    printf("========================\n");
    printf("13. Exibir Todos os Clientes\n");
    printf("14. Exibir Todos os Produtos\n");
    printf("15. Exibir Todos as Vendas\n");
    printf("16. Vendas Acima de um Valor\n");
    printf("17. Estoque Abaixo de um Valor\n");
    printf("========================\n");
    printf("18. Salvar Dados em Arquivo\n");
    printf("0. Sair\n");
    printf("========================\n");
    printf("Opção: ");
}

int main()
{
    Cliente* listaClientes = NULL;
    Produto* listaProdutos = NULL;
    Venda* listaVendas = NULL;
    lerDadosArquivo(&listaClientes, &listaProdutos, &listaVendas);
    int opcao;

    do
    {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao)
        {
            case 1:
                incluirNovoCliente(&listaClientes);
                break;
            case 2:
                printf("Digite o CPF do cliente a ser alterado: ");
                char cpfAlterar[12];
                scanf("%s", cpfAlterar);
                alterarCliente(listaClientes, cpfAlterar);
                break;
            case 3:
                printf("Digite o CPF do cliente a ser excluído: ");
                char cpfExcluir[12];
                scanf("%s", cpfExcluir);
                excluirCliente(&listaClientes, cpfExcluir, listaVendas);
                break;
            case 4:
                printf("Digite o CPF do cliente a ser consultado: ");
                char cpfConsultar[12];
                scanf("%s", cpfConsultar);
                consultarCliente(listaClientes, cpfConsultar);
                break;
            case 5:
                incluirNovoProduto(&listaProdutos);
                break;
            case 6:
                printf("Digite o código do produto a ser alterado: ");
                int codigoAlterar;
                scanf("%d", &codigoAlterar);
                alterarProduto(listaProdutos, codigoAlterar);
                break;
            case 7:
                printf("Digite o código do produto a ser excluído: ");
                int codigoExcluir;
                scanf("%d", &codigoExcluir);
                excluirProduto(&listaProdutos, codigoExcluir, listaVendas);
                break;
            case 8:
                printf("Digite o código do produto a ser consultado: ");
                int codigoConsultar;
                scanf("%d", &codigoConsultar);
                consultarProduto(listaProdutos, codigoConsultar);
                break;
            case 9:
                incluirNovaVenda(&listaVendas, listaClientes, listaProdutos);
                break;
            case 10:
                alterarVenda(&listaVendas, listaClientes, listaProdutos);
                break;
            case 11:
                excluirVenda(&listaVendas, listaProdutos);
                break;
            case 12:
                exibirVenda(listaVendas);
                break;
            case 13:
                listarClientes(listaClientes);
                break;
            case 14:
                listarProdutos(listaProdutos);
                break;
            case 15:
                listarVendas(listaVendas);
                break;
            case 16:
                printf("Valor: ");
                float valor;
                scanf("%f", &valor);
                listarClientesAcimaValor(listaClientes, listaVendas, listaProdutos, valor);
                break;
            case 17:
                printf("Digite o valor do estoque: ");
                int estoqueValor;
                scanf("%d", &estoqueValor);
                listarProdutosAbaixoEstoque(listaProdutos, estoqueValor);
                break;
            case 18:
                salvarDadosArquivo(listaClientes, listaProdutos, listaVendas);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }

        printf("\n");
    } while (opcao != 0);

    return 0;
}


