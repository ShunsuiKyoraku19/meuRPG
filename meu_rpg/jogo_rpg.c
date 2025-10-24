#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[50];
    int vida;
    int vidaMaxima;
    int ataque;
    int defesa;
    int nivel;
    int experiencia_dada;
    int stunned;
} Inimigo;

typedef enum {
    GUERREIRO,
    MAGO,
    PALADINO,
    ASSASSINO,
    TANK
} Classe;

typedef struct {
    char nome[50];
    Classe classe;
    int vida;
    int vidaMaxima;
    int ataque;
    int defesa;
    int nivel;
    int mana;
    int manaMaxima;
    int forca;
    int agilidade;
    int inteligencia;
    int experiencia;
    int pontosHabilidade;
    int escudoAtivo;
} personagem;

    int usarHabilidadeEspecial(personagem *p, Inimigo *i) {
        int custoMana = 30;
        int dano = 0;
        
        if (p->mana < custoMana) {
            printf("\nMana insuficiente para usar habilidade especial!\n");
            return -1;
        }

        p->mana -= custoMana;

        switch(p->classe) {
            case GUERREIRO:
                dano = p->forca * 3;
                printf("\nVoce usa GOLPE CIRCULAR causando dano em área!\n");
                break;
                
            case MAGO:
                dano = p->inteligencia * 4;
                printf("\nVoce lança EXPLOSÃO ARCANA com poder devastador!\n");
                break;
                
            case PALADINO:
                dano = p->forca * 2;
                int cura = p->vidaMaxima * 0.3;
                p->vida = (p->vida + cura > p->vidaMaxima) ? p->vidaMaxima : p->vida + cura;
                printf("\nVoce usa CURA DIVINA e recupera %d de HP!\n", cura);
                break;
                
            case ASSASSINO:
                dano = p->agilidade * 5;
                i->stunned = 1;
                printf("\nVoce usa ATAQUE FURTIVO causando dano crítico!\n");
                break;
                
            case TANK:
                p->escudoAtivo = 1;
                printf("\nVoce ativa ESCUDO PROTETOR reduzindo o próximo dano!\n");
                break;
        }
        
        return dano;
    }

    void mostrarDescricaoClasses() {
        printf("\n=== Classes Disponíveis ===\n");
        printf("1. Guerreiro - Especialista em combate corpo a corpo, forte e resistente\n");
        printf("   Status Base: Alta Força, Vida média-alta, Baixa Mana\n");
        printf("   Habilidade Especial: Golpe Circular (dano em área)\n\n");
        
        printf("2. Mago - Mestre das artes arcanas, domina magias poderosas\n");
        printf("   Status Base: Alta Inteligência, Vida baixa, Mana alta\n");
        printf("   Habilidade Especial: Explosão Arcana (dano mágico alto)\n\n");
        
        printf("3. Paladino - Guerreiro sagrado, equilibra ataque e defesa\n");
        printf("   Status Base: Força e Defesa balanceadas, Vida alta, Mana média\n");
        printf("   Habilidade Especial: Cura Divina (recupera HP)\n\n");
        
        printf("4. Assassino - Ágil e mortal, especialista em ataques rápidos\n");
        printf("   Status Base: Alta Agilidade, Vida baixa, Mana média\n");
        printf("   Habilidade Especial: Ataque Furtivo (dano crítico)\n\n");
        
        printf("5. Tank - Especialista em defesa e sobrevivência\n");
        printf("   Status Base: Alta Defesa, Vida muito alta, Mana baixa\n");
        printf("   Habilidade Especial: Escudo Protetor (reduz dano)\n");
    }

    personagem criarPersonagem(const char* nome, Classe classe) {
        personagem p;
        strncpy(p.nome, nome, sizeof(p.nome) - 1);
        p.nome[sizeof(p.nome) - 1] = '\0';
        p.classe = classe;
        p.nivel = 1;
        p.experiencia = 0;
        p.pontosHabilidade = 0;
        p.escudoAtivo = 0;

        switch(classe) {
            case GUERREIRO:
                p.vidaMaxima = 120;
                p.manaMaxima = 30;
                p.forca = 15;
                p.agilidade = 10;
                p.inteligencia = 5;
                p.defesa = 30;
                break;
                
            case MAGO:
                p.vidaMaxima = 80;
                p.manaMaxima = 100;
                p.forca = 5;
                p.agilidade = 8;
                p.inteligencia = 20;
                p.defesa = 15;
                break;
                
            case PALADINO:
                p.vidaMaxima = 150;
                p.manaMaxima = 50;
                p.forca = 12;
                p.agilidade = 8;
                p.inteligencia = 10;
                p.defesa = 35;
                break;
                
            case ASSASSINO:
                p.vidaMaxima = 90;
                p.manaMaxima = 40;
                p.forca = 10;
                p.agilidade = 20;
                p.inteligencia = 8;
                p.defesa = 20;
                break;
                
            case TANK:
                p.vidaMaxima = 200;
                p.manaMaxima = 20;
                p.forca = 10;
                p.agilidade = 5;
                p.inteligencia = 5;
                p.defesa = 45;
                break;
        }

        p.vida = p.vidaMaxima;
        p.mana = p.manaMaxima;
        p.ataque = p.forca * 2;

        return p;
    }

    Inimigo criarInimigo(personagem *p) {
        Inimigo i;
        const char* nomes[] = {"Goblin", "Orc", "Troll", "Esqueleto", "Slime", "Bandido", "Lobo", "Aranha"};
        int numNomes = sizeof(nomes) / sizeof(nomes[0]);
        
        strcpy(i.nome, nomes[rand() % numNomes]);
        
        i.nivel = p->nivel + (rand() % 5 - 2);
        if (i.nivel < 1) i.nivel = 1;
        
        i.vidaMaxima = (30 + i.nivel * 10) + (p->vidaMaxima / 10);
        i.vida = i.vidaMaxima;
        i.ataque = (8 + i.nivel * 3) + (p->ataque / 8);
        i.defesa = (5 + i.nivel * 2) + (p->defesa / 8);
        i.experiencia_dada = 20 + (i.nivel * 10);
        i.stunned = 0;
        
        return i;
    }

    int calcularDano(int ataque, int defesa) {
        int dano = ataque - (defesa / 2);
        return dano > 0 ? dano : 1;
    }

    void distribuirPontos(personagem *p) {
        while (p->pontosHabilidade > 0) {
            printf("\n=== Pontos de Habilidade Disponiveis: %d ===\n", p->pontosHabilidade);
            printf("Escolha onde investir seus pontos:\n");
            printf("1. Vida Maxima (Atual: %d/5000)\n", p->vidaMaxima);
            printf("2. Mana Maxima (Atual: %d/300)\n", p->manaMaxima);
            printf("3. Forca (Atual: %d/500)\n", p->forca);
            printf("4. Agilidade (Atual: %d/500)\n", p->agilidade);
            printf("5. Inteligencia (Atual: %d/500)\n", p->inteligencia);
            printf("6. Defesa (Atual: %d/500)\n", p->defesa);
            printf("7. Guardar pontos para depois\n");
            printf("Escolha: ");

            int escolha;
            scanf("%d", &escolha);

            switch(escolha) {
                case 1:
                    if (p->vidaMaxima < 5000) {
                        p->vidaMaxima += 50;
                        p->vida = p->vidaMaxima;
                        if (p->vidaMaxima > 5000) p->vidaMaxima = 5000;
                        p->pontosHabilidade--;
                    } else {
                        printf("Vida Maxima ja esta no limite!\n");
                    }
                    break;
                case 2:
                    if (p->manaMaxima < 300) {
                        p->manaMaxima += 10;
                        p->mana = p->manaMaxima;
                        if (p->manaMaxima > 300) p->manaMaxima = 300;
                        p->pontosHabilidade--;
                    } else {
                        printf("Mana Maxima ja esta no limite!\n");
                    }
                    break;
                case 3:
                    if (p->forca < 500) {
                        p->forca += 5;
                        if (p->forca > 500) p->forca = 500;
                        p->ataque = p->forca * 2;
                        p->pontosHabilidade--;
                    } else {
                        printf("Forca ja esta no limite!\n");
                    }
                    break;
                case 4:
                    if (p->agilidade < 500) {
                        p->agilidade += 5;
                        if (p->agilidade > 500) p->agilidade = 500;
                        p->pontosHabilidade--;
                    } else {
                        printf("Agilidade ja esta no limite!\n");
                    }
                    break;
                case 5:
                    if (p->inteligencia < 500) {
                        p->inteligencia += 5;
                        if (p->inteligencia > 500) p->inteligencia = 500;
                        p->pontosHabilidade--;
                    } else {
                        printf("Inteligencia ja esta no limite!\n");
                    }
                    break;
                case 6:
                    if (p->defesa < 500) {
                        p->defesa += 5;
                        if (p->defesa > 500) p->defesa = 500;
                        p->pontosHabilidade--;
                    } else {
                        printf("Defesa ja esta no limite!\n");
                    }
                    break;
                case 7:
                    return;
                default:
                    printf("Opcao invalida!\n");
            }
        }
    }

    void levelUp(personagem *p) {
        p->nivel++;
        p->pontosHabilidade += 5;
        printf("\nPARABENS! Nivel aumentou para %d!\n", p->nivel);
        printf("Voce ganhou 5 pontos de habilidade!\n");
        distribuirPontos(p);
    }

    int calcularExpNecessaria(int nivel) {
        return 100 * nivel * nivel;
    }

    void ganharExperiencia(personagem *p, int exp) {
        int expNecessaria = calcularExpNecessaria(p->nivel);
        p->experiencia += exp;
        printf("Ganhou %d de experiencia!\n", exp);
        printf("Experiencia: %d/%d\n", p->experiencia, expNecessaria);
        
        while (p->experiencia >= expNecessaria) {
            p->experiencia -= expNecessaria;
            levelUp(p);
            expNecessaria = calcularExpNecessaria(p->nivel);
            printf("Experiencia para proximo nivel: %d\n", expNecessaria);
        }
    }

    int calcularDanoMagico(int inteligencia, int defesa, int custoMana) {
        return (inteligencia * 3 + custoMana) - (defesa / 3);
    }

    int atacarMagicamente(personagem *p, Inimigo *i) {
        printf("\nEscolha seu ataque:\n");
        printf("1. Bola de Fogo (20 mana) - Dano baseado em Inteligencia\n");
        printf("2. Lanca de Gelo (15 mana) - Dano menor mas congela\n");
        printf("3. Raio (25 mana) - Dano alto mas consome mais mana\n");
        printf("4. Ataque Normal - Nao usa mana\n");
        printf("5. Habilidade Especial (30 mana)\n");
        printf("Escolha: ");

        int escolha;
        scanf("%d", &escolha);

        int dano = 0;
        switch(escolha) {
            case 1:
                if(p->mana >= 20) {
                    dano = calcularDanoMagico(p->inteligencia, i->defesa, 20);
                    p->mana -= 20;
                    printf("\nVoce lanca uma poderosa BOLA DE FOGO!\n");
                } else {
                    printf("\nMana insuficiente para Bola de Fogo!\n");
                    return -1;
                }
                break;

            case 2:
                if(p->mana >= 15) {
                    dano = calcularDanoMagico(p->inteligencia, i->defesa, 15);
                    p->mana -= 15;
                    printf("\nVoce conjura uma LANCA DE GELO afiada!\n");
                } else {
                    printf("\nMana insuficiente para Lanca de Gelo!\n");
                    return -1;
                }
                break;

            case 3:
                if(p->mana >= 25) {
                    dano = calcularDanoMagico(p->inteligencia, i->defesa, 25);
                    p->mana -= 25;
                    printf("\nVoce invoca um RAIO devastador!\n");
                } else {
                    printf("\nMana insuficiente para Raio!\n");
                    return -1;
                }
                break;

            case 4:
                dano = calcularDano(p->ataque, i->defesa);
                printf("\nVoce realiza um ataque normal!\n");
                break;
                
            case 5:
                dano = usarHabilidadeEspecial(p, i);
                if(dano == -1) return -1;
                break;

            default:
                printf("\nOpcao invalida! Realizando ataque normal.\n");
                dano = calcularDano(p->ataque, i->defesa);
        }
        return dano;
    }

    int combate(personagem *p, Inimigo *i) {
        printf("\n=== COMBATE INICIADO ===\n");
        printf("Voce encontrou um %s nivel %d!\n", i->nome, i->nivel);
        
        while (1) {
            printf("\nSeu MP: %d/%d\n", p->mana, p->manaMaxima);
            
            int danoJogador = atacarMagicamente(p, i);
            if(danoJogador == -1) {
                continue;
            }
            
            i->vida -= danoJogador;
            printf("Voce causou %d de dano ao %s!\n", danoJogador, i->nome);
            printf("%s: %d/%d HP\n", i->nome, i->vida, i->vidaMaxima);
            
            if (i->vida <= 0) {
                printf("\nVoce derrotou o %s!\n", i->nome);
                ganharExperiencia(p, i->experiencia_dada);
                return 1;
            }
            
            if (i->stunned) {
                printf("\n%s esta atordoado e nao pode atacar!\n", i->nome);
                i->stunned = 0;
                continue;
            }
            
            int danoInimigo = calcularDano(i->ataque, p->defesa);
            if (p->escudoAtivo) {
                danoInimigo /= 2;
                p->escudoAtivo = 0;
                printf("\nSeu escudo reduziu o dano pela metade!\n");
            }
            
            p->vida -= danoInimigo;
            printf("\n%s causou %d de dano a voce!\n", i->nome, danoInimigo);
            printf("Seu HP: %d/%d\n", p->vida, p->vidaMaxima);
            
            if (p->vida <= 0) {
                printf("\nVoce foi derrotado pelo %s...\n", i->nome);
                return 0;
            }
        }
    }
    
    const char* getNomeClasse(Classe classe) {
        switch(classe) {
            case GUERREIRO: return "Guerreiro";
            case MAGO: return "Mago";
            case PALADINO: return "Paladino";
            case ASSASSINO: return "Assassino";
            case TANK: return "Tank";
            default: return "Desconhecido";
        }
    }

    void exibirStatus(personagem p){
        printf("Nome: %s\n", p.nome);
        printf("Classe: %s\n", getNomeClasse(p.classe));
        printf("Nivel: %d\n", p.nivel);
        printf("Vida: %d/%d\n", p.vida, p.vidaMaxima);
        printf("Mana: %d/%d\n", p.mana, p.manaMaxima);
        printf("Forca: %d\n", p.forca);
        printf("Agilidade: %d\n", p.agilidade);
        printf("Inteligencia: %d\n", p.inteligencia);
        printf("Ataque: %d\n", p.ataque);
        printf("Defesa: %d\n", p.defesa);
        printf("Experiencia: %d/%d\n", p.experiencia, calcularExpNecessaria(p.nivel));
    }

void salvarJogo(personagem p) {
    FILE *arquivo = fopen("save_game.dat", "wb");
    if (arquivo == NULL) {
        printf("\nErro ao criar arquivo de save!\n");
        return;
    }
    
    fwrite(&p, sizeof(personagem), 1, arquivo);
    fclose(arquivo);
    printf("\nJogo salvo com sucesso!\n");
}

personagem carregarJogo() {
    FILE *arquivo = fopen("save_game.dat", "rb");
    personagem p;
    
    if (arquivo == NULL) {
        printf("\nNenhum save encontrado!\n");
        return criarPersonagem("NovoHeroi", GUERREIRO);
    }
    
    fread(&p, sizeof(personagem), 1, arquivo);
    fclose(arquivo);
    printf("\nJogo carregado com sucesso!\n");
    return p;
}

#define MAX_PERSONAGENS 5

void salvarTodosPersonagens(personagem personagens[], int numPersonagens) {
    FILE *arquivo = fopen("personagens.dat", "wb");
    if (arquivo == NULL) {
        printf("\nErro ao criar arquivo de save!\n");
        return;
    }
    
    fwrite(&numPersonagens, sizeof(int), 1, arquivo);
    fwrite(personagens, sizeof(personagem), numPersonagens, arquivo);
    fclose(arquivo);
    printf("\nTodos os personagens foram salvos com sucesso!\n");
}

int carregarTodosPersonagens(personagem personagens[]) {
    FILE *arquivo = fopen("personagens.dat", "rb");
    int numPersonagens = 0;
    
    if (arquivo == NULL) {
        return 0;
    }
    
    fread(&numPersonagens, sizeof(int), 1, arquivo);
    fread(personagens, sizeof(personagem), numPersonagens, arquivo);
    fclose(arquivo);
    printf("\nPersonagens carregados com sucesso!\n");
    return numPersonagens;
}

personagem criarNovoPersonagem() {
    char nome[50];
    int escolhaClasse;
    
    printf("\nDigite o nome do personagem: ");
    scanf("%s", nome);
    
    mostrarDescricaoClasses();
    
    do {
        printf("\nEscolha sua classe (1-5): ");
        scanf("%d", &escolhaClasse);
    } while (escolhaClasse < 1 || escolhaClasse > 5);
    
    return criarPersonagem(nome, (Classe)(escolhaClasse - 1));
}

int main(){
    srand(time(NULL));
    
    personagem personagens[MAX_PERSONAGENS];
    int numPersonagens = carregarTodosPersonagens(personagens);
    int personagemAtual = 0;
    
    printf("Bem-vindo ao RPG!\n");
    
    int continuar = 1;
    while (continuar) {
        printf("\n=== MENU PRINCIPAL ===\n");
        if (numPersonagens > 0) {
            printf("Personagem atual: %s (%s)\n", 
                personagens[personagemAtual].nome, 
                getNomeClasse(personagens[personagemAtual].classe));
        }
        printf("1. Criar novo personagem\n");
        printf("2. Selecionar personagem\n");
        printf("3. Ver status\n");
        printf("4. Procurar inimigo\n");
        printf("5. Descansar (recupera HP)\n");
        printf("6. Distribuir pontos de habilidade\n");
        printf("7. Salvar jogo\n");
        printf("8. Sair\n");
        printf("Escolha: ");
        
        int escolha;
        scanf("%d", &escolha);
        
        Inimigo inimigo;
        switch (escolha) {
            case 1:
                if (numPersonagens < MAX_PERSONAGENS) {
                    personagens[numPersonagens] = criarNovoPersonagem();
                    personagemAtual = numPersonagens;
                    numPersonagens++;
                    printf("\nPersonagem criado com sucesso!\n");
                } else {
                    printf("\nLimite máximo de personagens atingido!\n");
                }
                break;
                
            case 2:
                if (numPersonagens > 0) {
                    printf("\nPersonagens disponíveis:\n");
                    for (int i = 0; i < numPersonagens; i++) {
                        printf("%d. %s (%s) - Nível %d\n", 
                            i + 1, 
                            personagens[i].nome, 
                            getNomeClasse(personagens[i].classe),
                            personagens[i].nivel);
                    }
                    printf("Escolha um personagem (1-%d): ", numPersonagens);
                    int escolhaPersonagem;
                    scanf("%d", &escolhaPersonagem);
                    if (escolhaPersonagem >= 1 && escolhaPersonagem <= numPersonagens) {
                        personagemAtual = escolhaPersonagem - 1;
                        printf("Personagem selecionado: %s\n", personagens[personagemAtual].nome);
                    } else {
                        printf("Escolha inválida!\n");
                    }
                } else {
                    printf("\nNenhum personagem criado ainda!\n");
                }
                break;
                
            case 3:
                if (numPersonagens > 0) {
                    exibirStatus(personagens[personagemAtual]);
                } else {
                    printf("\nNenhum personagem criado ainda!\n");
                }
                break;
                
            case 4:
                if (numPersonagens > 0) {
                    inimigo = criarInimigo(&personagens[personagemAtual]);
                    if (combate(&personagens[personagemAtual], &inimigo)) {
                    } else {
                        printf("\nGAME OVER!\n");
                        if (numPersonagens > 1) {
                            printf("Escolha outro personagem para continuar...\n");
                        } else {
                            return 0;
                        }
                    }
                } else {
                    printf("\nCrie um personagem primeiro!\n");
                }
                break;
                
            case 5:
                if (numPersonagens > 0) {
                    personagens[personagemAtual].vida = personagens[personagemAtual].vidaMaxima;
                    personagens[personagemAtual].mana = personagens[personagemAtual].manaMaxima;
                    printf("\nVoce descansou e recuperou todo seu HP e Mana!\n");
                } else {
                    printf("\nCrie um personagem primeiro!\n");
                }
                break;
                
            case 6:
                if (numPersonagens > 0) {
                    if (personagens[personagemAtual].pontosHabilidade > 0) {
                        distribuirPontos(&personagens[personagemAtual]);
                    } else {
                        printf("\nVoce nao tem pontos de habilidade disponiveis!\n");
                    }
                } else {
                    printf("\nCrie um personagem primeiro!\n");
                }
                break;
                
            case 7:
                salvarTodosPersonagens(personagens, numPersonagens);
                break;
                
            case 8:
                salvarTodosPersonagens(personagens, numPersonagens);
                printf("\nJogo salvo automaticamente!\n");
                continuar = 0;
                break;
                
            default:
                printf("\nOpcao invalida!\n");
        }
    }
    
    printf("\nObrigado por jogar!\n");
    return 0;
}